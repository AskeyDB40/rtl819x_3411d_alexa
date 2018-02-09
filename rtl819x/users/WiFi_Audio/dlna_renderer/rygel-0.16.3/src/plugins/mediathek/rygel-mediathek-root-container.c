/* rygel-mediathek-root-container.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-mediathek-root-container.vala, do not modify */

/*
 * Copyright (C) 2009-2011 Jens Georg
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
#include <rygel-server.h>
#include <libsoup/soup.h>
#include <gee.h>
#include <rygel-core.h>
#include <gio/gio.h>


#define RYGEL_MEDIATHEK_TYPE_ROOT_CONTAINER (rygel_mediathek_root_container_get_type ())
#define RYGEL_MEDIATHEK_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIATHEK_TYPE_ROOT_CONTAINER, RygelMediathekRootContainer))
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIATHEK_TYPE_ROOT_CONTAINER, RygelMediathekRootContainerClass))
#define RYGEL_MEDIATHEK_IS_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIATHEK_TYPE_ROOT_CONTAINER))
#define RYGEL_MEDIATHEK_IS_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIATHEK_TYPE_ROOT_CONTAINER))
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIATHEK_TYPE_ROOT_CONTAINER, RygelMediathekRootContainerClass))

typedef struct _RygelMediathekRootContainer RygelMediathekRootContainer;
typedef struct _RygelMediathekRootContainerClass RygelMediathekRootContainerClass;
typedef struct _RygelMediathekRootContainerPrivate RygelMediathekRootContainerPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

#define RYGEL_MEDIATHEK_TYPE_RSS_CONTAINER (rygel_mediathek_rss_container_get_type ())
#define RYGEL_MEDIATHEK_RSS_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIATHEK_TYPE_RSS_CONTAINER, RygelMediathekRssContainer))
#define RYGEL_MEDIATHEK_RSS_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIATHEK_TYPE_RSS_CONTAINER, RygelMediathekRssContainerClass))
#define RYGEL_MEDIATHEK_IS_RSS_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIATHEK_TYPE_RSS_CONTAINER))
#define RYGEL_MEDIATHEK_IS_RSS_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIATHEK_TYPE_RSS_CONTAINER))
#define RYGEL_MEDIATHEK_RSS_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIATHEK_TYPE_RSS_CONTAINER, RygelMediathekRssContainerClass))

typedef struct _RygelMediathekRssContainer RygelMediathekRssContainer;
typedef struct _RygelMediathekRssContainerClass RygelMediathekRssContainerClass;

struct _RygelMediathekRootContainer {
	RygelSimpleContainer parent_instance;
	RygelMediathekRootContainerPrivate * priv;
};

struct _RygelMediathekRootContainerClass {
	RygelSimpleContainerClass parent_class;
};

struct _RygelMediathekRootContainerPrivate {
	SoupSessionAsync* session;
};


static gpointer rygel_mediathek_root_container_parent_class = NULL;
static RygelMediathekRootContainer* rygel_mediathek_root_container_instance;
static RygelMediathekRootContainer* rygel_mediathek_root_container_instance = NULL;
static gint rygel_mediathek_root_container_DEFAULT_UPDATE_INTERVAL;
static gint rygel_mediathek_root_container_DEFAULT_UPDATE_INTERVAL = 1800;

GType rygel_mediathek_root_container_get_type (void) G_GNUC_CONST;
#define RYGEL_MEDIATHEK_ROOT_CONTAINER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_MEDIATHEK_TYPE_ROOT_CONTAINER, RygelMediathekRootContainerPrivate))
enum  {
	RYGEL_MEDIATHEK_ROOT_CONTAINER_DUMMY_PROPERTY
};
RygelMediathekRootContainer* rygel_mediathek_root_container_get_instance (void);
static RygelMediathekRootContainer* rygel_mediathek_root_container_new (void);
static RygelMediathekRootContainer* rygel_mediathek_root_container_construct (GType object_type);
static void rygel_mediathek_root_container_init (RygelMediathekRootContainer* self);
SoupSessionAsync* rygel_mediathek_root_container_get_default_session (void);
RygelMediathekRssContainer* rygel_mediathek_rss_container_new (RygelMediaContainer* parent, guint id);
RygelMediathekRssContainer* rygel_mediathek_rss_container_construct (GType object_type, RygelMediaContainer* parent, guint id);
GType rygel_mediathek_rss_container_get_type (void) G_GNUC_CONST;
static gboolean __lambda4_ (RygelMediathekRootContainer* self);
void rygel_mediathek_rss_container_update (RygelMediathekRssContainer* self, GAsyncReadyCallback _callback_, gpointer _user_data_);
void rygel_mediathek_rss_container_update_finish (RygelMediathekRssContainer* self, GAsyncResult* _res_);
static gboolean ___lambda4__gsource_func (gpointer self);
static void rygel_mediathek_root_container_finalize (GObject* obj);


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


RygelMediathekRootContainer* rygel_mediathek_root_container_get_instance (void) {
	RygelMediathekRootContainer* result = NULL;
	RygelMediathekRootContainer* _tmp0_;
	RygelMediathekRootContainer* _tmp3_;
	RygelMediathekRootContainer* _tmp4_;
	_tmp0_ = rygel_mediathek_root_container_instance;
	if (_tmp0_ == NULL) {
		RygelMediathekRootContainer* _tmp1_;
		RygelMediathekRootContainer* _tmp2_;
		_tmp1_ = rygel_mediathek_root_container_new ();
		_g_object_unref0 (rygel_mediathek_root_container_instance);
		rygel_mediathek_root_container_instance = _tmp1_;
		_tmp2_ = rygel_mediathek_root_container_instance;
		rygel_mediathek_root_container_init (_tmp2_);
	}
	_tmp3_ = rygel_mediathek_root_container_instance;
	_tmp4_ = _g_object_ref0 (_tmp3_);
	result = _tmp4_;
	return result;
}


SoupSessionAsync* rygel_mediathek_root_container_get_default_session (void) {
	SoupSessionAsync* result = NULL;
	RygelMediathekRootContainer* _tmp0_ = NULL;
	RygelMediathekRootContainer* _tmp1_;
	SoupSessionAsync* _tmp2_;
	SoupSessionAsync* _tmp3_;
	SoupSessionAsync* _tmp4_;
	_tmp0_ = rygel_mediathek_root_container_get_instance ();
	_tmp1_ = _tmp0_;
	_tmp2_ = _tmp1_->priv->session;
	_tmp3_ = _g_object_ref0 (_tmp2_);
	_tmp4_ = _tmp3_;
	_g_object_unref0 (_tmp1_);
	result = _tmp4_;
	return result;
}


static RygelMediathekRootContainer* rygel_mediathek_root_container_construct (GType object_type) {
	RygelMediathekRootContainer * self = NULL;
	SoupSessionAsync* _tmp0_;
	self = (RygelMediathekRootContainer*) rygel_simple_container_construct_root (object_type, "ZDF Mediathek");
	_tmp0_ = (SoupSessionAsync*) soup_session_async_new ();
	_g_object_unref0 (self->priv->session);
	self->priv->session = _tmp0_;
	return self;
}


static RygelMediathekRootContainer* rygel_mediathek_root_container_new (void) {
	return rygel_mediathek_root_container_construct (RYGEL_MEDIATHEK_TYPE_ROOT_CONTAINER);
}


static gboolean __lambda4_ (RygelMediathekRootContainer* self) {
	gboolean result = FALSE;
	{
		RygelMediaObjects* _tmp0_;
		RygelMediaObjects* _tmp1_;
		RygelMediaObjects* _child_list;
		RygelMediaObjects* _tmp2_;
		gint _tmp3_;
		gint _tmp4_;
		gint _child_size;
		gint _child_index;
		_tmp0_ = ((RygelSimpleContainer*) self)->children;
		_tmp1_ = _g_object_ref0 (_tmp0_);
		_child_list = _tmp1_;
		_tmp2_ = _child_list;
		_tmp3_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp2_);
		_tmp4_ = _tmp3_;
		_child_size = _tmp4_;
		_child_index = -1;
		while (TRUE) {
			gint _tmp5_;
			gint _tmp6_;
			gint _tmp7_;
			RygelMediaObjects* _tmp8_;
			gint _tmp9_;
			gpointer _tmp10_ = NULL;
			RygelMediaObject* child;
			RygelMediaObject* _tmp11_;
			RygelMediathekRssContainer* _tmp12_;
			RygelMediathekRssContainer* container;
			RygelMediathekRssContainer* _tmp13_;
			_tmp5_ = _child_index;
			_child_index = _tmp5_ + 1;
			_tmp6_ = _child_index;
			_tmp7_ = _child_size;
			if (!(_tmp6_ < _tmp7_)) {
				break;
			}
			_tmp8_ = _child_list;
			_tmp9_ = _child_index;
			_tmp10_ = gee_abstract_list_get ((GeeAbstractList*) _tmp8_, _tmp9_);
			child = (RygelMediaObject*) _tmp10_;
			_tmp11_ = child;
			_tmp12_ = _g_object_ref0 (RYGEL_MEDIATHEK_IS_RSS_CONTAINER (_tmp11_) ? ((RygelMediathekRssContainer*) _tmp11_) : NULL);
			container = _tmp12_;
			_tmp13_ = container;
			rygel_mediathek_rss_container_update (_tmp13_, NULL, NULL);
			_g_object_unref0 (container);
			_g_object_unref0 (child);
		}
		_g_object_unref0 (_child_list);
	}
	result = TRUE;
	return result;
}


static gboolean ___lambda4__gsource_func (gpointer self) {
	gboolean result;
	result = __lambda4_ (self);
	return result;
}


static void rygel_mediathek_root_container_init (RygelMediathekRootContainer* self) {
	GeeArrayList* feeds;
	gint _tmp0_;
	gint update_interval;
	RygelMetaConfig* _tmp1_ = NULL;
	RygelMetaConfig* config;
	GeeArrayList* _tmp5_;
	gint _tmp6_;
	gint _tmp7_;
	gint _tmp27_;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	feeds = NULL;
	_tmp0_ = rygel_mediathek_root_container_DEFAULT_UPDATE_INTERVAL;
	update_interval = _tmp0_;
	_tmp1_ = rygel_meta_config_get_default ();
	config = _tmp1_;
	{
		GeeArrayList* _tmp2_ = NULL;
		GeeArrayList* _tmp3_;
		_tmp2_ = rygel_configuration_get_int_list ((RygelConfiguration*) config, "ZDFMediathek", "rss", &_inner_error_);
		_tmp3_ = _tmp2_;
		if (_inner_error_ != NULL) {
			goto __catch3_g_error;
		}
		_g_object_unref0 (feeds);
		feeds = _tmp3_;
	}
	goto __finally3;
	__catch3_g_error:
	{
		GError* _error_ = NULL;
		GeeArrayList* _tmp4_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		_tmp4_ = gee_array_list_new (G_TYPE_INT, NULL, NULL, NULL);
		_g_object_unref0 (feeds);
		feeds = _tmp4_;
		_g_error_free0 (_error_);
	}
	__finally3:
	if (_inner_error_ != NULL) {
		_g_object_unref0 (config);
		_g_object_unref0 (feeds);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp5_ = feeds;
	_tmp6_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp5_);
	_tmp7_ = _tmp6_;
	if (_tmp7_ == 0) {
		GeeArrayList* _tmp8_;
		g_message ("rygel-mediathek-root-container.vala:61: Could not get RSS from configu" \
"ration, using defaults");
		_tmp8_ = feeds;
		gee_abstract_collection_add ((GeeAbstractCollection*) _tmp8_, GINT_TO_POINTER (508));
	}
	{
		gint _tmp9_;
		gint _tmp10_ = 0;
		gint _tmp11_;
		_tmp9_ = G_MAXINT;
		_tmp10_ = rygel_configuration_get_int ((RygelConfiguration*) config, "ZDFMediathek", "update-interval", 600, _tmp9_, &_inner_error_);
		_tmp11_ = _tmp10_;
		if (_inner_error_ != NULL) {
			goto __catch4_g_error;
		}
		update_interval = _tmp11_;
	}
	goto __finally4;
	__catch4_g_error:
	{
		GError* _error_ = NULL;
		gint _tmp12_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		_tmp12_ = rygel_mediathek_root_container_DEFAULT_UPDATE_INTERVAL;
		update_interval = _tmp12_;
		_g_error_free0 (_error_);
	}
	__finally4:
	if (_inner_error_ != NULL) {
		_g_object_unref0 (config);
		_g_object_unref0 (feeds);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	{
		GeeArrayList* _tmp13_;
		GeeArrayList* _tmp14_;
		GeeArrayList* _id_list;
		GeeArrayList* _tmp15_;
		gint _tmp16_;
		gint _tmp17_;
		gint _id_size;
		gint _id_index;
		_tmp13_ = feeds;
		_tmp14_ = _g_object_ref0 (_tmp13_);
		_id_list = _tmp14_;
		_tmp15_ = _id_list;
		_tmp16_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp15_);
		_tmp17_ = _tmp16_;
		_id_size = _tmp17_;
		_id_index = -1;
		while (TRUE) {
			gint _tmp18_;
			gint _tmp19_;
			gint _tmp20_;
			GeeArrayList* _tmp21_;
			gint _tmp22_;
			gpointer _tmp23_ = NULL;
			gint id;
			gint _tmp24_;
			RygelMediathekRssContainer* _tmp25_;
			RygelMediathekRssContainer* _tmp26_;
			_tmp18_ = _id_index;
			_id_index = _tmp18_ + 1;
			_tmp19_ = _id_index;
			_tmp20_ = _id_size;
			if (!(_tmp19_ < _tmp20_)) {
				break;
			}
			_tmp21_ = _id_list;
			_tmp22_ = _id_index;
			_tmp23_ = gee_abstract_list_get ((GeeAbstractList*) _tmp21_, _tmp22_);
			id = GPOINTER_TO_INT (_tmp23_);
			_tmp24_ = id;
			_tmp25_ = rygel_mediathek_rss_container_new ((RygelMediaContainer*) self, (guint) _tmp24_);
			_tmp26_ = _tmp25_;
			rygel_simple_container_add_child_container ((RygelSimpleContainer*) self, (RygelMediaContainer*) _tmp26_);
			_g_object_unref0 (_tmp26_);
		}
		_g_object_unref0 (_id_list);
	}
	_tmp27_ = update_interval;
	g_timeout_add_seconds_full (G_PRIORITY_DEFAULT, (guint) _tmp27_, ___lambda4__gsource_func, g_object_ref (self), g_object_unref);
	_g_object_unref0 (config);
	_g_object_unref0 (feeds);
}


static void rygel_mediathek_root_container_class_init (RygelMediathekRootContainerClass * klass) {
	rygel_mediathek_root_container_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMediathekRootContainerPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_mediathek_root_container_finalize;
}


static void rygel_mediathek_root_container_instance_init (RygelMediathekRootContainer * self) {
	self->priv = RYGEL_MEDIATHEK_ROOT_CONTAINER_GET_PRIVATE (self);
}


static void rygel_mediathek_root_container_finalize (GObject* obj) {
	RygelMediathekRootContainer * self;
	self = RYGEL_MEDIATHEK_ROOT_CONTAINER (obj);
	_g_object_unref0 (self->priv->session);
	G_OBJECT_CLASS (rygel_mediathek_root_container_parent_class)->finalize (obj);
}


GType rygel_mediathek_root_container_get_type (void) {
	static volatile gsize rygel_mediathek_root_container_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_mediathek_root_container_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediathekRootContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_mediathek_root_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediathekRootContainer), 0, (GInstanceInitFunc) rygel_mediathek_root_container_instance_init, NULL };
		GType rygel_mediathek_root_container_type_id;
		rygel_mediathek_root_container_type_id = g_type_register_static (RYGEL_TYPE_SIMPLE_CONTAINER, "RygelMediathekRootContainer", &g_define_type_info, 0);
		g_once_init_leave (&rygel_mediathek_root_container_type_id__volatile, rygel_mediathek_root_container_type_id);
	}
	return rygel_mediathek_root_container_type_id__volatile;
}


