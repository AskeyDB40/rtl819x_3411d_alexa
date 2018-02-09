/* rygel-mediathek-playlist-parser.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-mediathek-playlist-parser.vala, do not modify */

/*
 * Copyright (C) 2011 Jens Georg
 *
 * Author: Jens Georg <mail@jensge.org>
 *
 * This file is part of Rygel.
 *
 * Rygel is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Rygel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gee.h>
#include <libsoup/soup.h>
#include <gio/gio.h>


#define RYGEL_MEDIATHEK_TYPE_PLAYLIST_PARSER (rygel_mediathek_playlist_parser_get_type ())
#define RYGEL_MEDIATHEK_PLAYLIST_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIATHEK_TYPE_PLAYLIST_PARSER, RygelMediathekPlaylistParser))
#define RYGEL_MEDIATHEK_PLAYLIST_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIATHEK_TYPE_PLAYLIST_PARSER, RygelMediathekPlaylistParserClass))
#define RYGEL_MEDIATHEK_IS_PLAYLIST_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIATHEK_TYPE_PLAYLIST_PARSER))
#define RYGEL_MEDIATHEK_IS_PLAYLIST_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIATHEK_TYPE_PLAYLIST_PARSER))
#define RYGEL_MEDIATHEK_PLAYLIST_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIATHEK_TYPE_PLAYLIST_PARSER, RygelMediathekPlaylistParserClass))

typedef struct _RygelMediathekPlaylistParser RygelMediathekPlaylistParser;
typedef struct _RygelMediathekPlaylistParserClass RygelMediathekPlaylistParserClass;
typedef struct _RygelMediathekPlaylistParserPrivate RygelMediathekPlaylistParserPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
typedef struct _Block1Data Block1Data;
typedef struct _RygelMediathekPlaylistParserParseData RygelMediathekPlaylistParserParseData;

typedef enum  {
	RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_XML_PARSE_ERROR,
	RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_NETWORK_ERROR
} RygelMediathekVideoItemError;
#define RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR rygel_mediathek_video_item_error_quark ()
struct _RygelMediathekPlaylistParser {
	GObject parent_instance;
	RygelMediathekPlaylistParserPrivate * priv;
};

struct _RygelMediathekPlaylistParserClass {
	GObjectClass parent_class;
	GeeList* (*parse_playlist) (RygelMediathekPlaylistParser* self, const gchar* data, gint length, GError** error);
};

struct _RygelMediathekPlaylistParserPrivate {
	SoupSession* _session;
	gchar* _playlist_suffix;
	gchar* _mime_type;
};

struct _Block1Data {
	int _ref_count_;
	RygelMediathekPlaylistParser * self;
	GSourceFunc callback;
	gpointer callback_target;
	GDestroyNotify callback_target_destroy_notify;
	gpointer _async_data_;
};

struct _RygelMediathekPlaylistParserParseData {
	int _state_;
	GObject* _source_object_;
	GAsyncResult* _res_;
	GSimpleAsyncResult* _async_result;
	RygelMediathekPlaylistParser* self;
	gchar* uri;
	GeeList* result;
	Block1Data* _data1_;
	const gchar* _tmp0_;
	SoupMessage* _tmp1_;
	SoupMessage* message;
	SoupSession* _tmp2_;
	SoupMessage* _tmp3_;
	SoupMessage* _tmp4_;
	SoupMessage* _tmp5_;
	guint _tmp6_;
	guint _tmp7_;
	SoupMessage* _tmp8_;
	guint _tmp9_;
	guint _tmp10_;
	SoupMessage* _tmp11_;
	guint _tmp12_;
	guint _tmp13_;
	const gchar* _tmp14_;
	GError* _tmp15_;
	SoupMessage* _tmp16_;
	SoupMessageBody* _tmp17_;
	guint8* _tmp18_;
	gint _tmp18__length1;
	SoupMessage* _tmp19_;
	SoupMessageBody* _tmp20_;
	gint64 _tmp21_;
	GeeList* _tmp22_;
	GeeList* _tmp23_;
	GError * _inner_error_;
};


static gpointer rygel_mediathek_playlist_parser_parent_class = NULL;

GType rygel_mediathek_playlist_parser_get_type (void) G_GNUC_CONST;
GQuark rygel_mediathek_video_item_error_quark (void);
#define RYGEL_MEDIATHEK_PLAYLIST_PARSER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_MEDIATHEK_TYPE_PLAYLIST_PARSER, RygelMediathekPlaylistParserPrivate))
enum  {
	RYGEL_MEDIATHEK_PLAYLIST_PARSER_DUMMY_PROPERTY,
	RYGEL_MEDIATHEK_PLAYLIST_PARSER_SESSION,
	RYGEL_MEDIATHEK_PLAYLIST_PARSER_PLAYLIST_SUFFIX,
	RYGEL_MEDIATHEK_PLAYLIST_PARSER_MIME_TYPE
};
static void rygel_mediathek_playlist_parser_parse_data_free (gpointer _data);
void rygel_mediathek_playlist_parser_parse (RygelMediathekPlaylistParser* self, const gchar* uri, GAsyncReadyCallback _callback_, gpointer _user_data_);
GeeList* rygel_mediathek_playlist_parser_parse_finish (RygelMediathekPlaylistParser* self, GAsyncResult* _res_, GError** error);
static gboolean rygel_mediathek_playlist_parser_parse_co (RygelMediathekPlaylistParserParseData* _data_);
static Block1Data* block1_data_ref (Block1Data* _data1_);
static void block1_data_unref (void * _userdata_);
static gboolean _rygel_mediathek_playlist_parser_parse_co_gsource_func (gpointer self);
SoupSession* rygel_mediathek_playlist_parser_get_session (RygelMediathekPlaylistParser* self);
static void __lambda2_ (Block1Data* _data1_);
static void ___lambda2__soup_session_callback (SoupSession* session, SoupMessage* msg, gpointer self);
GeeList* rygel_mediathek_playlist_parser_parse_playlist (RygelMediathekPlaylistParser* self, const gchar* data, gint length, GError** error);
static GeeList* rygel_mediathek_playlist_parser_real_parse_playlist (RygelMediathekPlaylistParser* self, const gchar* data, gint length, GError** error);
RygelMediathekPlaylistParser* rygel_mediathek_playlist_parser_construct (GType object_type);
static void rygel_mediathek_playlist_parser_set_session (RygelMediathekPlaylistParser* self, SoupSession* value);
const gchar* rygel_mediathek_playlist_parser_get_playlist_suffix (RygelMediathekPlaylistParser* self);
static void rygel_mediathek_playlist_parser_set_playlist_suffix (RygelMediathekPlaylistParser* self, const gchar* value);
const gchar* rygel_mediathek_playlist_parser_get_mime_type (RygelMediathekPlaylistParser* self);
static void rygel_mediathek_playlist_parser_set_mime_type (RygelMediathekPlaylistParser* self, const gchar* value);
static void rygel_mediathek_playlist_parser_finalize (GObject* obj);
static void _vala_rygel_mediathek_playlist_parser_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _vala_rygel_mediathek_playlist_parser_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);


static void rygel_mediathek_playlist_parser_parse_data_free (gpointer _data) {
	RygelMediathekPlaylistParserParseData* _data_;
	_data_ = _data;
	_g_free0 (_data_->uri);
	_g_object_unref0 (_data_->result);
	_g_object_unref0 (_data_->self);
	g_slice_free (RygelMediathekPlaylistParserParseData, _data_);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


void rygel_mediathek_playlist_parser_parse (RygelMediathekPlaylistParser* self, const gchar* uri, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	RygelMediathekPlaylistParserParseData* _data_;
	RygelMediathekPlaylistParser* _tmp0_;
	const gchar* _tmp1_;
	gchar* _tmp2_;
	_data_ = g_slice_new0 (RygelMediathekPlaylistParserParseData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, rygel_mediathek_playlist_parser_parse);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, rygel_mediathek_playlist_parser_parse_data_free);
	_tmp0_ = _g_object_ref0 (self);
	_data_->self = _tmp0_;
	_tmp1_ = uri;
	_tmp2_ = g_strdup (_tmp1_);
	_data_->uri = _tmp2_;
	rygel_mediathek_playlist_parser_parse_co (_data_);
}


GeeList* rygel_mediathek_playlist_parser_parse_finish (RygelMediathekPlaylistParser* self, GAsyncResult* _res_, GError** error) {
	GeeList* result;
	RygelMediathekPlaylistParserParseData* _data_;
	if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (_res_), error)) {
		return NULL;
	}
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
	result = _data_->result;
	_data_->result = NULL;
	return result;
}


static Block1Data* block1_data_ref (Block1Data* _data1_) {
	g_atomic_int_inc (&_data1_->_ref_count_);
	return _data1_;
}


static void block1_data_unref (void * _userdata_) {
	Block1Data* _data1_;
	_data1_ = (Block1Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data1_->_ref_count_)) {
		RygelMediathekPlaylistParser * self;
		self = _data1_->self;
		(_data1_->callback_target_destroy_notify == NULL) ? NULL : (_data1_->callback_target_destroy_notify (_data1_->callback_target), NULL);
		_data1_->callback = NULL;
		_data1_->callback_target = NULL;
		_data1_->callback_target_destroy_notify = NULL;
		_g_object_unref0 (self);
		g_slice_free (Block1Data, _data1_);
	}
}


static gboolean _rygel_mediathek_playlist_parser_parse_co_gsource_func (gpointer self) {
	gboolean result;
	result = rygel_mediathek_playlist_parser_parse_co (self);
	return result;
}


static void __lambda2_ (Block1Data* _data1_) {
	RygelMediathekPlaylistParser * self;
	GSourceFunc _tmp0_;
	void* _tmp0__target;
	self = _data1_->self;
	_tmp0_ = _data1_->callback;
	_tmp0__target = _data1_->callback_target;
	_tmp0_ (_tmp0__target);
}


static void ___lambda2__soup_session_callback (SoupSession* session, SoupMessage* msg, gpointer self) {
	__lambda2_ (self);
}


static gboolean rygel_mediathek_playlist_parser_parse_co (RygelMediathekPlaylistParserParseData* _data_) {
	switch (_data_->_state_) {
		case 0:
		goto _state_0;
		case 1:
		goto _state_1;
		default:
		g_assert_not_reached ();
	}
	_state_0:
	_data_->_data1_ = g_slice_new0 (Block1Data);
	_data_->_data1_->_ref_count_ = 1;
	_data_->_data1_->self = g_object_ref (_data_->self);
	_data_->_data1_->_async_data_ = _data_;
	_data_->_tmp0_ = _data_->uri;
	_data_->_tmp1_ = soup_message_new ("GET", _data_->_tmp0_);
	_data_->message = _data_->_tmp1_;
	_data_->_data1_->callback = _rygel_mediathek_playlist_parser_parse_co_gsource_func;
	_data_->_data1_->callback_target = _data_;
	_data_->_data1_->callback_target_destroy_notify = NULL;
	_data_->_tmp2_ = _data_->self->priv->_session;
	_data_->_tmp3_ = _data_->message;
	_data_->_tmp4_ = _g_object_ref0 (_data_->_tmp3_);
	soup_session_queue_message (_data_->_tmp2_, _data_->_tmp4_, ___lambda2__soup_session_callback, _data_->_data1_);
	_data_->_state_ = 1;
	return FALSE;
	_state_1:
	;
	_data_->_tmp5_ = _data_->message;
	_data_->_tmp6_ = 0U;
	g_object_get (_data_->_tmp5_, "status-code", &_data_->_tmp6_, NULL);
	_data_->_tmp7_ = _data_->_tmp6_;
	if (_data_->_tmp7_ != ((guint) 200)) {
		_data_->_tmp8_ = _data_->message;
		_data_->_tmp9_ = 0U;
		g_object_get (_data_->_tmp8_, "status-code", &_data_->_tmp9_, NULL);
		_data_->_tmp10_ = _data_->_tmp9_;
		_data_->_tmp11_ = _data_->message;
		_data_->_tmp12_ = 0U;
		g_object_get (_data_->_tmp11_, "status-code", &_data_->_tmp12_, NULL);
		_data_->_tmp13_ = _data_->_tmp12_;
		_data_->_tmp14_ = NULL;
		_data_->_tmp14_ = soup_status_get_phrase (_data_->_tmp13_);
		_data_->_tmp15_ = g_error_new (RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR, RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR_NETWORK_ERROR, "Playlist download failed: %u (%s)", _data_->_tmp10_, _data_->_tmp14_);
		_data_->_inner_error_ = _data_->_tmp15_;
		if (_data_->_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
			g_simple_async_result_set_from_error (_data_->_async_result, _data_->_inner_error_);
			g_error_free (_data_->_inner_error_);
			_g_object_unref0 (_data_->message);
			block1_data_unref (_data_->_data1_);
			_data_->_data1_ = NULL;
			if (_data_->_state_ == 0) {
				g_simple_async_result_complete_in_idle (_data_->_async_result);
			} else {
				g_simple_async_result_complete (_data_->_async_result);
			}
			g_object_unref (_data_->_async_result);
			return FALSE;
		} else {
			_g_object_unref0 (_data_->message);
			block1_data_unref (_data_->_data1_);
			_data_->_data1_ = NULL;
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _data_->_inner_error_->message, g_quark_to_string (_data_->_inner_error_->domain), _data_->_inner_error_->code);
			g_clear_error (&_data_->_inner_error_);
			return FALSE;
		}
	}
	_data_->_tmp16_ = _data_->message;
	_data_->_tmp17_ = _data_->_tmp16_->response_body;
	_data_->_tmp18_ = _data_->_tmp17_->data;
	_data_->_tmp18__length1 = (gint) _data_->_tmp17_->length;
	_data_->_tmp19_ = _data_->message;
	_data_->_tmp20_ = _data_->_tmp19_->response_body;
	_data_->_tmp21_ = _data_->_tmp20_->length;
	_data_->_tmp22_ = NULL;
	_data_->_tmp22_ = rygel_mediathek_playlist_parser_parse_playlist (_data_->self, (const gchar*) _data_->_tmp18_, (gint) _data_->_tmp21_, &_data_->_inner_error_);
	_data_->_tmp23_ = _data_->_tmp22_;
	if (_data_->_inner_error_ != NULL) {
		if (_data_->_inner_error_->domain == RYGEL_MEDIATHEK_VIDEO_ITEM_ERROR) {
			g_simple_async_result_set_from_error (_data_->_async_result, _data_->_inner_error_);
			g_error_free (_data_->_inner_error_);
			_g_object_unref0 (_data_->message);
			block1_data_unref (_data_->_data1_);
			_data_->_data1_ = NULL;
			if (_data_->_state_ == 0) {
				g_simple_async_result_complete_in_idle (_data_->_async_result);
			} else {
				g_simple_async_result_complete (_data_->_async_result);
			}
			g_object_unref (_data_->_async_result);
			return FALSE;
		} else {
			_g_object_unref0 (_data_->message);
			block1_data_unref (_data_->_data1_);
			_data_->_data1_ = NULL;
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _data_->_inner_error_->message, g_quark_to_string (_data_->_inner_error_->domain), _data_->_inner_error_->code);
			g_clear_error (&_data_->_inner_error_);
			return FALSE;
		}
	}
	_data_->result = _data_->_tmp23_;
	_g_object_unref0 (_data_->message);
	block1_data_unref (_data_->_data1_);
	_data_->_data1_ = NULL;
	if (_data_->_state_ == 0) {
		g_simple_async_result_complete_in_idle (_data_->_async_result);
	} else {
		g_simple_async_result_complete (_data_->_async_result);
	}
	g_object_unref (_data_->_async_result);
	return FALSE;
	_g_object_unref0 (_data_->message);
	block1_data_unref (_data_->_data1_);
	_data_->_data1_ = NULL;
	if (_data_->_state_ == 0) {
		g_simple_async_result_complete_in_idle (_data_->_async_result);
	} else {
		g_simple_async_result_complete (_data_->_async_result);
	}
	g_object_unref (_data_->_async_result);
	return FALSE;
}


static GeeList* rygel_mediathek_playlist_parser_real_parse_playlist (RygelMediathekPlaylistParser* self, const gchar* data, gint length, GError** error) {
	g_critical ("Type `%s' does not implement abstract method `rygel_mediathek_playlist_parser_parse_playlist'", g_type_name (G_TYPE_FROM_INSTANCE (self)));
	return NULL;
}


GeeList* rygel_mediathek_playlist_parser_parse_playlist (RygelMediathekPlaylistParser* self, const gchar* data, gint length, GError** error) {
	g_return_val_if_fail (self != NULL, NULL);
	return RYGEL_MEDIATHEK_PLAYLIST_PARSER_GET_CLASS (self)->parse_playlist (self, data, length, error);
}


RygelMediathekPlaylistParser* rygel_mediathek_playlist_parser_construct (GType object_type) {
	RygelMediathekPlaylistParser * self = NULL;
	self = (RygelMediathekPlaylistParser*) g_object_new (object_type, NULL);
	return self;
}


SoupSession* rygel_mediathek_playlist_parser_get_session (RygelMediathekPlaylistParser* self) {
	SoupSession* result;
	SoupSession* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_session;
	result = _tmp0_;
	return result;
}


static void rygel_mediathek_playlist_parser_set_session (RygelMediathekPlaylistParser* self, SoupSession* value) {
	SoupSession* _tmp0_;
	SoupSession* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->priv->_session);
	self->priv->_session = _tmp1_;
	g_object_notify ((GObject *) self, "session");
}


const gchar* rygel_mediathek_playlist_parser_get_playlist_suffix (RygelMediathekPlaylistParser* self) {
	const gchar* result;
	const gchar* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_playlist_suffix;
	result = _tmp0_;
	return result;
}


static void rygel_mediathek_playlist_parser_set_playlist_suffix (RygelMediathekPlaylistParser* self, const gchar* value) {
	const gchar* _tmp0_;
	gchar* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->_playlist_suffix);
	self->priv->_playlist_suffix = _tmp1_;
	g_object_notify ((GObject *) self, "playlist-suffix");
}


const gchar* rygel_mediathek_playlist_parser_get_mime_type (RygelMediathekPlaylistParser* self) {
	const gchar* result;
	const gchar* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_mime_type;
	result = _tmp0_;
	return result;
}


static void rygel_mediathek_playlist_parser_set_mime_type (RygelMediathekPlaylistParser* self, const gchar* value) {
	const gchar* _tmp0_;
	gchar* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->_mime_type);
	self->priv->_mime_type = _tmp1_;
	g_object_notify ((GObject *) self, "mime-type");
}


static void rygel_mediathek_playlist_parser_class_init (RygelMediathekPlaylistParserClass * klass) {
	rygel_mediathek_playlist_parser_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMediathekPlaylistParserPrivate));
	RYGEL_MEDIATHEK_PLAYLIST_PARSER_CLASS (klass)->parse_playlist = rygel_mediathek_playlist_parser_real_parse_playlist;
	G_OBJECT_CLASS (klass)->get_property = _vala_rygel_mediathek_playlist_parser_get_property;
	G_OBJECT_CLASS (klass)->set_property = _vala_rygel_mediathek_playlist_parser_set_property;
	G_OBJECT_CLASS (klass)->finalize = rygel_mediathek_playlist_parser_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_MEDIATHEK_PLAYLIST_PARSER_SESSION, g_param_spec_object ("session", "session", "session", soup_session_get_type (), G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_MEDIATHEK_PLAYLIST_PARSER_PLAYLIST_SUFFIX, g_param_spec_string ("playlist-suffix", "playlist-suffix", "playlist-suffix", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_MEDIATHEK_PLAYLIST_PARSER_MIME_TYPE, g_param_spec_string ("mime-type", "mime-type", "mime-type", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
}


static void rygel_mediathek_playlist_parser_instance_init (RygelMediathekPlaylistParser * self) {
	self->priv = RYGEL_MEDIATHEK_PLAYLIST_PARSER_GET_PRIVATE (self);
}


static void rygel_mediathek_playlist_parser_finalize (GObject* obj) {
	RygelMediathekPlaylistParser * self;
	self = RYGEL_MEDIATHEK_PLAYLIST_PARSER (obj);
	_g_object_unref0 (self->priv->_session);
	_g_free0 (self->priv->_playlist_suffix);
	_g_free0 (self->priv->_mime_type);
	G_OBJECT_CLASS (rygel_mediathek_playlist_parser_parent_class)->finalize (obj);
}


GType rygel_mediathek_playlist_parser_get_type (void) {
	static volatile gsize rygel_mediathek_playlist_parser_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_mediathek_playlist_parser_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediathekPlaylistParserClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mediathek_playlist_parser_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediathekPlaylistParser), 0, (GInstanceInitFunc) rygel_mediathek_playlist_parser_instance_init, NULL };
		GType rygel_mediathek_playlist_parser_type_id;
		rygel_mediathek_playlist_parser_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelMediathekPlaylistParser", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
		g_once_init_leave (&rygel_mediathek_playlist_parser_type_id__volatile, rygel_mediathek_playlist_parser_type_id);
	}
	return rygel_mediathek_playlist_parser_type_id__volatile;
}


static void _vala_rygel_mediathek_playlist_parser_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	RygelMediathekPlaylistParser * self;
	self = RYGEL_MEDIATHEK_PLAYLIST_PARSER (object);
	switch (property_id) {
		case RYGEL_MEDIATHEK_PLAYLIST_PARSER_SESSION:
		g_value_set_object (value, rygel_mediathek_playlist_parser_get_session (self));
		break;
		case RYGEL_MEDIATHEK_PLAYLIST_PARSER_PLAYLIST_SUFFIX:
		g_value_set_string (value, rygel_mediathek_playlist_parser_get_playlist_suffix (self));
		break;
		case RYGEL_MEDIATHEK_PLAYLIST_PARSER_MIME_TYPE:
		g_value_set_string (value, rygel_mediathek_playlist_parser_get_mime_type (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_rygel_mediathek_playlist_parser_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	RygelMediathekPlaylistParser * self;
	self = RYGEL_MEDIATHEK_PLAYLIST_PARSER (object);
	switch (property_id) {
		case RYGEL_MEDIATHEK_PLAYLIST_PARSER_SESSION:
		rygel_mediathek_playlist_parser_set_session (self, g_value_get_object (value));
		break;
		case RYGEL_MEDIATHEK_PLAYLIST_PARSER_PLAYLIST_SUFFIX:
		rygel_mediathek_playlist_parser_set_playlist_suffix (self, g_value_get_string (value));
		break;
		case RYGEL_MEDIATHEK_PLAYLIST_PARSER_MIME_TYPE:
		rygel_mediathek_playlist_parser_set_mime_type (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


