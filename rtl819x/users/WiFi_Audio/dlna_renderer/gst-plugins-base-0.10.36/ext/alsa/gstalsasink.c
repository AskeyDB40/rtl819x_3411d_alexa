/* GStreamer
 * Copyright (C) 2005 Wim Taymans <wim@fluendo.com>
 * Copyright (C) 2006 Tim-Philipp Muller <tim centricular net>
 *
 * gstalsasink.c:
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
 * SECTION:element-alsasink
 * @see_also: alsasrc, alsamixer
 *
 * This element renders raw audio samples using the ALSA api.
 *
 * <refsect2>
 * <title>Example pipelines</title>
 * |[
 * gst-launch -v filesrc location=sine.ogg ! oggdemux ! vorbisdec ! audioconvert ! audioresample ! alsasink
 * ]| Play an Ogg/Vorbis file.
 * </refsect2>
 *
 * Last reviewed on 2006-03-01 (0.10.4)
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <sys/ioctl.h>
 #include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <alsa/asoundlib.h>

#include "gstalsa.h"
#include "gstalsasink.h"
#include "gstalsadeviceprobe.h"

#include <gst/gst-i18n-plugin.h>
#include "gst/glib-compat-private.h"
#include "wfshm.h"
#define TARGET_AUDIO_SRC_CAPS_FILE "/var/gstreamer-0.10/gstcaps"

#if defined(CONFIG_SND_RTL819XD_SOC_I2S)
#define DEFAULT_DEVICE		"default"
#else
#define DEFAULT_DEVICE		"fmt_conv48_card1_ch1"
#endif


#define DEFAULT_DEVICE_NAME	""
#define DEFAULT_CARD_NAME	""
#define SPDIF_PERIOD_SIZE 1536
#define SPDIF_BUFFER_SIZE 15360

#define DEFAULT_ENABLE_MULTI_ROOM TRUE
#define DEFAULT_THREAD_PRIORITY 99
#define DEFAULT_CHANNEL_TYPE 0
#define DEFAULT_SLAVE_CHANNEL_TYPE 0
#define DEFAULT_SLAVE_VOLUME_MAX 1024
#define DEFAULT_SLAVE_VOLUME_MIN 0
#define DEFAULT_SLAVE_VOLUME DEFAULT_SLAVE_VOLUME_MAX
#define DEFAULT_SLAVE_MUTE FALSE


struct _pcmrate_
{
  int rate;
  int isAvailavle;
};
struct _pcmrate_ _PCM_RATE_[12] = {
	{8000, 0},
	{11025, 0},
	{16000, 0},
	{22050, 0},
	{32000, 0},
	{44100, 0},
	{48000, 0},
	{64000, 0},
	{88200, 0},
	{96000, 0},
	{176400, 0},
	{192000, 0}
};
int num_rate= sizeof(_PCM_RATE_)/sizeof(struct _pcmrate_);
enum
{
  PROP_0,
  PROP_DEVICE,
  PROP_DEVICE_NAME,
  PROP_CARD_NAME,
  PROP_ENABLE_MULTI_ROOM,
  PROP_THREAD_PRIORITY,
  PROP_SLAVE_INFO,
  PROP_CHANNEL_TYPE,
  PROP_SLAVE_CHANNEL_TYPE,
  PROP_SLAVE_VOLUME_MAX,
  PROP_SLAVE_VOLUME_MIN,
  PROP_SLAVE_VOLUME,
  PROP_SLAVE_MUTE,
  PROP_BYPASS_ALSA,
  PROP_LAST
};

struct _PCM_FMTs_
{
	int pcm_type;
	const char *pcm_name;
};
struct _PCM_FMTs_ BE_PCM_FMT[] = {
	{SND_PCM_FORMAT_S16_BE, ""},
	{SND_PCM_FORMAT_U16_BE,""},
	{SND_PCM_FORMAT_S24_BE,""},
	{SND_PCM_FORMAT_U24_BE,""},
	{SND_PCM_FORMAT_S32_BE,""},
	{SND_PCM_FORMAT_U32_BE,""},
	{SND_PCM_FORMAT_S24_3BE,""},
	{SND_PCM_FORMAT_U24_3BE,""}
};
struct _PCM_FMTs_ LE_PCM_FMT[]= {
	{SND_PCM_FORMAT_S16_LE,"audio_fmt_convert16LE"},
	{SND_PCM_FORMAT_U16_LE,"audio_fmt_convertU16LE"},
	{SND_PCM_FORMAT_S24_LE,"audio_fmt_convert24LE"},
	{SND_PCM_FORMAT_U24_LE,"audio_fmt_convertU24LE"},
	{SND_PCM_FORMAT_S32_LE,"audio_fmt_convert32LE"},
	{SND_PCM_FORMAT_U32_LE,"audio_fmt_convertU32LE"},
	{SND_PCM_FORMAT_S24_3LE,"audio_fmt_convert243LE"},
	{SND_PCM_FORMAT_U24_3LE,"audio_fmt_convertU243LE"}
};
static void gst_alsasink_init_interfaces (GType type);
#if defined(MULTI_ROOM_SUPPORT)
GstAudioSinkClass *gstaudiosink_class;
#endif
GST_BOILERPLATE_FULL (GstAlsaSink, gst_alsasink, GstAudioSink,
    GST_TYPE_AUDIO_SINK, gst_alsasink_init_interfaces);

static void gst_alsasink_finalise (GObject * object);
static void gst_alsasink_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_alsasink_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec);

static GstCaps *gst_alsasink_getcaps (GstBaseSink * bsink);

static gboolean gst_alsasink_open (GstAudioSink * asink);
static gboolean gst_alsasink_prepare (GstAudioSink * asink,
    GstRingBufferSpec * spec);
static gboolean gst_alsasink_unprepare (GstAudioSink * asink);
static gboolean gst_alsasink_close (GstAudioSink * asink);
static guint gst_alsasink_write (GstAudioSink * asink, gpointer data,
    guint length);
#if defined(MULTI_ROOM_SUPPORT)
static guint gst_alsasink_write_audio(GstAudioSink * asink, gpointer data,
    guint length);
#endif
static guint gst_alsasink_delay (GstAudioSink * asink);
static void gst_alsasink_reset (GstAudioSink * asink);

//static gint output_ref;         /* 0    */
//static snd_output_t *output;    /* NULL */
//static GStaticMutex output_mutex = G_STATIC_MUTEX_INIT;



#if (G_BYTE_ORDER == G_LITTLE_ENDIAN)
# define ALSA_SINK_FACTORY_ENDIANNESS	"LITTLE_ENDIAN, BIG_ENDIAN"
#else
# define ALSA_SINK_FACTORY_ENDIANNESS	"BIG_ENDIAN, LITTLE_ENDIAN"
#endif

static GstStaticPadTemplate alsasink_sink_factory =
    GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("audio/x-raw-int, "
        "endianness = (int) { " ALSA_SINK_FACTORY_ENDIANNESS " }, "
        "signed = (boolean) { TRUE, FALSE }, "
        "width = (int) 32, "
        "depth = (int) 32, "
        "rate = (int) [ 1, MAX ], " "channels = (int) [ 1, MAX ]; "
        "audio/x-raw-int, "
        "endianness = (int) { " ALSA_SINK_FACTORY_ENDIANNESS " }, "
        "signed = (boolean) { TRUE, FALSE }, "
        "width = (int) 24, "
        "depth = (int) 24, "
        "rate = (int) [ 1, MAX ], " "channels = (int) [ 1, MAX ]; "
        "audio/x-raw-int, "
        "endianness = (int) { " ALSA_SINK_FACTORY_ENDIANNESS " }, "
        "signed = (boolean) { TRUE, FALSE }, "
        "width = (int) 32, "
        "depth = (int) 24, "
        "rate = (int) [ 1, MAX ], " "channels = (int) [ 1, MAX ]; "
        "audio/x-raw-int, "
        "endianness = (int) { " ALSA_SINK_FACTORY_ENDIANNESS " }, "
        "signed = (boolean) { TRUE, FALSE }, "
        "width = (int) 16, "
        "depth = (int) 16, "
        "rate = (int) [ 1, MAX ], " "channels = (int) [ 1, MAX ]; "
        "audio/x-raw-int, "
        "signed = (boolean) { TRUE, FALSE }, "
        "width = (int) 8, "
        "depth = (int) 8, "
        "rate = (int) [ 1, MAX ], " "channels = (int) [ 1, MAX ];"
        "audio/x-iec958")
    );

typedef enum _PLAYER_ALSA_STATE{
	ALSA_REGULAR_WORKING= 0,
	ALSA_TO_CLOSE		= 1,
	ALSA_CLOSE_DONE		= 2,
	ALSA_TO_OPEN		= 3
}PLAYER_ALSA_STATE;

PLAYER_ALSA_STATE Get_AlexaDialogState(void)
{
	unsigned int state=0;

	wfshm_get(WFSHM_AMZ_ALSA_STATE, (void *)&state);

	return state;
}
	
static void
gst_alsasink_finalise (GObject * object)
{
  GstAlsaSink *sink = GST_ALSA_SINK (object);

  g_free (sink->device);
  g_mutex_free (sink->alsa_lock);
#if defined(MULTI_ROOM_SUPPORT)
if (sink->mr_u != NULL)
	multiroom_data_free(sink->mr_u);
#endif

 #if 0 
  g_static_mutex_lock (&output_mutex);
  --output_ref;
  if (output_ref == 0) {
    snd_output_close (output);
    output = NULL;
  }
  g_static_mutex_unlock (&output_mutex);
#endif
  G_OBJECT_CLASS (parent_class)->finalize (object);

}

static void
gst_alsasink_init_interfaces (GType type)
{

  gst_alsa_type_add_device_property_probe_interface (type);
}

static void
gst_alsasink_base_init (gpointer g_class)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (g_class);

  gst_element_class_set_details_simple (element_class,
      "Audio sink (ALSA)", "Sink/Audio",
      "Output to a sound card via ALSA", "Wim Taymans <wim@fluendo.com>");

  gst_element_class_add_static_pad_template (element_class,
      &alsasink_sink_factory);
}

static void
gst_alsasink_class_init (GstAlsaSinkClass * klass)
{
  GObjectClass *gobject_class;
  GstBaseSinkClass *gstbasesink_class;
#if !defined(MULTI_ROOM_SUPPORT)
  GstAudioSinkClass *gstaudiosink_class;
#endif

  gobject_class = (GObjectClass *) klass;
  gstbasesink_class = (GstBaseSinkClass *) klass;
  gstaudiosink_class = (GstAudioSinkClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  gobject_class->finalize = gst_alsasink_finalise;
  gobject_class->get_property = gst_alsasink_get_property;
  gobject_class->set_property = gst_alsasink_set_property;

  gstbasesink_class->get_caps = GST_DEBUG_FUNCPTR (gst_alsasink_getcaps);

  gstaudiosink_class->open = GST_DEBUG_FUNCPTR (gst_alsasink_open);
  gstaudiosink_class->prepare = GST_DEBUG_FUNCPTR (gst_alsasink_prepare);
  gstaudiosink_class->unprepare = GST_DEBUG_FUNCPTR (gst_alsasink_unprepare);
  gstaudiosink_class->close = GST_DEBUG_FUNCPTR (gst_alsasink_close);
  gstaudiosink_class->write = GST_DEBUG_FUNCPTR (gst_alsasink_write);
  gstaudiosink_class->delay = GST_DEBUG_FUNCPTR (gst_alsasink_delay);
  gstaudiosink_class->reset = GST_DEBUG_FUNCPTR (gst_alsasink_reset);

  g_object_class_install_property (gobject_class, PROP_DEVICE,
      g_param_spec_string ("device", "Device",
          "ALSA device, as defined in an asound configuration file",
          DEFAULT_DEVICE, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_DEVICE_NAME,
      g_param_spec_string ("device-name", "Device name",
          "Human-readable name of the sound device", DEFAULT_DEVICE_NAME,
          G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_CARD_NAME,
      g_param_spec_string ("card-name", "Card name",
          "Human-readable name of the sound card", DEFAULT_CARD_NAME,
          G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));

g_object_class_install_property (gobject_class, PROP_BYPASS_ALSA,
      g_param_spec_int ("bypass-alsa", "Bypass ALSA write",
          "skip alsa write while playing", 0, 3,
          0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

     
#if defined(MULTI_ROOM_SUPPORT)
    g_object_class_install_property (gobject_class, PROP_ENABLE_MULTI_ROOM,
      g_param_spec_boolean ("enable-multi-room", "Enable multi-room function",
          "Enable multi-room function to send audio data to remote speakers", DEFAULT_ENABLE_MULTI_ROOM,
          G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));

    g_object_class_install_property (gobject_class, PROP_THREAD_PRIORITY,
      g_param_spec_int ("thread-priority", "Thread priority",
          "The scheduling priority of the main thread", 1, 99,
          DEFAULT_THREAD_PRIORITY,
          G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));


    g_object_class_install_property (gobject_class, PROP_CHANNEL_TYPE,
      g_param_spec_int ("channel-type", "Channel Type",
          "The channel the speaker outputs", -1, 2,
          DEFAULT_CHANNEL_TYPE,
          G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));


    g_object_class_install_property (gobject_class, PROP_SLAVE_VOLUME_MAX,
      g_param_spec_int ("slave-volume-max", "Slave Audio Volume Max",
          "The max volume of slave speakers", 0, 2048,
          DEFAULT_SLAVE_VOLUME_MAX,
          G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));

    g_object_class_install_property (gobject_class, PROP_SLAVE_VOLUME_MIN,
      g_param_spec_int ("slave-volume-min", "Slave Audio Volume Min",
          "The min volume of slave speakers", 0, 2048,
          DEFAULT_SLAVE_VOLUME_MIN,
          G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));

    g_object_class_install_property (gobject_class, PROP_SLAVE_VOLUME,
      g_param_spec_int ("slave-volume", "Slave Audio Volume",
          "The audio volume of slave speakers", 0, 2048,
          DEFAULT_SLAVE_VOLUME,
          G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));

    g_object_class_install_property (gobject_class, PROP_SLAVE_MUTE,
      g_param_spec_boolean ("slave-mute", "Slave Audio Mute",
          "Audio mute of slave speakers", DEFAULT_SLAVE_MUTE,
          G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));
#endif
}

static void
gst_alsasink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstAlsaSink *sink;
  int int_temp;
  int gst_state = -1;
  unsigned int PassALSADone=0;
#if defined(MULTI_ROOM_SUPPORT)
bool bool_temp;
unsigned int uint_temp;
#endif
  sink = GST_ALSA_SINK (object);

  switch (prop_id) {
    case PROP_DEVICE:
      g_free (sink->device);
      sink->device = g_value_dup_string (value);
      /* setting NULL restores the default device */
      if (sink->device == NULL) {
        sink->device = g_strdup (DEFAULT_DEVICE);
      }
      break;
    case PROP_BYPASS_ALSA:
		int_temp = g_value_get_int(value);
		sink->bypassalsa = (guint)int_temp;
		//g_message("%s %d ALSA Sink get bypassalsa:%d",__FUNCTION__,__LINE__, sink->bypassalsa);
		
		if(sink->handle !=NULL){
			//g_message(" %s %d \n",__FUNCTION__, __LINE__);
			gst_state = snd_pcm_state(sink->handle);
			//g_message(" %s %d gst_state:%u\n",__FUNCTION__, __LINE__,gst_state);
			if(gst_state==SND_PCM_STATE_PREPARED ){
				if (sink->bypassalsa == 1 && sink->handle !=NULL) {
					//g_message("!!!!! %s %d close alsa handle\n",__FUNCTION__,__LINE__);
					snd_pcm_drop (sink->handle);
					snd_pcm_close (sink->handle);
					sink->handle = NULL;
					PassALSADone = 1;
					wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
				}
			}
		}
		
		
		break;
#if defined(MULTI_ROOM_SUPPORT)

    case PROP_ENABLE_MULTI_ROOM:
	bool_temp = g_value_get_boolean(value);
	Set_enable_multi_room_mode(sink->mr_u, bool_temp);
        break;

    case PROP_THREAD_PRIORITY:
	int_temp = g_value_get_int(value);
        break;

    case PROP_CHANNEL_TYPE:
	int_temp = g_value_get_int(value);
	Set_multi_room_channelType(sink->mr_u, int_temp);

        break;
    case PROP_SLAVE_VOLUME_MAX:
	int_temp = g_value_get_int(value);
	Set_multi_room_VolumeMax(sink->mr_u, (unsigned int)int_temp);
        break;
    case PROP_SLAVE_VOLUME_MIN:
        int_temp = g_value_get_int(value);
	Set_multi_room_VolumeMin(sink->mr_u, (unsigned int)int_temp);
        break;
    case PROP_SLAVE_VOLUME:
        int_temp = g_value_get_int(value);
	Set_multi_room_Volume(sink->mr_u, (unsigned int)int_temp);
        break;
    case PROP_SLAVE_MUTE:
        bool_temp = g_value_get_boolean(value);
	Set_multi_room_mute(sink->mr_u, bool_temp);
        break;
#endif
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_alsasink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstAlsaSink *sink;

  sink = GST_ALSA_SINK (object);

  switch (prop_id) {
    case PROP_DEVICE:
      g_value_set_string (value, sink->device);
      break;
    case PROP_DEVICE_NAME:
      g_value_take_string (value,
          gst_alsa_find_device_name (GST_OBJECT_CAST (sink),
              sink->device, sink->handle, SND_PCM_STREAM_PLAYBACK));
      break;
    case PROP_CARD_NAME:
      g_value_take_string (value,
          gst_alsa_find_card_name (GST_OBJECT_CAST (sink),
              sink->device, SND_PCM_STREAM_PLAYBACK));
      break;
       case PROP_BYPASS_ALSA:
       //	g_message("%s %d try to get bypassalsa:%u", __FUNCTION__, __LINE__, sink->bypassalsa);
      g_value_set_int (value, (gint)sink->bypassalsa);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_alsasink_init (GstAlsaSink * alsasink, GstAlsaSinkClass * g_class)
{
  GST_DEBUG_OBJECT (alsasink, "initializing alsasink");
  alsasink->device = g_strdup (DEFAULT_DEVICE);
  alsasink->handle = NULL;
  alsasink->cached_caps = NULL;
  alsasink->alsa_lock = g_mutex_new ();

#if defined(MULTI_ROOM_SUPPORT)
	alsasink->mr_u = multiroom_data_init(2, NULL, NULL, NULL);
#endif


#if 0
  g_static_mutex_lock (&output_mutex);
  if (output_ref == 0) {
    snd_output_stdio_attach (&output, stdout, 0);
    ++output_ref;
  }
  g_static_mutex_unlock (&output_mutex);
 #endif 
 //g_message("Exit %s %d\n",__FUNCTION__, __LINE__);

}

#define CHECK(call, error) \
G_STMT_START {                  \
if ((err = call) < 0)           \
  goto error;                   \
} G_STMT_END;

#if defined(CONFIG_RTL_8881A) && defined(CONFIG_SND_RTL819XD_SOC_I2S)
int alsasink_getcapsfromFile(const char *file_name, GstAudioSink * asink);
int alsasink_getcapsfromFile(const char *file_name, GstAudioSink * asink)
{
	FILE *fp;
	int result = -1;
	GstAlsaSink *alsa;
  	gint err;
	int sample_rate, byte_endianness,bit_width,bit_depth;
	int caps_signed, caps_channels;
	
	alsa = GST_ALSA_SINK (asink);
	fp= fopen(file_name, "r");
	if (!fp) {
        	g_debug("can not open:%s\n", file_name);
		return -1;
   	}
   	
	fscanf(fp,"%d %d %d %d %d %d",&sample_rate, &caps_channels, &caps_signed, &byte_endianness, &bit_width, &bit_depth);
	fclose(fp);
	result =1;
	 //g_debug("%d Negotiating to %d channels @ %d Hz (format = %s)\n", __LINE__, alsa->channels, alsa->rate,snd_pcm_format_name (alsa->format));
	//g_debug("%s, %d %d %d %d %d %d %d\n", __FUNCTION__, __LINE__, sample_rate, caps_channels, caps_signed, byte_endianness, bit_width, bit_depth);
	
	if(caps_signed == 1){ //signed
		switch(bit_width)
		{
		case 8:
			alsa->format=SND_PCM_FORMAT_S8;
			break;
		case 16:
			if(byte_endianness ==1)
				alsa->format=SND_PCM_FORMAT_S16_BE;
			else
				alsa->format=SND_PCM_FORMAT_S16_LE;
			break;
		case 24:
			break;
		case 32:
			if(byte_endianness ==1)
				alsa->format=SND_PCM_FORMAT_S32_BE;
			else
				alsa->format=SND_PCM_FORMAT_S32_LE;
			break;
		default:
			break;
		}
		
	}else{  //un-signed
		switch(bit_width)
		{
		case 8:
			alsa->format=SND_PCM_FORMAT_U8;
			break;
		case 16:
			if(byte_endianness ==1)
				alsa->format=SND_PCM_FORMAT_U16_BE;
			else
				alsa->format=SND_PCM_FORMAT_U16_LE;
			break;
		case 24:
			break;
		case 32:
			if(byte_endianness ==1)
				alsa->format=SND_PCM_FORMAT_U32_BE;
			else
				alsa->format=SND_PCM_FORMAT_U32_LE;
			break;
		default:
			break;
		}
	}
	g_free(alsa->device);
#if 0	
	if(sample_rate <= 8000){
		alsa->device = g_strdup ("format_convert08");
	}else
#endif		
	if(sample_rate <= 16000){
		alsa->device = g_strdup ("format_convert16");
	}else if(sample_rate <= 32000){
		alsa->device = g_strdup ("format_convert32");
	}else if(sample_rate <= 44100){
		alsa->device = g_strdup ("format_convert441");
	}else if(sample_rate <= 48000){
		alsa->device = g_strdup ("format_convert48");
	}else if(sample_rate <= 96000){
		alsa->device = g_strdup ("format_convert96");
	}else{
		alsa->device = g_strdup ("format_convert96");
	}
  			
	
	//g_print ("\n<<<<<%s, %d New PCM=%s\n",__FUNCTION__,  __LINE__, alsa->device);
	alsa->rate=sample_rate;
	alsa->channels=caps_channels;
	alsa->bytes_per_sample = bit_width/8;
 //g_print ("%d Negotiating to %d channels @ %d Hz (format = %s)\n", __LINE__, alsa->channels, alsa->rate,snd_pcm_format_name (alsa->format));
	return result;
}
#endif
static GstCaps *
gst_alsasink_getcaps (GstBaseSink * bsink)
{
  GstElementClass *element_class;
  GstPadTemplate *pad_template;
  GstAlsaSink *sink = GST_ALSA_SINK (bsink);
  GstCaps *caps;
  gint err;
  gint i;
  gint EndianOrder=0;
  snd_pcm_hw_params_t *hw_params;
  snd_pcm_format_mask_t *mask;
  char pcm_name[64];
  
  
  if (sink->handle == NULL) {
    GST_DEBUG_OBJECT (sink, "device not open, using template caps");
    return NULL;                /* base class will get template caps for us */
  }

  if (sink->cached_caps) {
    GST_LOG_OBJECT (sink, "Returning cached caps");
    return gst_caps_ref (sink->cached_caps);
  }else {

	snd_pcm_hw_params_malloc (&hw_params);
	if ((err = snd_pcm_hw_params_any (sink->handle, hw_params)) < 0)
    		return NULL;
    	else{
    		snd_pcm_format_mask_malloc (&mask);
  		snd_pcm_hw_params_get_format_mask (hw_params, mask);
    	}
    	for (i = 0; i < G_N_ELEMENTS (_PCM_RATE_); i++){
		if(snd_pcm_hw_params_test_rate(sink->handle, hw_params,_PCM_RATE_[i].rate,0) ==0){
			//g_print("rate %d is available\n", _PCM_RATE_[i].rate);
			_PCM_RATE_[i].isAvailavle =1;
		}else
				_PCM_RATE_[i].isAvailavle =0;
    	}
#if defined(CONFIG_RTL_8881A) && defined(CONFIG_SND_RTL819XD_SOC_I2S)
    	for (i = 0; i < G_N_ELEMENTS (BE_PCM_FMT); i++){
    		 if (snd_pcm_format_mask_test (mask, BE_PCM_FMT[i].pcm_type)) {
        				EndianOrder=BIG_ENDIAN;
        				break;
        		}
    	}
    	if(EndianOrder == 0){
    		i=0;
    		for (i = 0; i < G_N_ELEMENTS (LE_PCM_FMT); i++){
	    		if (snd_pcm_format_mask_test (mask, LE_PCM_FMT[i].pcm_type)) {
	        				EndianOrder=LITTLE_ENDIAN;
	        				sprintf(pcm_name, "%s",LE_PCM_FMT[i].pcm_name);
	        				break;
	        		}
    		}
    	}		
	    	if(EndianOrder == 0){
	    		EndianOrder = G_BYTE_ORDER;
	    	}
	    	if(EndianOrder == LITTLE_ENDIAN){
	    		 if (sink->handle) {
    				snd_pcm_close (sink->handle);
    				sink->handle = NULL;
  			}
  			g_free(sink->device);
  			sink->device = g_strdup (pcm_name);
//  			g_warning("%s, %d,get caps:pcm_name:%s",__FUNCTION__, __LINE__,pcm_name );
  			err = snd_pcm_open (&sink->handle, sink->device, SND_PCM_STREAM_PLAYBACK,SND_PCM_NONBLOCK);
  			if( err< 0){
  				
  				if (err == -EBUSY) {
					g_warning("%d, Could not open audio device for playback. Device is being used by another application.",__LINE__);
					g_warning("%d, Device '%s' is busy", __LINE__, sink->device);          
    				} else {
					g_warning("%d, Could not open audio device for playback.Playback open error on device '%s': %s", __LINE__,sink->device, snd_strerror (err));              
    				}
    				return NULL;
  			}
	    	}
#endif	    	
    	}
  element_class = GST_ELEMENT_GET_CLASS (sink);
  pad_template = gst_element_class_get_pad_template (element_class, "sink");
  g_return_val_if_fail (pad_template != NULL, NULL);
#if defined(CONFIG_RTL_8881A) && defined(CONFIG_SND_RTL819XD_SOC_I2S)
  caps = gst_alsa_probe_supported_formats (GST_OBJECT (sink), sink->handle,
      gst_pad_template_get_caps (pad_template),EndianOrder);
#else
caps = gst_alsa_probe_supported_formats (GST_OBJECT (sink), sink->handle,
      gst_pad_template_get_caps (pad_template));
#endif      
  if (caps) {
    sink->cached_caps = gst_caps_ref (caps);
  }

  GST_INFO_OBJECT (sink, "returning caps %" GST_PTR_FORMAT, caps);
	snd_pcm_format_mask_free (mask);
	snd_pcm_hw_params_free (hw_params);
  return caps;
}

static int
set_hwparams (GstAlsaSink * alsa)
{
  guint rrate;
  gint err;
  snd_pcm_hw_params_t *params;
  guint period_time, buffer_time;
  guint max_buffer_time;
  guint max_period_time, min_period_time;
guint min, max;
snd_pcm_uframes_t buffersize;
snd_pcm_uframes_t min_buffersize, max_buffersize;

  snd_pcm_hw_params_malloc (&params);
// g_print ("%d Negotiating to %d channels @ %d Hz (format = %s)\n", __LINE__, alsa->channels, alsa->rate,snd_pcm_format_name (alsa->format));
  GST_DEBUG_OBJECT (alsa, "Negotiating to %d channels @ %d Hz (format = %s) "
      "SPDIF (%d)", alsa->channels, alsa->rate,
      snd_pcm_format_name (alsa->format), alsa->iec958);

  /* start with requested values, if we cannot configure alsa for those values,
   * we set these values to -1, which will leave the default alsa values */
	if(alsa->period_time < 20000){
        GST_WARNING_OBJECT (alsa, "double period_time(%u) and buffer_time(%u)", alsa->period_time, alsa->buffer_time);
		alsa->buffer_time = alsa->buffer_time*2;
		alsa->period_time = alsa->period_time*2;
	}
	
  buffer_time = alsa->buffer_time;
  period_time = alsa->period_time;

retry:
  /* choose all parameters */
  CHECK (snd_pcm_hw_params_any (alsa->handle, params), no_config);
  /* set the interleaved read/write format */
  CHECK (snd_pcm_hw_params_set_access (alsa->handle, params, alsa->access),
      wrong_access);
  /* set the sample format */
  if (alsa->iec958) {
    /* Try to use big endian first else fallback to le and swap bytes */
    if (snd_pcm_hw_params_set_format (alsa->handle, params, alsa->format) < 0) {
      alsa->format = SND_PCM_FORMAT_S16_LE;
      alsa->need_swap = TRUE;
      GST_DEBUG_OBJECT (alsa, "falling back to little endian with swapping");
    } else {
      alsa->need_swap = FALSE;
    }
  }
  CHECK (snd_pcm_hw_params_set_format (alsa->handle, params, alsa->format),
      no_sample_format);
  /* set the count of channels */
  CHECK (snd_pcm_hw_params_set_channels (alsa->handle, params, alsa->channels),
      no_channels);
  /* set the stream rate */
  rrate = alsa->rate;
  CHECK (snd_pcm_hw_params_set_rate_near (alsa->handle, params, &rrate, NULL),
      no_rate);

//#ifndef GST_DISABLE_GST_DEBUG
  /* get and dump some limits */
  {
    guint min, max;
	
    snd_pcm_hw_params_get_buffer_time_min (params, &min, NULL);
    snd_pcm_hw_params_get_buffer_time_max (params, &max, NULL);

    GST_DEBUG_OBJECT (alsa, "buffer time %u, min %u, max %u",
        alsa->buffer_time, min, max);
	max_buffer_time = max;
//g_message("max_buffer_time=%u, min=%u\n",max_buffer_time,min);
#if defined(CONFIG_RTL_8881A) && defined(CONFIG_SND_RTL819XD_SOC_I2S)        
	if( alsa->rate <= 8000 && buffer_time < 400000 && min < 400000){
  		buffer_time=400000;
	}
#endif	
    snd_pcm_hw_params_get_period_time_min (params, &min, NULL);
    snd_pcm_hw_params_get_period_time_max (params, &max, NULL);

    GST_DEBUG_OBJECT (alsa, "period time %u, min %u, max %u",
        alsa->period_time, min, max);
	max_period_time = max;
	min_period_time = min;
//g_message("max_period_time=%u, min=%u\n",max_period_time, min_period_time);
    snd_pcm_hw_params_get_periods_min (params, &min, NULL);
    snd_pcm_hw_params_get_periods_max (params, &max, NULL);

    GST_DEBUG_OBJECT (alsa, "periods min %u, max %u", min, max);
#if defined(CONFIG_RTL_8881A) && defined(CONFIG_SND_RTL819XD_SOC_I2S)    
     if( alsa->rate <= 8000 && period_time < 100000){
  		period_time=100000;
  	}
#endif  

snd_pcm_hw_params_get_buffer_size_min	(params,&min_buffersize);
snd_pcm_hw_params_get_buffer_size_max(params,&max_buffersize);
//g_message("buffersize min=%lu, max=%lu", min_buffersize, max_buffersize);
  }
//#endif
#if 0
  /* now try to configure the buffer time and period time, if one
   * of those fail, we fall back to the defaults and emit a warning. */
  if (buffer_time != -1 && !alsa->iec958) {
    /* set the buffer time */
#if 0
    if ((err = snd_pcm_hw_params_set_buffer_time_near (alsa->handle, params,
                &buffer_time, NULL)) < 0) {
      GST_ELEMENT_WARNING (alsa, RESOURCE, SETTINGS, (NULL),
          ("Unable to set buffer time %i for playback: %s",
              buffer_time, snd_strerror (err)));
      /* disable buffer_time the next round */
      buffer_time = -1;
      goto retry;
    }
#else
    if ((err = snd_pcm_hw_params_set_buffer_time (alsa->handle, params,
                buffer_time, 0)) < 0) {
      GST_ELEMENT_WARNING (alsa, RESOURCE, SETTINGS, (NULL),
          ("Unable to set buffer time %i for playback: %s",
              buffer_time, snd_strerror (err)));
      /* disable buffer_time the next round */
      buffer_time = -1;
      goto retry;
    }
#endif
    GST_DEBUG_OBJECT (alsa, "buffer time %u", buffer_time);
    alsa->buffer_time = buffer_time;
    
  }
#endif  
  if (period_time != -1 && !alsa->iec958) {
    /* set the period time */
#if 0
    if ((err = snd_pcm_hw_params_set_period_time_near (alsa->handle, params,
                &period_time, NULL)) < 0) {
      GST_ELEMENT_WARNING (alsa, RESOURCE, SETTINGS, (NULL),
          ("Unable to set period time %i for playback: %s",
              period_time, snd_strerror (err)));
      /* disable period_time the next round */
      period_time = -1;
      goto retry;
    }
#else
	if ( min_period_time <= 20000 && 20000 < max_period_time)
		period_time = 20000;
	else
		period_time = min_period_time+5000;
	err = snd_pcm_hw_params_set_period_time_near(alsa->handle, params,&period_time, 0);
	if (err < 0) {
		GST_ELEMENT_WARNING (alsa, RESOURCE, SETTINGS, (NULL),("Unable to set period time %i for playback: %s",period_time, snd_strerror (err)));
	}
#if defined(CONFIG_SND_USB_AUDIO)
	//buffersize = (alsa->rate/1000)*200; //200ms buffer
	buffersize = (alsa->rate*15/1000)*(period_time/1000);//15 period_time
	//printf("gst buffersize:%lu\n",buffersize);
	if (buffersize >= min_buffersize && buffersize <=max_buffersize) { 
	}else {
		buffersize = min_buffersize + (period_time/1000)*10;
	}
	err =  snd_pcm_hw_params_set_buffer_size(alsa->handle, params, buffersize);
	if (err < 0) {
		g_message("%s %d set buffer size fail!", __FUNCTION__, __LINE__);
	}
#endif	
#if 0		
    if ((err = snd_pcm_hw_params_set_period_time (alsa->handle, params,
                period_time, 0)) < 0) {
      GST_ELEMENT_WARNING (alsa, RESOURCE, SETTINGS, (NULL),
          ("Unable to set period time %i for playback: %s",
              period_time, snd_strerror (err)));
      /* disable period_time the next round */
      period_time = -1;
      goto retry;
    }
#endif    
#endif
    GST_DEBUG_OBJECT (alsa, "period time %u", period_time);
    alsa->period_time = period_time;
    snd_pcm_hw_params_get_buffer_time(params,&buffer_time,NULL);
    alsa->buffer_time = buffer_time;
    
  }

  /* Set buffer size and period size manually for SPDIF */
  if (G_UNLIKELY (alsa->iec958)) {
    snd_pcm_uframes_t buffer_size = SPDIF_BUFFER_SIZE;
    snd_pcm_uframes_t period_size = SPDIF_PERIOD_SIZE;

    CHECK (snd_pcm_hw_params_set_buffer_size_near (alsa->handle, params,
            &buffer_size), buffer_size);
    CHECK (snd_pcm_hw_params_set_period_size_near (alsa->handle, params,
            &period_size, NULL), period_size);
  }

  /* write the parameters to device */
  CHECK (snd_pcm_hw_params (alsa->handle, params), set_hw_params);

  /* now get the configured values */
  CHECK (snd_pcm_hw_params_get_buffer_size (params, &alsa->buffer_size),
      buffer_size);
  CHECK (snd_pcm_hw_params_get_period_size (params, &alsa->period_size, NULL),
      period_size);
  snd_pcm_hw_params_get_period_time (params, &period_time, NULL);
  alsa->period_time = period_time;

  GST_DEBUG_OBJECT (alsa, "buffer size %lu, period size %lu, period time %lu", alsa->buffer_size,
      alsa->period_size, alsa->period_time);

  snd_pcm_hw_params_free (params);
  
  return 0;

  /* ERRORS */
no_config:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Broken configuration for playback: no configurations available: %s",
            snd_strerror (err)));
    snd_pcm_hw_params_free (params);
    return err;
  }
wrong_access:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Access type not available for playback: %s", snd_strerror (err)));
    snd_pcm_hw_params_free (params);
    return err;
  }
no_sample_format:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Sample format not available for playback: %s", snd_strerror (err)));
    snd_pcm_hw_params_free (params);
    return err;
  }
no_channels:
  {
    gchar *msg = NULL;

    if ((alsa->channels) == 1)
      msg = g_strdup (_("Could not open device for playback in mono mode."));
    if ((alsa->channels) == 2)
      msg = g_strdup (_("Could not open device for playback in stereo mode."));
    if ((alsa->channels) > 2)
      msg =
          g_strdup_printf (_
          ("Could not open device for playback in %d-channel mode."),
          alsa->channels);
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, ("%s", msg),
        ("%s", snd_strerror (err)));
    g_free (msg);
    snd_pcm_hw_params_free (params);
    return err;
  }
no_rate:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Rate %iHz not available for playback: %s",
            alsa->rate, snd_strerror (err)));
    return err;
  }
buffer_size:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to get buffer size for playback: %s", snd_strerror (err)));
    snd_pcm_hw_params_free (params);
    return err;
  }
period_size:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to get period size for playback: %s", snd_strerror (err)));
    snd_pcm_hw_params_free (params);
    return err;
  }
set_hw_params:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to set hw params for playback: %s", snd_strerror (err)));
    snd_pcm_hw_params_free (params);
    return err;
  }
}

static int
set_swparams (GstAlsaSink * alsa)
{
  int err;
  snd_pcm_sw_params_t *params;
snd_output_t *log;
  snd_pcm_sw_params_malloc (&params);

  /* get the current swparams */
  CHECK (snd_pcm_sw_params_current (alsa->handle, params), no_config);
#if defined(MULTI_ROOM_SUPPORT)  
if (is_enable_multi_room_mode(alsa->mr_u) == FALSE) 
#else
if(1)
#endif
{
 snd_pcm_uframes_t boundary;
  /* start the transfer when the buffer is almost full: */
  /* (buffer_size / avail_min) * avail_min */
  
 
  //g_message("buffer_size=%lu, period_size=%lu", alsa->buffer_size, alsa->period_size);
#if 1 
  CHECK (snd_pcm_sw_params_set_start_threshold (alsa->handle, params,
          (alsa->buffer_size / alsa->period_size) * alsa->period_size),
      start_threshold);
      
  CHECK (snd_pcm_sw_params_get_boundary(params, &boundary), get_boundary);
    //CHECK (snd_pcm_sw_params_set_stop_threshold (alsa->handle, params, boundary), stop_threshold);     
 CHECK (snd_pcm_sw_params_set_stop_threshold (alsa->handle, params, ((alsa->buffer_size / alsa->period_size) * alsa->period_size)*100),  stop_threshold);
 #else
 CHECK (snd_pcm_sw_params_set_start_threshold (alsa->handle, params,(alsa->period_size*10)),start_threshold);
 CHECK (snd_pcm_sw_params_set_stop_threshold (alsa->handle, params,((alsa->period_size*10)*100)),stop_threshold);
 #endif
  }
  else {
		 snd_pcm_uframes_t boundary;

    CHECK (snd_pcm_sw_params_set_start_threshold (alsa->handle, params, 0x7fffffff),
            start_threshold);
   
    CHECK (snd_pcm_sw_params_get_boundary(params, &boundary), get_boundary);
    CHECK (snd_pcm_sw_params_set_stop_threshold (alsa->handle, params, boundary), stop_threshold);
    CHECK (snd_pcm_sw_params_set_silence_threshold(alsa->handle, params, 0), silence_threshold);
    CHECK (snd_pcm_sw_params_set_silence_size(alsa->handle, params, boundary), silence_size);
  }
  /* allow the transfer when at least period_size samples can be processed */
  CHECK (snd_pcm_sw_params_set_avail_min (alsa->handle, params,
          alsa->period_size), set_avail);

#if GST_CHECK_ALSA_VERSION(1,0,16)
  /* snd_pcm_sw_params_set_xfer_align() is deprecated, alignment is always 1 */
#else
  /* align all transfers to 1 sample */
  CHECK (snd_pcm_sw_params_set_xfer_align (alsa->handle, params, 1), set_align);
#endif
 err = snd_output_stdio_attach(&log, stderr, 0);
 
  /* write the parameters to the playback device */
  CHECK (snd_pcm_sw_params (alsa->handle, params), set_sw_params);
//snd_pcm_dump(alsa->handle, log);
  snd_pcm_sw_params_free (params);
  snd_output_close(log);
  return 0;

  /* ERRORS */
no_config:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to determine current swparams for playback: %s",
            snd_strerror (err)));
    snd_pcm_sw_params_free (params);
    return err;
  }
start_threshold:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to set start threshold mode for playback: %s",
            snd_strerror (err)));
    snd_pcm_sw_params_free (params);
    return err;
  }
 stop_threshold:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to set stop threshold mode for playback: %s",
            snd_strerror (err)));
    snd_pcm_sw_params_free (params);
    return err;
  }     
set_avail:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to set avail min for playback: %s", snd_strerror (err)));
    snd_pcm_sw_params_free (params);
    return err;
  }
#if !GST_CHECK_ALSA_VERSION(1,0,16)
set_align:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to set transfer align for playback: %s", snd_strerror (err)));
    snd_pcm_sw_params_free (params);
    return err;
  }
#endif
set_sw_params:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to set sw params for playback: %s", snd_strerror (err)));
    snd_pcm_sw_params_free (params);
    return err;
  }
get_boundary:
  {
      GST_ELEMENT_ERROR(alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to get boundary info for playback: %s", snd_strerror(err)));
      snd_pcm_sw_params_free(params);
      return err;
  }
silence_threshold:
  {
      GST_ELEMENT_ERROR(alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to set silence threshold for playback: %s", snd_strerror(err)));
      snd_pcm_sw_params_free(params);
      return err;
  }
silence_size:
  {
      GST_ELEMENT_ERROR(alsa, RESOURCE, SETTINGS, (NULL),
        ("Unable to set silence size for playback: %s", snd_strerror(err)));
      snd_pcm_sw_params_free(params);
      return err;
  }
}

static gboolean
alsasink_parse_spec (GstAlsaSink * alsa, GstRingBufferSpec * spec)
{
  /* Initialize our boolean */
  alsa->iec958 = FALSE;

  switch (spec->type) {
    case GST_BUFTYPE_LINEAR:
      GST_DEBUG_OBJECT (alsa,
          "Linear format : depth=%d, width=%d, sign=%d, bigend=%d", spec->depth,
          spec->width, spec->sign, spec->bigend);

      alsa->format = snd_pcm_build_linear_format (spec->depth, spec->width,
          spec->sign ? 0 : 1, spec->bigend ? 1 : 0);
      break;
    case GST_BUFTYPE_FLOAT:
      switch (spec->format) {
        case GST_FLOAT32_LE:
          alsa->format = SND_PCM_FORMAT_FLOAT_LE;
          break;
        case GST_FLOAT32_BE:
          alsa->format = SND_PCM_FORMAT_FLOAT_BE;
          break;
        case GST_FLOAT64_LE:
          alsa->format = SND_PCM_FORMAT_FLOAT64_LE;
          break;
        case GST_FLOAT64_BE:
          alsa->format = SND_PCM_FORMAT_FLOAT64_BE;
          break;
        default:
          goto error;
      }
      break;
    case GST_BUFTYPE_A_LAW:
      alsa->format = SND_PCM_FORMAT_A_LAW;
      break;
    case GST_BUFTYPE_MU_LAW:
      alsa->format = SND_PCM_FORMAT_MU_LAW;
      break;
    case GST_BUFTYPE_IEC958:
      alsa->format = SND_PCM_FORMAT_S16_BE;
      alsa->iec958 = TRUE;
      break;
    default:
      goto error;

  }
  alsa->rate = spec->rate;
  alsa->channels = spec->channels;
  alsa->buffer_time = spec->buffer_time;
  alsa->period_time = spec->latency_time;
  alsa->access = SND_PCM_ACCESS_RW_INTERLEAVED;

  return TRUE;

  /* ERRORS */
error:
  {
    return FALSE;
  }
}

static gboolean
gst_alsasink_open (GstAudioSink * asink)
{
  GstAlsaSink *alsa;
  gint err;
  gint alsa_release=0;
  alsa = GST_ALSA_SINK (asink);

	alsa->amz_announce_alsa_state=ALSA_REGULAR_WORKING;

	if(Get_AlexaDialogState()>0){
		//g_message("## %s(%d) RECOG_PROCESS\n",__FUNCTION__,__LINE__);
		alsa->amz_announce_alsa_state = ALSA_CLOSE_DONE;
		
		return TRUE;
	}
  
  /* open in non-blocking mode, we'll use snd_pcm_wait() for space to become
   * available. */
   
  wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
  CHECK (snd_pcm_open (&alsa->handle, alsa->device, SND_PCM_STREAM_PLAYBACK,
          SND_PCM_NONBLOCK), open_error);
  snd_pcm_drop (alsa->handle);
  GST_LOG_OBJECT (alsa, "Opened device %s", alsa->device);
  alsa->bypassalsa=0;
  return TRUE;

  /* ERRORS */
open_error:
  {
    if (err == -EBUSY) {
      GST_ELEMENT_ERROR (alsa, RESOURCE, BUSY,
          (_("Could not open audio device for playback. "
                  "Device is being used by another application.")),
          ("Device '%s' is busy", alsa->device));
g_warning("Could not open audio device for playback. Device is being used by another application.");
g_warning("Device '%s' is busy", alsa->device);          
    } else {
      GST_ELEMENT_ERROR (alsa, RESOURCE, OPEN_WRITE,
          (_("Could not open audio device for playback.")),
          ("Playback open error on device '%s': %s", alsa->device,
              snd_strerror (err)));
g_warning("Could not open audio device for playback.Playback open error on device '%s': %s", alsa->device, snd_strerror (err));              
    }
    return FALSE;
  }
}
#if defined(MULTI_ROOM_SUPPORT)
static void set_audio_format(snd_pcm_format_t format, rtmr_audio_sample_format_t *rtmr_format)
{
	switch (format) {
	case SND_PCM_FORMAT_S8:
        		*rtmr_format = RTMR_SAMPLE_S8;
					break;
        	case SND_PCM_FORMAT_U8:
            	*rtmr_format = RTMR_SAMPLE_U8;
				break;
        	case SND_PCM_FORMAT_S16_LE:
            	*rtmr_format = RTMR_SAMPLE_S16LE;
					break;
        	case SND_PCM_FORMAT_S16_BE:
            	*rtmr_format = RTMR_SAMPLE_S16BE;
					break;
        	case SND_PCM_FORMAT_S32_LE:
            	*rtmr_format = RTMR_SAMPLE_S32LE;
					break;
        	case SND_PCM_FORMAT_S32_BE:
            	*rtmr_format = RTMR_SAMPLE_S32BE;
			break;
	default:
		*rtmr_format = RTMR_SAMPLE_INVALID;
	}
}

#endif

static gboolean
gst_alsasink_prepare (GstAudioSink * asink, GstRingBufferSpec * spec)
{
  GstAlsaSink *alsa;
  gint err;
  gint alsa_release=0;
  unsigned int PassALSADone=0;
  
#if defined(MULTI_ROOM_SUPPORT)
  alsa_parameters_t params; 
  audio_sample_spec_t sample_spec;
#endif
  alsa = GST_ALSA_SINK (asink);
  GST_DEBUG_OBJECT (alsa, "%s", __func__);

	if(Get_AlexaDialogState()>0){
		//printf("## %s(%d) RECOG_PROCESS\n",__FUNCTION__,__LINE__);
		
		if(alsa->handle!=NULL){
			//printf("%d close alsa handle\n",__LINE__);	
			snd_pcm_drop (alsa->handle);
			snd_pcm_close (alsa->handle);
			alsa->handle = NULL;
			alsa_release = 1;
			wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
			alsa->amz_announce_alsa_state = ALSA_CLOSE_DONE;
		}
		
		return TRUE;
	}

	if(alsa->handle==NULL && alsa->amz_announce_alsa_state == ALSA_CLOSE_DONE){
		//printf("## %s(%d) reopen pcm ##\n",__FUNCTION__,__LINE__);
		alsa->amz_announce_alsa_state = ALSA_TO_OPEN;
		alsa_release = 0;
		wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
		err = snd_pcm_open (&alsa->handle, alsa->device, SND_PCM_STREAM_PLAYBACK,SND_PCM_NONBLOCK);
		if( err< 0){
			if (err == -EBUSY) {
				g_warning("%d, Could not open audio device for playback. Device is being used by another application.",__LINE__);
				g_warning("%d, Device '%s' is busy", __LINE__, alsa->device);          
			} else {
				g_warning("%d, Could not open audio device for playback.Playback open error on device '%s': %s", __LINE__,alsa->device, snd_strerror (err));              
			}
			return FALSE;
		}
		snd_pcm_drop (alsa->handle);
		alsa->bypassalsa=0;
		alsa->amz_announce_alsa_state = ALSA_REGULAR_WORKING;
	}
	
  if (spec->format == GST_IEC958) {
    snd_pcm_close (alsa->handle);
    alsa->handle = gst_alsa_open_iec958_pcm (GST_OBJECT (alsa));
    if (G_UNLIKELY (!alsa->handle)) {
      goto no_iec958;
    }
  }

  if (!alsasink_parse_spec (alsa, spec))
    goto spec_parse;
#if defined(CONFIG_RTL_8881A) && defined(CONFIG_SND_RTL819XD_SOC_I2S)
if (access(TARGET_AUDIO_SRC_CAPS_FILE,R_OK) == 0) {	
	snd_pcm_close (alsa->handle);
	alsasink_getcapsfromFile(TARGET_AUDIO_SRC_CAPS_FILE, asink);
	unlink(TARGET_AUDIO_SRC_CAPS_FILE);
	
	err = snd_pcm_open (&alsa->handle, alsa->device, SND_PCM_STREAM_PLAYBACK,SND_PCM_NONBLOCK);
	
	if( err< 0){
		if (err == -EBUSY) {
			g_warning("%d, Could not open audio device for playback. Device is being used by another application.",__LINE__);
			g_warning("%d, Device '%s' is busy", __LINE__, alsa->device);          
		} else {
			g_warning("%d, Could not open audio device for playback.Playback open error on device '%s': %s", __LINE__,alsa->device, snd_strerror (err));              
		}
		return FALSE;
  	}
  	
}
#endif
#if defined(MULTI_ROOM_SUPPORT)
  CHECK (set_hwparams (alsa), hw_params_failed);
  CHECK (set_swparams (alsa), sw_params_failed);
	
  alsa->bytes_per_sample = spec->bytes_per_sample;
  spec->segsize = alsa->period_size * spec->bytes_per_sample;
  spec->segtotal = alsa->buffer_size / alsa->period_size;

	set_audio_format(alsa->format, &sample_spec.format);
	sample_spec.rate = alsa->rate;
	sample_spec.channels = alsa->channels;
	params.period_time = alsa->period_time;
	params.period_size = (unsigned int)alsa->period_size;
	params.vol_min = 0;
	params.vol_max = 1024;
	params.vol =  GetSoundCardVolume(alsa->mr_u);
	update_multiroom_data(alsa->mr_u, alsa->handle, &sample_spec, &params);
	gstaudiosink_class->write = GST_DEBUG_FUNCPTR (gst_alsasink_write_audio);
	snd_pcm_prepare(alsa->handle);
#else
	CHECK (set_hwparams (alsa), hw_params_failed);
	CHECK (set_swparams (alsa), sw_params_failed);
	alsa->bytes_per_sample = spec->bytes_per_sample;
	spec->segsize = alsa->period_size * spec->bytes_per_sample;
	spec->segtotal = alsa->buffer_size / alsa->period_size;
#endif


if(0)
  {
    snd_output_t *out_buf = NULL;
    char *msg = NULL;

    snd_output_buffer_open (&out_buf);
    snd_pcm_dump_hw_setup (alsa->handle, out_buf);
    snd_output_buffer_string (out_buf, &msg);
    GST_DEBUG_OBJECT (alsa, "Hardware setup: \n%s", msg);
     
    snd_output_close (out_buf);
    snd_output_buffer_open (&out_buf);
    snd_pcm_dump_sw_setup (alsa->handle, out_buf);
    snd_output_buffer_string (out_buf, &msg);
    GST_DEBUG_OBJECT (alsa, "Software setup: \n%s", msg);
    
    snd_output_close (out_buf);
  }
#if defined(MULTI_ROOM_SUPPORT)
  set_playback_state(alsa->mr_u, PLAYBACK_PLAYING);
#endif

  return TRUE;

  /* ERRORS */
no_iec958:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, OPEN_WRITE, (NULL),
        ("Could not open IEC958 (SPDIF) device for playback"));
    return FALSE;
  }
spec_parse:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Error parsing spec"));
    return FALSE;
  }
hw_params_failed:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Setting of hwparams failed: %s", snd_strerror (err)));
    return FALSE;
  }
sw_params_failed:
  {
    GST_ELEMENT_ERROR (alsa, RESOURCE, SETTINGS, (NULL),
        ("Setting of swparams failed: %s", snd_strerror (err)));
    return FALSE;
  }
}

static gboolean
gst_alsasink_unprepare (GstAudioSink * asink)
{
  GstAlsaSink *alsa;
  unsigned int PassALSADone=0;
  gint alsa_release=0;
  
  alsa = GST_ALSA_SINK (asink);
  
	if(Get_AlexaDialogState()>0){
		alsa->amz_announce_alsa_state = ALSA_TO_CLOSE;
		if(alsa->handle!=NULL){
			snd_pcm_drop (alsa->handle);
		}
		
		if(alsa->handle!=NULL)
			snd_pcm_hw_free (alsa->handle);
		
		if (alsa->handle) {
			snd_pcm_close (alsa->handle);
			alsa->handle = NULL;
		}
		PassALSADone = 1;
		wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
		alsa->amz_announce_alsa_state = ALSA_CLOSE_DONE;
		
		alsa_release=1;
		wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
		
		return TRUE;
  }

//g_message(" %s %d\n",__FUNCTION__, __LINE__);
	if (alsa->bypassalsa ==0){
		if(alsa->handle!=NULL){
			snd_pcm_drop (alsa->handle);
		}
	}
#if defined(MULTI_ROOM_SUPPORT)
	if (alsa->bypassalsa ==0) {
		suspend_audio_playback_thread(alsa->mr_u);
		unprepare_mr(alsa->mr_u);
	}
	#endif
//g_message("%s bypass alsa",__FUNCTION__);

	if (alsa->bypassalsa ==0){
		if(alsa->handle!=NULL){
			snd_pcm_hw_free (alsa->handle);
		}
	}

 // g_message("Exit %s %d\n",__FUNCTION__, __LINE__);

  return TRUE;
}

static gboolean
gst_alsasink_close (GstAudioSink * asink)
{
  unsigned int PassALSADone=0;
  GstAlsaSink *alsa = GST_ALSA_SINK (asink);
  guint alsa_release=1;
  
  if (alsa->handle) {
    snd_pcm_close (alsa->handle);
    alsa->handle = NULL;
  }
  
  gst_caps_replace (&alsa->cached_caps, NULL);
  
  wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
if (alsa->bypassalsa ==0) {
  
#if (defined(CONFIG_RTL_8197F) || defined(CONFIG_RTL_8881A)) && defined(CONFIG_SND_RTL819XD_SOC_I2S)  
unlink("/var/gstreamer-0.10/input_gstcaps");
unlink("/var/gstreamer-0.10/gstcaps");
unlink("/var/gstreamer-0.10/bypass");
unlink(TARGET_AUDIO_SRC_CAPS_FILE);
#endif  

//g_message("%s",__FUNCTION__);
}else {
//	g_message("%s bypass alsa",__FUNCTION__);
	alsa->bypassalsa =0;
	
}

	alsa->amz_announce_alsa_state=ALSA_REGULAR_WORKING;
  return TRUE;

}


/*
 *   Underrun and suspend recovery
 */
static gint
xrun_recovery (GstAlsaSink * alsa, snd_pcm_t * handle, gint err)
{
  GST_DEBUG_OBJECT (alsa, "xrun recovery %d", err);
  
	g_warning("run recovery %d", err);
  if (err == -EPIPE) {          /* under-run */
    err = snd_pcm_prepare (handle);
    if (err < 0)
      GST_WARNING_OBJECT (alsa,
          "Can't recovery from underrun, prepare failed: %s",
          snd_strerror (err));
    return 0;
  } else if (err == -ESTRPIPE) {
    while ((err = snd_pcm_resume (handle)) == -EAGAIN)
      g_usleep (100);           /* wait until the suspend flag is released */

    if (err < 0) {
      err = snd_pcm_prepare (handle);
      if (err < 0)
        GST_WARNING_OBJECT (alsa,
            "Can't recovery from suspend, prepare failed: %s",
            snd_strerror (err));
    }
    return 0;
  }
  return err;
}
char __attribute__((used)) *LRmixing_s16(const char *inLR_buffer, const size_t size)
{
    char *mixingBuffer = malloc(size * 2 * sizeof(int16_t));
    int32_t L_sample, R_sample, mixing_sample;
    
    int16_t *pSample = (int16_t *)inLR_buffer;
    int16_t *pEnd = pSample + size * 2;
    int16_t *pMixing = (int16_t *)mixingBuffer;
    while (pSample < pEnd) {
        L_sample = *pSample++;
        R_sample = *pSample++;
        mixing_sample = (L_sample + R_sample) / 2L;
        *pMixing++ = (int16_t) mixing_sample;
        *pMixing++ = (int16_t) mixing_sample;
    }
    return mixingBuffer;
}
static guint
gst_alsasink_write (GstAudioSink * asink, gpointer data, guint length)
{
  GstAlsaSink *alsa;
  gint err;
  gint cptr;
  gint alsa_release=0;
  guint ret_value=0;
  snd_pcm_state_t Current_ALSA_St;
  guint max_retry=0;
  unsigned int PassALSADone=0;
  gint16 *ptr = data;
//char *mixing_data = LRmixing_s16(data, length);
//char *ptr_mixied = mixing_data;
//gint16 *ptr = mixing_data;
  alsa = GST_ALSA_SINK (asink);
  snd_pcm_sframes_t avail;

	if(Get_AlexaDialogState()>0 ){
		//printf("## %s(%d) RECOG_PROCESS\n",__FUNCTION__,__LINE__);
		
		if(alsa->handle!=NULL && alsa->amz_announce_alsa_state == ALSA_REGULAR_WORKING){
			alsa->amz_announce_alsa_state = ALSA_TO_CLOSE;
			//printf("%d close alsa handle\n",__LINE__);
			snd_pcm_drop (alsa->handle);
			snd_pcm_close (alsa->handle);
			alsa->handle = NULL;
			PassALSADone = 1;
			wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
			alsa_release=1;
			wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
			alsa->amz_announce_alsa_state = ALSA_CLOSE_DONE;
		}
		usleep(alsa->period_time);
		
		return length;
	}

	if(alsa->handle==NULL && alsa->amz_announce_alsa_state == ALSA_CLOSE_DONE){
		alsa->amz_announce_alsa_state = ALSA_TO_OPEN;

		alsa_release=0;
		wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
		err = snd_pcm_open (&alsa->handle, alsa->device, SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK);
		if (err ==0) {
			set_hwparams (alsa);
			set_swparams (alsa);
			snd_pcm_drop (alsa->handle);
			snd_pcm_prepare(alsa->handle);
		}else
			g_message("open pcm error: %d", err);
		
		PassALSADone = 1;
		wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
		
		usleep(alsa->period_time);
		
		return length;
	}
  
	if (alsa->amz_announce_alsa_state == ALSA_TO_OPEN && alsa->handle != NULL && snd_pcm_state(alsa->handle) == SND_PCM_STATE_PREPARED) {
		//printf("Reset bypassalsa!\n");
		alsa->bypassalsa= 0;
		PassALSADone = 0;
		wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
		alsa->amz_announce_alsa_state = ALSA_REGULAR_WORKING;
		
		usleep(alsa->period_time);
		
		return length;
	}
  
  
  if (alsa->iec958 && alsa->need_swap) {
    guint i;

    GST_DEBUG_OBJECT (asink, "swapping bytes");
    for (i = 0; i < length / 2; i++) {
      ptr[i] = GUINT16_SWAP_LE_BE (ptr[i]);
    }
  }

  GST_LOG_OBJECT (asink, "received audio samples buffer of %u bytes", length);

  cptr = length / alsa->bytes_per_sample;
#if 0
	if (alsa->bypassalsa >0) {
		 GST_ALSA_SINK_LOCK (asink);
		if (alsa->bypassalsa ==1 && alsa->handle !=NULL) {
			//printf("%d close alsa handle\n",__LINE__);
			snd_pcm_drop (alsa->handle);
			snd_pcm_close (alsa->handle);
			alsa->handle = NULL;
			PassALSADone = 1;
			wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
		} else if (alsa->bypassalsa ==1 && alsa->handle ==NULL) {
			alsa->bypassalsa =2;
		} else {
			if (alsa->bypassalsa ==3 && alsa->handle ==NULL) {
				int open_ret=0;
				//g_message("Should Start recover %s\n",alsa->device);
				
				open_ret = snd_pcm_open (&alsa->handle, alsa->device, SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK);
				if (open_ret ==0) {
					set_hwparams (alsa);
					set_swparams (alsa);
					snd_pcm_drop (alsa->handle);
					snd_pcm_prepare(alsa->handle);
				}else
					g_message("open pcm error: %d", open_ret);
				PassALSADone = 1;
				wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
			}else {
			}	
		}
		
		usleep(alsa->period_time);
		
		if (alsa->bypassalsa ==3 && alsa->handle != NULL && snd_pcm_state(alsa->handle) == SND_PCM_STATE_PREPARED) {
			//printf("Reset bypassalsa!\n");
			alsa->bypassalsa= 0;
		}
		GST_ALSA_SINK_UNLOCK (asink);
		//if (mixing_data != data) free(mixing_data);
		//g_message(" AB %u\n", length);
		
		return length;
		
	}else {
	}
#endif
	//g_message(" %s %d\n",__FUNCTION__, __LINE__);
	GST_ALSA_SINK_LOCK (asink);
	alsa->inalsa_write =1;
	
	while (cptr > 0) {
		/* start by doing a blocking wait for free space. Set the timeout
		* to 4 times the period time */
		err = snd_pcm_wait (alsa->handle, (4 * alsa->period_time / 1000));
		if (err < 0) {
			GST_DEBUG_OBJECT (asink, "wait error, %d", err);
		} else {
			
			/* get available size in ALSA ring buffer for write */
			if ((avail = snd_pcm_avail_update(alsa->handle)) < 0) {
				continue;
			}

			if (avail < alsa->period_size) {
				//printf("available frame %ld < %lu\n", avail, alsa->period_size);
				usleep(1000);
				continue;
			}
			
			err = snd_pcm_writei (alsa->handle, ptr, cptr);
		}
		
		
		GST_LOG_OBJECT (asink, "written %d frames out of %d", err, cptr);
		if (err < 0) {
			GST_DEBUG_OBJECT (asink, "Write error: %s", snd_strerror (err));
			g_message("Write error: %s", snd_strerror (err));
			if (err == -EAGAIN) {
				Current_ALSA_St = snd_pcm_state(alsa->handle);
				g_message("SND ST:%d",Current_ALSA_St);
				max_retry++;
				if (max_retry < 30)
						continue;
					else {
						gint next_err;
						g_message("SND ST reinit SND");
						snd_pcm_drop (alsa->handle);
						snd_pcm_close (alsa->handle);
						usleep(100000);
						snd_pcm_open (&alsa->handle, alsa->device, SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK);
						set_hwparams (alsa);
						set_swparams (alsa);
						next_err = snd_pcm_prepare(alsa->handle);
						if (next_err<0) {
							g_message("next_err=%s",snd_strerror (next_err));
						}
						max_retry = 0;
						goto write_error;
					}
					
			} else if (xrun_recovery (alsa, alsa->handle, err) < 0) {
				goto write_error;
			}
			goto write_error;
		}

		ptr += snd_pcm_frames_to_bytes (alsa->handle, err);
		cptr -= err;
	}

#if defined(MULTI_ROOM_SUPPORT)  
	if (!is_enable_multi_room_ABrunning(alsa->mr_u) && snd_pcm_state(alsa->handle) == SND_PCM_STATE_PREPARED)
	{
      if (snd_pcm_avail_update(alsa->handle) < alsa->period_size) {
          if ((err = snd_pcm_start(alsa->handle)) < 0) {
              GST_ERROR_OBJECT(alsa, "trigger alsa start error: %s", snd_strerror(err));
          } else {
              GST_DEBUG_OBJECT(alsa, "trigger alsa start...");
          }
      }
  }
#endif 
  GST_ALSA_SINK_UNLOCK (asink);
  
	//if (mixing_data != data) free(mixing_data);
	ret_value = (length - (cptr * alsa->bytes_per_sample));
	//printf("ALSA Write:%u, length=%u\n", ret_value, length);
	 alsa->inalsa_write =0;
	 //printf("ALSA Write:%u\n", ret_value);
	// g_message("A Write:%u",ret_value);
  return ret_value;

write_error:
  {
    GST_ALSA_SINK_UNLOCK (asink);
    //g_message("%s %d write_error", __FUNCTION__, __LINE__);
    alsa->inalsa_write =0;
    //if (mixing_data != data) free(mixing_data);
    return length;              /* skip one period */
  }
}

static guint
gst_alsasink_delay (GstAudioSink * asink)
{
  GstAlsaSink *alsa;
  snd_pcm_sframes_t delay;
  int res;
  gint err;
  gint alsa_release=0;
  guint ret_buffersize=0;
  unsigned int PassALSADone=0;
  
  alsa = GST_ALSA_SINK (asink);
  
  ///g_message(" %s %d\n",__FUNCTION__, __LINE__);
	if(Get_AlexaDialogState()>0){
		
		if(alsa->handle!=NULL && alsa->amz_announce_alsa_state == ALSA_REGULAR_WORKING){
			alsa->amz_announce_alsa_state = ALSA_TO_CLOSE;
			//printf("%d close alsa handle\n",__LINE__);
			snd_pcm_drop (alsa->handle);
			snd_pcm_close (alsa->handle);
			alsa->handle = NULL;
			PassALSADone = 1;
			wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
			alsa_release=1;
			wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
			alsa->amz_announce_alsa_state = ALSA_CLOSE_DONE;
		}
		
		if(alsa->amz_announce_alsa_state>0)
		{
			if(alsa->amz_announce_alsa_state == ALSA_TO_CLOSE || alsa->amz_announce_alsa_state == ALSA_CLOSE_DONE){
				ret_buffersize = (guint)alsa->buffer_size;
				//printf("ret_buffersize=%u\n",ret_buffersize);
				return ret_buffersize;
			}else if(alsa->amz_announce_alsa_state == ALSA_TO_OPEN){
				if (alsa->handle != NULL){
					//printf("alsa handle is ready!\n");
				}else {
					ret_buffersize = (guint)alsa->buffer_size;
					return ret_buffersize;
				}
			}
		}
	}

	if(alsa->handle == NULL){
		ret_buffersize = (guint)alsa->buffer_size;
		return ret_buffersize;
	}
  
#if 0
	if (alsa->bypassalsa > 0) {
		if (alsa->bypassalsa ==1 || alsa->bypassalsa ==2) {
			ret_buffersize = (guint)alsa->buffer_size;
			//printf("ret_buffersize=%u\n",ret_buffersize);
			return ret_buffersize;
		}else if (alsa->bypassalsa ==3){
			if (alsa->handle != NULL){
				//printf("alsa handle is ready!\n");
			}else {
				ret_buffersize = (guint)alsa->buffer_size;
				return ret_buffersize;
			}
		}
	}
#endif
	
  res = snd_pcm_delay (alsa->handle, &delay);
  if (G_UNLIKELY (res < 0)) {
    /* on errors, report 0 delay */
    GST_LOG_OBJECT (alsa, "snd_pcm_delay returned %d", res);
    delay = 0;
  }
  if (G_UNLIKELY (delay < 0)) {
    /* make sure we never return a negative delay */
    GST_LOG_OBJECT (alsa, "snd_pcm_delay returned negative delay");
    delay = 0;
  }

  return delay;
}

static void
gst_alsasink_reset (GstAudioSink * asink)
{
  GstAlsaSink *alsa;
  gint err;
gint i;
  alsa = GST_ALSA_SINK (asink);
  GST_DEBUG_OBJECT(alsa, "%s", __func__);
  
  
if (alsa->bypassalsa >0) {
	//g_message(" %s %d bypassalsa\n",__FUNCTION__, __LINE__);
	return;
}

#if 0
	if (is_enable_multi_room_mode(alsa->mr_u)) {
		reset_mr((void *)alsa->mr_u);
		return;
	}else
	{
		GST_ALSA_SINK_LOCK (asink);
  		GST_DEBUG_OBJECT (alsa, "drop");
  		CHECK (snd_pcm_drop (alsa->handle), drop_error);
  		GST_DEBUG_OBJECT (alsa, "prepare");
  		CHECK (snd_pcm_prepare (alsa->handle), prepare_error);
  		GST_DEBUG_OBJECT (alsa, "reset done");
  		GST_ALSA_SINK_UNLOCK (asink);
  	return;

	  /* ERRORS */
	drop_error:
	{
		GST_ERROR_OBJECT (alsa, "alsa-reset: pcm drop error: %s",snd_strerror (err));
		GST_ALSA_SINK_UNLOCK (asink);
        return;
    }
	prepare_error:
	{
		GST_ERROR_OBJECT (alsa, "alsa-reset: pcm prepare error: %s",snd_strerror (err));
		GST_ALSA_SINK_UNLOCK (asink);
	    return;
    }
    }
#else
  GST_ALSA_SINK_LOCK (asink);
  GST_DEBUG_OBJECT (alsa, "drop");
  if(alsa->handle)
	CHECK (snd_pcm_drop (alsa->handle), drop_error);
  GST_DEBUG_OBJECT (alsa, "prepare");
  if(alsa->handle)
	CHECK (snd_pcm_prepare (alsa->handle), prepare_error);
  GST_DEBUG_OBJECT (alsa, "reset done");
  GST_ALSA_SINK_UNLOCK (asink);
  return;

  /* ERRORS */
drop_error:
  {
    GST_ERROR_OBJECT (alsa, "alsa-reset: pcm drop error: %s",
        snd_strerror (err));
    GST_ALSA_SINK_UNLOCK (asink);
    return;
  }
prepare_error:
  {
    GST_ERROR_OBJECT (alsa, "alsa-reset: pcm prepare error: %s",
        snd_strerror (err));
    GST_ALSA_SINK_UNLOCK (asink);
    return;
  }
#endif	

    }
#if defined(MULTI_ROOM_SUPPORT)
static guint
gst_alsasink_write_audio (GstAudioSink * asink, gpointer data, guint length)
{
	gint err;
	gchar *ptr;
	gint period_bytes;
	gint write_bytes;
	unsigned int PassALSADone=0;
	alsa_parameters_t params; 
  	audio_sample_spec_t sample_spec;
  	gint alsa_release=0;
	GstAlsaSink *alsa = GST_ALSA_SINK (asink);
    /**
     * If audio_playback_thread is not started, call the original write function. 
     */
	if (!is_enable_multi_room_mode(alsa->mr_u) && !is_enable_multi_room_ABrunning(alsa->mr_u)) {
		if (is_enable_multi_room_rejoin(alsa->mr_u)) {
			usleep(20000);
			return length;
		} else {
			return gst_alsasink_write(asink, data, length);
		}
	}
    if (Get_AlexaDialogState()>0 ){
    	if(alsa->handle!=NULL && alsa->amz_announce_alsa_state == ALSA_REGULAR_WORKING){
			alsa->amz_announce_alsa_state = ALSA_TO_CLOSE;
//			printf("%d will close alsa handle\n",__LINE__);
			bypass_alsa_mrA((void *)alsa->mr_u);
			snd_pcm_close (alsa->handle);
			alsa->handle = NULL;
			PassALSADone = 1;
			wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
			alsa_release=1;
			wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
			alsa->amz_announce_alsa_state = ALSA_CLOSE_DONE;
			bypass_alsa_mrB((void *)alsa->mr_u);
		}
		usleep(alsa->period_time);
		return length;
	}
	if(alsa->handle==NULL && alsa->amz_announce_alsa_state == ALSA_CLOSE_DONE){
		alsa->amz_announce_alsa_state = ALSA_TO_OPEN;
		alsa_release=0;
		wfshm_set(WFSHM_ALSA_RELEASE, (void *)&alsa_release);
		
		err = snd_pcm_open (&alsa->handle, alsa->device, SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK);
		if (err ==0) {
			set_hwparams (alsa);
			set_swparams (alsa);
			set_audio_format(alsa->format, &sample_spec.format);
			sample_spec.rate = alsa->rate;
			sample_spec.channels = alsa->channels;
			params.period_time = alsa->period_time;
			params.period_size = (unsigned int)alsa->period_size;
			params.vol_min = 0;
			params.vol_max = 1024;
			params.vol =  GetSoundCardVolume(alsa->mr_u);
			update_multiroom_data(alsa->mr_u, alsa->handle, &sample_spec, &params);
			snd_pcm_drop (alsa->handle);
			snd_pcm_prepare(alsa->handle);
		}else
			g_message("open pcm error: %d", err);
		
		PassALSADone = 1;
		wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
		
		usleep(alsa->period_time);
		
		return length;
	}
	if (alsa->amz_announce_alsa_state == ALSA_TO_OPEN && alsa->handle != NULL && snd_pcm_state(alsa->handle) == SND_PCM_STATE_PREPARED) {
		//printf("Reset bypassalsa!\n");
		alsa->bypassalsa= 0;
		PassALSADone = 0;
		wfshm_set(WFSHM_BYPASS_ALSA_DONE, (void *)&PassALSADone);
		alsa->amz_announce_alsa_state = ALSA_REGULAR_WORKING;
		
		usleep(alsa->period_time);
		
		return length;
	}
	
	
	 write_audio(alsa->mr_u, (const uint8_t*) data, length, 0);

	return length;	 

}
#endif


