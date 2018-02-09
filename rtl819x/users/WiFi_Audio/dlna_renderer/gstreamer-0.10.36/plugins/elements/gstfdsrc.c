/* GStreamer
 * Copyright (C) 1999,2000 Erik Walthinsen <omega@cse.ogi.edu>
 *                    2000 Wim Taymans <wtay@chello.be>
 *                    2005 Philippe Khalaf <burger@speedy.org>
 *
 * gstfdsrc.c:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
/**
 * SECTION:element-fdsrc
 * @see_also: #GstFdSink
 *
 * Read data from a unix file descriptor.
 * 
 * To generate data, enter some data on the console folowed by enter.
 * The above mentioned pipeline should dump data packets to the console.
 * 
 * If the #GstFdSrc:timeout property is set to a value bigger than 0, fdsrc will
 * generate an element message named
 * <classname>&quot;GstFdSrcTimeout&quot;</classname>
 * if no data was recieved in the given timeout.
 * The message's structure contains one field:
 * <itemizedlist>
 * <listitem>
 *   <para>
 *   #guint64
 *   <classname>&quot;timeout&quot;</classname>: the timeout in microseconds that
 *   expired when waiting for data.
 *   </para>
 * </listitem>
 * </itemizedlist>
 * 
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * echo "Hello GStreamer" | gst-launch -v fdsrc ! fakesink dump=true
 * ]| A simple pipeline to read from the standard input and dump the data
 * with a fakesink as hex ascii block.
 * </refsect2>
 * 
 * Last reviewed on 2008-06-20 (0.10.21)
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#include "gst/gst_private.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#ifdef G_OS_WIN32
#include <io.h>                 /* lseek, open, close, read */
#undef lseek
#define lseek _lseeki64
#undef off_t
#define off_t guint64
#endif

#include <sys/stat.h>
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#include <fcntl.h>
#include <stdio.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef _MSC_VER
#undef stat
#define stat _stat
#define fstat _fstat
#define S_ISREG(m)	(((m)&S_IFREG)==S_IFREG)
#endif
#include <stdlib.h>
#include <errno.h>

#include "gstfdsrc.h"
unsigned int isSeek=0;
int CheckIsOOBReceived(int sock_fd);
int IsDataAvailable(int src_fd, unsigned int iTimeout);
int MAX_Retry=0;
static GstStaticPadTemplate srctemplate = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS_ANY);

GST_DEBUG_CATEGORY_STATIC (gst_fd_src_debug);
#define GST_CAT_DEFAULT gst_fd_src_debug

#define DEFAULT_FD              0
#define DEFAULT_TIMEOUT         0

enum
{
  PROP_0,

  PROP_FD,
  PROP_TIMEOUT,
  PROP_NETSOCK_FD,

  PROP_LAST
};

static void gst_fd_src_uri_handler_init (gpointer g_iface, gpointer iface_data);

static void
_do_init (GType fd_src_type)
{
  static const GInterfaceInfo urihandler_info = {
    gst_fd_src_uri_handler_init,
    NULL,
    NULL
  };

  g_type_add_interface_static (fd_src_type, GST_TYPE_URI_HANDLER,
      &urihandler_info);

  GST_DEBUG_CATEGORY_INIT (gst_fd_src_debug, "fdsrc", 0, "fdsrc element");
}

GST_BOILERPLATE_FULL (GstFdSrc, gst_fd_src, GstPushSrc, GST_TYPE_PUSH_SRC,
    _do_init);

static void gst_fd_src_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_fd_src_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);
static void gst_fd_src_dispose (GObject * obj);

static gboolean gst_fd_src_start (GstBaseSrc * bsrc);
static gboolean gst_fd_src_stop (GstBaseSrc * bsrc);
static gboolean gst_fd_src_unlock (GstBaseSrc * bsrc);
static gboolean gst_fd_src_unlock_stop (GstBaseSrc * bsrc);
static gboolean gst_fd_src_is_seekable (GstBaseSrc * bsrc);
static gboolean gst_fd_src_get_size (GstBaseSrc * src, guint64 * size);
static gboolean gst_fd_src_do_seek (GstBaseSrc * src, GstSegment * segment);
static gboolean gst_fd_src_query (GstBaseSrc * src, GstQuery * query);

static GstFlowReturn gst_fd_src_create (GstPushSrc * psrc, GstBuffer ** outbuf);



int fdsrc_write_line_to_file_(const char *filename, int mode, char *line_data);
int fdsrc_write_line_to_file_(const char *filename, int mode, char *line_data)
{
	unsigned char tmpbuf[512];
	int fh=0;
	if(mode == 1) {/* write line datato file */
		fh = open(filename, O_RDWR|O_CREAT|O_TRUNC);
	}else if(mode == 2){/*append line data to file*/
		fh = open(filename, O_RDWR|O_APPEND);	
	}
	if (fh < 0) {
		fprintf(stderr, "Create %s error!\n", filename);
		return 0;
	}
	sprintf(tmpbuf, "%s", line_data);
	write(fh, tmpbuf, strlen(tmpbuf));
	close(fh);
	return 1;
}
static void
gst_fd_src_base_init (gpointer g_class)
{
  GstElementClass *gstelement_class = GST_ELEMENT_CLASS (g_class);

  gst_element_class_set_details_simple (gstelement_class,
      "Filedescriptor Source",
      "Source/File",
      "Read from a file descriptor", "Erik Walthinsen <omega@cse.ogi.edu>");
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&srctemplate));
}

static void
gst_fd_src_class_init (GstFdSrcClass * klass)
{
  GObjectClass *gobject_class;
  GstBaseSrcClass *gstbasesrc_class;
  GstPushSrcClass *gstpush_src_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gstbasesrc_class = GST_BASE_SRC_CLASS (klass);
  gstpush_src_class = GST_PUSH_SRC_CLASS (klass);

  gobject_class->set_property = gst_fd_src_set_property;
  gobject_class->get_property = gst_fd_src_get_property;
  gobject_class->dispose = gst_fd_src_dispose;

  g_object_class_install_property (gobject_class, PROP_FD,
      g_param_spec_int ("fd", "fd", "An open file descriptor to read from",
          0, G_MAXINT, DEFAULT_FD, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
          
g_object_class_install_property (gobject_class, PROP_NETSOCK_FD,
      g_param_spec_int ("is-net", "is-net", "Act like a live source",
          0, 1, 0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));   
  /**
   * GstFdSrc:timeout
   *
   * Post a message after timeout microseconds
   *
   * Since: 0.10.21
   */
  g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_TIMEOUT,
      g_param_spec_uint64 ("timeout", "Timeout",
          "Post a message after timeout microseconds (0 = disabled)", 0,
          G_MAXUINT64, DEFAULT_TIMEOUT,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  gstbasesrc_class->start = GST_DEBUG_FUNCPTR (gst_fd_src_start);
  gstbasesrc_class->stop = GST_DEBUG_FUNCPTR (gst_fd_src_stop);
  gstbasesrc_class->unlock = GST_DEBUG_FUNCPTR (gst_fd_src_unlock);
  gstbasesrc_class->unlock_stop = GST_DEBUG_FUNCPTR (gst_fd_src_unlock_stop);
  gstbasesrc_class->is_seekable = GST_DEBUG_FUNCPTR (gst_fd_src_is_seekable);
  gstbasesrc_class->get_size = GST_DEBUG_FUNCPTR (gst_fd_src_get_size);
  gstbasesrc_class->do_seek = GST_DEBUG_FUNCPTR (gst_fd_src_do_seek);
  gstbasesrc_class->query = GST_DEBUG_FUNCPTR (gst_fd_src_query);

  gstpush_src_class->create = GST_DEBUG_FUNCPTR (gst_fd_src_create);
}

static void
gst_fd_src_init (GstFdSrc * fdsrc, GstFdSrcClass * klass)
{
  fdsrc->new_fd = DEFAULT_FD;
  fdsrc->seekable_fd = FALSE;
  fdsrc->fd = -1;
  fdsrc->size = -1;
  fdsrc->timeout = DEFAULT_TIMEOUT;
  fdsrc->uri = g_strdup_printf ("fd://0");
  fdsrc->curoffset = 0;
  fdsrc->isNetfd=0;
}

static void
gst_fd_src_dispose (GObject * obj)
{
  GstFdSrc *src = GST_FD_SRC (obj);

  g_free (src->uri);
  src->uri = NULL;

  G_OBJECT_CLASS (parent_class)->dispose (obj);
}

static void
gst_fd_src_update_fd (GstFdSrc * src, guint64 size)
{
  struct stat stat_results;

  GST_DEBUG_OBJECT (src, "fdset %p, old_fd %d, new_fd %d", src->fdset, src->fd,
      src->new_fd);

  /* we need to always update the fdset since it may not have existed when
   * gst_fd_src_update_fd () was called earlier */
  if (src->fdset != NULL) {
    GstPollFD fd = GST_POLL_FD_INIT;

    if (src->fd >= 0) {
      fd.fd = src->fd;
      /* this will log a harmless warning, if it was never added */
      gst_poll_remove_fd (src->fdset, &fd);
    }

    fd.fd = src->new_fd;
    gst_poll_add_fd (src->fdset, &fd);
    gst_poll_fd_ctl_read (src->fdset, &fd, TRUE);
  }


  if (src->fd != src->new_fd) {
    GST_INFO_OBJECT (src, "Updating to fd %d", src->new_fd);

    src->fd = src->new_fd;

    GST_INFO_OBJECT (src, "Setting size to fd %" G_GUINT64_FORMAT, size);
    src->size = size;

    g_free (src->uri);
    src->uri = g_strdup_printf ("fd://%d", src->fd);
if(src->isNetfd == 0){
    if (fstat (src->fd, &stat_results) < 0)
      goto not_seekable;

    if (!S_ISREG (stat_results.st_mode))
      goto not_seekable;

    /* Try a seek of 0 bytes offset to check for seekability */
    if (lseek (src->fd, 0, SEEK_CUR) < 0)
      goto not_seekable;
}
    GST_INFO_OBJECT (src, "marking fd %d as seekable", src->fd);
    src->seekable_fd = TRUE;

    gst_base_src_set_dynamic_size (GST_BASE_SRC (src), TRUE);
  }
  return;

not_seekable:
  {
    GST_INFO_OBJECT (src, "marking fd %d as NOT seekable", src->fd);
    src->seekable_fd = FALSE;
    gst_base_src_set_dynamic_size (GST_BASE_SRC (src), FALSE);
  }
}

static gboolean
gst_fd_src_start (GstBaseSrc * bsrc)
{
  GstFdSrc *src = GST_FD_SRC (bsrc);

  src->curoffset = 0;

  if ((src->fdset = gst_poll_new (TRUE)) == NULL)
    goto socket_pair;

  gst_fd_src_update_fd (src, -1);

  return TRUE;

  /* ERRORS */
socket_pair:
  {
    GST_ELEMENT_ERROR (src, RESOURCE, OPEN_READ_WRITE, (NULL),
        GST_ERROR_SYSTEM);
    return FALSE;
  }
}

static gboolean
gst_fd_src_stop (GstBaseSrc * bsrc)
{
  GstFdSrc *src = GST_FD_SRC (bsrc);

  if (src->fdset) {
    gst_poll_free (src->fdset);
    src->fdset = NULL;
  }

  return TRUE;
}

static gboolean
gst_fd_src_unlock (GstBaseSrc * bsrc)
{
  GstFdSrc *src = GST_FD_SRC (bsrc);

  GST_LOG_OBJECT (src, "Flushing");
  GST_OBJECT_LOCK (src);
  gst_poll_set_flushing (src->fdset, TRUE);
  GST_OBJECT_UNLOCK (src);

  return TRUE;
}

static gboolean
gst_fd_src_unlock_stop (GstBaseSrc * bsrc)
{
  GstFdSrc *src = GST_FD_SRC (bsrc);

  GST_LOG_OBJECT (src, "No longer flushing");
  GST_OBJECT_LOCK (src);
  gst_poll_set_flushing (src->fdset, FALSE);
  GST_OBJECT_UNLOCK (src);

  return TRUE;
}

static void
gst_fd_src_set_property (GObject * object, guint prop_id, const GValue * value,
    GParamSpec * pspec)
{
  GstFdSrc *src = GST_FD_SRC (object);

  switch (prop_id) {
    case PROP_FD:
      src->new_fd = g_value_get_int (value);

      /* If state is ready or below, update the current fd immediately
       * so it is reflected in get_properties and uri */
      GST_OBJECT_LOCK (object);
      if (GST_STATE (GST_ELEMENT (src)) <= GST_STATE_READY) {
        GST_DEBUG_OBJECT (src, "state ready or lower, updating to use new fd");
        gst_fd_src_update_fd (src, -1);
      } else {
        GST_DEBUG_OBJECT (src, "state above ready, not updating to new fd yet");
      }
      GST_OBJECT_UNLOCK (object);
      break;
    case PROP_TIMEOUT:
      src->timeout = g_value_get_uint64 (value);
      GST_DEBUG_OBJECT (src, "poll timeout set to %" GST_TIME_FORMAT,
          GST_TIME_ARGS (src->timeout));
      break;
      case PROP_NETSOCK_FD:
      	src->isNetfd = g_value_get_int (value);
      	break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_fd_src_get_property (GObject * object, guint prop_id, GValue * value,
    GParamSpec * pspec)
{
  GstFdSrc *src = GST_FD_SRC (object);

  switch (prop_id) {
    case PROP_FD:
      g_value_set_int (value, src->fd);
      break;
    case PROP_TIMEOUT:
      g_value_set_uint64 (value, src->timeout);
      break;
    case PROP_NETSOCK_FD:
      	g_value_set_int (value, src->isNetfd);
      	break;  
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

int CheckIsOOBReceived(int sock_fd)
{
	unsigned long iFlag = 0;
	if (ioctl(sock_fd, SIOCATMARK, &iFlag) != 0) return 0;
    	return iFlag == 1;
}

int IsDataAvailable(int src_fd, unsigned int iTimeout)
{
    struct timeval tv;
    fd_set fds;
    
    FD_ZERO(&fds);
    FD_SET(src_fd, &fds);
    tv.tv_sec = iTimeout;
    tv.tv_usec = 0;
    int iRet = select(src_fd + 1, &fds, NULL, NULL, &tv);
    if (iRet < 0)
    {
        g_print("CSocketClient::IsDataAvailable(): select failed(%d)\n", iRet);
        return 0;
    }
    return iRet > 0;
}
	
static GstFlowReturn
gst_fd_src_create (GstPushSrc * psrc, GstBuffer ** outbuf)
{
  GstFdSrc *src;
  GstBuffer *buf;
  gssize readbytes=0;
  guint blocksize;
  GstClockTime timeout;
  unsigned char SeekPoint[1];
  int temp_readbytes=0;
  unsigned char temp[4096];
  unsigned int iSeqNum;
	unsigned long long iValue;
int reset_data=0;
#ifndef HAVE_WIN32
  gboolean try_again;
  gint retval;
#endif

  src = GST_FD_SRC (psrc);

  if (src->timeout > 0) {
    timeout = src->timeout * GST_USECOND;
  } else {
    timeout = GST_CLOCK_TIME_NONE;
  }

#ifndef HAVE_WIN32
  do {
    try_again = FALSE;

    GST_LOG_OBJECT (src, "doing poll, timeout %" GST_TIME_FORMAT,
        GST_TIME_ARGS (src->timeout));

    retval = gst_poll_wait (src->fdset, timeout);
    GST_LOG_OBJECT (src, "poll returned %d", retval);

    if (G_UNLIKELY (retval == -1)) {
      if (errno == EINTR || errno == EAGAIN) {
        /* retry if interrupted */
        try_again = TRUE;
      } else if (errno == EBUSY) {
        goto stopped;
      } else {
        goto poll_error;
      }
    } else if (G_UNLIKELY (retval == 0)) {
      try_again = TRUE;
      /* timeout, post element message */
      gst_element_post_message (GST_ELEMENT_CAST (src),
          gst_message_new_element (GST_OBJECT_CAST (src),
              gst_structure_new ("GstFdSrcTimeout",
                  "timeout", G_TYPE_UINT64, src->timeout, NULL)));
    }
  } while (G_UNLIKELY (try_again));     /* retry if interrupted or timeout */
#endif

  blocksize = GST_BASE_SRC (src)->blocksize;

  /* create the buffer */
  buf = gst_buffer_try_new_and_alloc (blocksize);
  if (G_UNLIKELY (buf == NULL)) {
    GST_ERROR_OBJECT (src, "Failed to allocate %u bytes", blocksize);
    return GST_FLOW_ERROR;
  }
  
  
	if(src->isNetfd == 1&& isSeek == 1){
ReCheck:		
		if(access("/var/tmp/net/seek_done",R_OK) == 0)
		{
SearchSeek:
		if(!IsDataAvailable(src->fd, 2)){
				MAX_Retry++;
				if(MAX_Retry < 6)
			    		goto SearchSeek;
			    	else
			    		goto eos;
		}else{		
			if(!CheckIsOOBReceived(src->fd)){
				
				do {
					temp_readbytes = read (src->fd, temp, 4096);
				} while (readbytes == -1 && errno == EINTR);  /* retry if interrupted */
				
				if (temp_readbytes < 0){
			    		goto read_error;
				}
			  	if (temp_readbytes == 0){
			    		goto eos;	
			    	}
			    	goto SearchSeek;
			}else
				{
					MAX_Retry=0;
					if(temp_readbytes ==1){
						//g_printf("temp==%02X\n",temp[0]);
					}
					readbytes = read (src->fd, SeekPoint, 1);
					if(SeekPoint[0] == '$'){
						isSeek = 0;
						unlink("/var/tmp/net/seek_done");
						unlink("/var/tmp/net/seek_src");
						
					}else{
						
					}
				
					readbytes = read (src->fd, &iSeqNum, 4);
					readbytes = read (src->fd, &iValue, 8);
					
					do {
						readbytes = read (src->fd, GST_BUFFER_DATA (buf), blocksize);
						GST_LOG_OBJECT (src, "read %" G_GSSIZE_FORMAT, readbytes);
					} while (readbytes == -1 && errno == EINTR);  /* retry if interrupted */
					
					if (readbytes < 0){
				    		goto read_error;
					}
					
				  	if (readbytes == 0)
				    	goto eos;	
					
				}  
			}
		}else{
			goto ReCheck;
		}
	}else{
		
		do {
			readbytes = read (src->fd, GST_BUFFER_DATA (buf), blocksize);
			GST_LOG_OBJECT (src, "read %" G_GSSIZE_FORMAT, readbytes);
		} while (readbytes == -1 && errno == EINTR);  /* retry if interrupted */
			
		if (readbytes < 0){
			goto read_error;
		}
	  	if (readbytes == 0)
	    	goto eos;	
	}
	
GST_BUFFER_OFFSET (buf) = src->curoffset;
GST_BUFFER_SIZE (buf) = readbytes;
GST_BUFFER_TIMESTAMP (buf) = GST_CLOCK_TIME_NONE;
src->curoffset += readbytes;
*outbuf = buf;
  GST_LOG_OBJECT (psrc, "Read buffer of size %" G_GSSIZE_FORMAT, readbytes);
  /* we're done, return the buffer */
  
  return GST_FLOW_OK;

  /* ERRORS */
#ifndef HAVE_WIN32
poll_error:
  {
    GST_ELEMENT_ERROR (src, RESOURCE, READ, (NULL),
        ("poll on file descriptor: %s.", g_strerror (errno)));
    GST_DEBUG_OBJECT (psrc, "Error during poll");
    return GST_FLOW_ERROR;
  }
stopped:
  {
    GST_DEBUG_OBJECT (psrc, "Poll stopped");
    return GST_FLOW_WRONG_STATE;
  }
#endif
eos:
  {
    GST_DEBUG_OBJECT (psrc, "Read 0 bytes. EOS.");
    gst_buffer_unref (buf);
    return GST_FLOW_UNEXPECTED;
  }
read_error:
  {
    GST_ELEMENT_ERROR (src, RESOURCE, READ, (NULL),
        ("read on file descriptor: %s.", g_strerror (errno)));
    GST_DEBUG_OBJECT (psrc, "Error reading from fd");
    gst_buffer_unref (buf);
    return GST_FLOW_ERROR;
  }
}

static gboolean
gst_fd_src_query (GstBaseSrc * basesrc, GstQuery * query)
{
  gboolean ret = FALSE;
  GstFdSrc *src = GST_FD_SRC (basesrc);

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_URI:
      gst_query_set_uri (query, src->uri);
      ret = TRUE;
      break;
    default:
      ret = FALSE;
      break;
  }

  if (!ret)
    ret = GST_BASE_SRC_CLASS (parent_class)->query (basesrc, query);

  return ret;
}

static gboolean
gst_fd_src_is_seekable (GstBaseSrc * bsrc)
{
  GstFdSrc *src = GST_FD_SRC (bsrc);

  return src->seekable_fd;
}

static gboolean
gst_fd_src_get_size (GstBaseSrc * bsrc, guint64 * size)
{
  GstFdSrc *src = GST_FD_SRC (bsrc);
  struct stat stat_results;

  if (src->size != -1) {
    *size = src->size;
    return TRUE;
  }

  if (!src->seekable_fd) {
    /* If it isn't seekable, we won't know the length (but fstat will still
     * succeed, and wrongly say our length is zero. */
    return FALSE;
  }

  if (fstat (src->fd, &stat_results) < 0)
    goto could_not_stat;

  *size = stat_results.st_size;

  return TRUE;

  /* ERROR */
could_not_stat:
  {
    return FALSE;
  }
}

static gboolean
gst_fd_src_do_seek (GstBaseSrc * bsrc, GstSegment * segment)
{
  gint res;
  gint64 offset;
  GstFdSrc *src = GST_FD_SRC (bsrc);
char syscmd[64]={0};
  offset = segment->start;

  /* No need to seek to the current position */
  if (offset == src->curoffset)
    return TRUE;
    
    
    
if(src->isNetfd == 0){
  res = lseek (src->fd, offset, SEEK_SET);
  if (G_UNLIKELY (res < 0 || res != offset))
    goto seek_failed;
}
	src->curoffset = segment->start;
  segment->last_stop = segment->start;
  segment->time = segment->start;
	if (access("/var/tmp/net/seek_src",R_OK) == 0 && src->isNetfd == 1) 
	{  
		//g_print("%s, %d new offset=%lld\n", __FUNCTION__, __LINE__, offset);
		sprintf(syscmd, "%lld", offset);
		fdsrc_write_line_to_file_("/var/tmp/net/seek_offset", 1,syscmd);
		isSeek = 1;
	}

  return TRUE;

seek_failed:
  GST_DEBUG_OBJECT (src, "lseek returned %" G_GINT64_FORMAT, offset);
  return FALSE;
}

/*** GSTURIHANDLER INTERFACE *************************************************/

static GstURIType
gst_fd_src_uri_get_type (void)
{
  return GST_URI_SRC;
}

static gchar **
gst_fd_src_uri_get_protocols (void)
{
  static gchar *protocols[] = { (char *) "fd", NULL };

  return protocols;
}

static const gchar *
gst_fd_src_uri_get_uri (GstURIHandler * handler)
{
  GstFdSrc *src = GST_FD_SRC (handler);

  return src->uri;
}

static gboolean
gst_fd_src_uri_set_uri (GstURIHandler * handler, const gchar * uri)
{
  gchar *protocol, *q;
  GstFdSrc *src = GST_FD_SRC (handler);
  gint fd;
  guint64 size = (guint64) - 1;
guint isNet;
  GST_INFO_OBJECT (src, "checking uri %s", uri);

  protocol = gst_uri_get_protocol (uri);
  if (strcmp (protocol, "fd") != 0) {
    g_free (protocol);
    return FALSE;
  }
  g_free (protocol);

  if (sscanf (uri, "fd://%d", &fd) != 1 || fd < 0)
    return FALSE;

  if ((q = g_strstr_len (uri, -1, "?"))) {
    gchar *sp;

    GST_INFO_OBJECT (src, "found ?");

    if ((sp = g_strstr_len (q, -1, "size="))) {
      if (sscanf (sp, "size=%" G_GUINT64_FORMAT, &size) != 1) {
        GST_INFO_OBJECT (src, "parsing size failed");
        size = -1;
      } else {
        GST_INFO_OBJECT (src, "found size %" G_GUINT64_FORMAT, size);
      }
    }
     if ((sp = g_strstr_len (q, -1, "is-net="))) {
     	if (sscanf (sp, "is-net=%d", &isNet) != 1) {
        GST_INFO_OBJECT (src, "parsing isNet failed");
        isNet = 0;
      } else {
        GST_INFO_OBJECT (src, "found size %d", isNet);
      }
    }
  }

  src->new_fd = fd;
	src->isNetfd = isNet;
  GST_OBJECT_LOCK (src);
  if (GST_STATE (GST_ELEMENT (src)) <= GST_STATE_READY) {
    gst_fd_src_update_fd (src, size);
  }
  GST_OBJECT_UNLOCK (src);

  return TRUE;
}

static void
gst_fd_src_uri_handler_init (gpointer g_iface, gpointer iface_data)
{
  GstURIHandlerInterface *iface = (GstURIHandlerInterface *) g_iface;

  iface->get_type = gst_fd_src_uri_get_type;
  iface->get_protocols = gst_fd_src_uri_get_protocols;
  iface->get_uri = gst_fd_src_uri_get_uri;
  iface->set_uri = gst_fd_src_uri_set_uri;
}
