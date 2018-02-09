/* testpriorityqueue.c generated by valac 0.15.0.90-e9553, the Vala compiler
 * generated from testpriorityqueue.vala, do not modify */

/* testpriorityqueue.vala
 *
 * Copyright (C) 2009  Didier Villevalois
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 * Authors:
 * 	Didier 'Ptitjes Villevalois <ptitjes@free.fr>
 */

#include <glib.h>
#include <glib-object.h>
#include <gee.h>
#include <stdlib.h>
#include <string.h>


#define GEE_TYPE_TEST_CASE (gee_test_case_get_type ())
#define GEE_TEST_CASE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_TEST_CASE, GeeTestCase))
#define GEE_TEST_CASE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEE_TYPE_TEST_CASE, GeeTestCaseClass))
#define GEE_IS_TEST_CASE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_TEST_CASE))
#define GEE_IS_TEST_CASE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEE_TYPE_TEST_CASE))
#define GEE_TEST_CASE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GEE_TYPE_TEST_CASE, GeeTestCaseClass))

typedef struct _GeeTestCase GeeTestCase;
typedef struct _GeeTestCaseClass GeeTestCaseClass;
typedef struct _GeeTestCasePrivate GeeTestCasePrivate;

#define TYPE_COLLECTION_TESTS (collection_tests_get_type ())
#define COLLECTION_TESTS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_COLLECTION_TESTS, CollectionTests))
#define COLLECTION_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_COLLECTION_TESTS, CollectionTestsClass))
#define IS_COLLECTION_TESTS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_COLLECTION_TESTS))
#define IS_COLLECTION_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_COLLECTION_TESTS))
#define COLLECTION_TESTS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_COLLECTION_TESTS, CollectionTestsClass))

typedef struct _CollectionTests CollectionTests;
typedef struct _CollectionTestsClass CollectionTestsClass;
typedef struct _CollectionTestsPrivate CollectionTestsPrivate;

#define TYPE_QUEUE_TESTS (queue_tests_get_type ())
#define QUEUE_TESTS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_QUEUE_TESTS, QueueTests))
#define QUEUE_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_QUEUE_TESTS, QueueTestsClass))
#define IS_QUEUE_TESTS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_QUEUE_TESTS))
#define IS_QUEUE_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_QUEUE_TESTS))
#define QUEUE_TESTS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_QUEUE_TESTS, QueueTestsClass))

typedef struct _QueueTests QueueTests;
typedef struct _QueueTestsClass QueueTestsClass;
typedef struct _QueueTestsPrivate QueueTestsPrivate;

#define TYPE_PRIORITY_QUEUE_TESTS (priority_queue_tests_get_type ())
#define PRIORITY_QUEUE_TESTS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_PRIORITY_QUEUE_TESTS, PriorityQueueTests))
#define PRIORITY_QUEUE_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_PRIORITY_QUEUE_TESTS, PriorityQueueTestsClass))
#define IS_PRIORITY_QUEUE_TESTS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_PRIORITY_QUEUE_TESTS))
#define IS_PRIORITY_QUEUE_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_PRIORITY_QUEUE_TESTS))
#define PRIORITY_QUEUE_TESTS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_PRIORITY_QUEUE_TESTS, PriorityQueueTestsClass))

typedef struct _PriorityQueueTests PriorityQueueTests;
typedef struct _PriorityQueueTestsClass PriorityQueueTestsClass;
typedef struct _PriorityQueueTestsPrivate PriorityQueueTestsPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

struct _GeeTestCase {
	GObject parent_instance;
	GeeTestCasePrivate * priv;
};

struct _GeeTestCaseClass {
	GObjectClass parent_class;
	void (*set_up) (GeeTestCase* self);
	void (*tear_down) (GeeTestCase* self);
};

struct _CollectionTests {
	GeeTestCase parent_instance;
	CollectionTestsPrivate * priv;
	GeeCollection* test_collection;
};

struct _CollectionTestsClass {
	GeeTestCaseClass parent_class;
};

struct _QueueTests {
	CollectionTests parent_instance;
	QueueTestsPrivate * priv;
};

struct _QueueTestsClass {
	CollectionTestsClass parent_class;
};

struct _PriorityQueueTests {
	QueueTests parent_instance;
	PriorityQueueTestsPrivate * priv;
};

struct _PriorityQueueTestsClass {
	QueueTestsClass parent_class;
};

typedef void (*GeeTestCaseTestMethod) (void* user_data);

static gpointer priority_queue_tests_parent_class = NULL;

GType gee_test_case_get_type (void) G_GNUC_CONST;
GType collection_tests_get_type (void) G_GNUC_CONST;
GType queue_tests_get_type (void) G_GNUC_CONST;
GType priority_queue_tests_get_type (void) G_GNUC_CONST;
enum  {
	PRIORITY_QUEUE_TESTS_DUMMY_PROPERTY
};
PriorityQueueTests* priority_queue_tests_new (void);
PriorityQueueTests* priority_queue_tests_construct (GType object_type);
QueueTests* queue_tests_construct (GType object_type, const gchar* name);
void gee_test_case_add_test (GeeTestCase* self, const gchar* name, GeeTestCaseTestMethod test, void* test_target);
static void priority_queue_tests_test_selected_functions (PriorityQueueTests* self);
static void _priority_queue_tests_test_selected_functions_gee_test_case_test_method (gpointer self);
void priority_queue_tests_test_gobject_properties (PriorityQueueTests* self);
static void _priority_queue_tests_test_gobject_properties_gee_test_case_test_method (gpointer self);
static void priority_queue_tests_test_poll_gives_minimum (PriorityQueueTests* self);
static void _priority_queue_tests_test_poll_gives_minimum_gee_test_case_test_method (gpointer self);
static void priority_queue_tests_real_set_up (GeeTestCase* base);
static void priority_queue_tests_real_tear_down (GeeTestCase* base);


static void _priority_queue_tests_test_selected_functions_gee_test_case_test_method (gpointer self) {
	priority_queue_tests_test_selected_functions (self);
}


static void _priority_queue_tests_test_gobject_properties_gee_test_case_test_method (gpointer self) {
	priority_queue_tests_test_gobject_properties (self);
}


static void _priority_queue_tests_test_poll_gives_minimum_gee_test_case_test_method (gpointer self) {
	priority_queue_tests_test_poll_gives_minimum (self);
}


PriorityQueueTests* priority_queue_tests_construct (GType object_type) {
	PriorityQueueTests * self = NULL;
	self = (PriorityQueueTests*) queue_tests_construct (object_type, "PriorityQueue");
	gee_test_case_add_test ((GeeTestCase*) self, "[PriorityQueue] selected functions", _priority_queue_tests_test_selected_functions_gee_test_case_test_method, self);
	gee_test_case_add_test ((GeeTestCase*) self, "[PriorityQueue] GObject properties", _priority_queue_tests_test_gobject_properties_gee_test_case_test_method, self);
	gee_test_case_add_test ((GeeTestCase*) self, "[PriorityQueue] poll gives minimum", _priority_queue_tests_test_poll_gives_minimum_gee_test_case_test_method, self);
	return self;
}


PriorityQueueTests* priority_queue_tests_new (void) {
	return priority_queue_tests_construct (TYPE_PRIORITY_QUEUE_TESTS);
}


static void priority_queue_tests_real_set_up (GeeTestCase* base) {
	PriorityQueueTests * self;
	GeePriorityQueue* _tmp0_;
	self = (PriorityQueueTests*) base;
	_tmp0_ = gee_priority_queue_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL);
	_g_object_unref0 (((CollectionTests*) self)->test_collection);
	((CollectionTests*) self)->test_collection = (GeeCollection*) _tmp0_;
}


static void priority_queue_tests_real_tear_down (GeeTestCase* base) {
	PriorityQueueTests * self;
	self = (PriorityQueueTests*) base;
	_g_object_unref0 (((CollectionTests*) self)->test_collection);
	((CollectionTests*) self)->test_collection = NULL;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void priority_queue_tests_test_selected_functions (PriorityQueueTests* self) {
	GeeCollection* _tmp0_;
	GeePriorityQueue* _tmp1_;
	GeePriorityQueue* test_queue;
	GCompareFunc _tmp2_;
	GCompareFunc _tmp3_;
	GCompareFunc _tmp4_;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((CollectionTests*) self)->test_collection;
	_tmp1_ = _g_object_ref0 (GEE_IS_PRIORITY_QUEUE (_tmp0_) ? ((GeePriorityQueue*) _tmp0_) : NULL);
	test_queue = _tmp1_;
	g_assert (test_queue != NULL);
	_tmp2_ = gee_priority_queue_get_compare_func (test_queue);
	_tmp3_ = _tmp2_;
	_tmp4_ = g_strcmp0;
	g_assert (_tmp3_ == ((GCompareFunc) _tmp4_));
	_g_object_unref0 (test_queue);
}


void priority_queue_tests_test_gobject_properties (PriorityQueueTests* self) {
	GeeCollection* _tmp0_;
	GeePriorityQueue* _tmp1_;
	GeePriorityQueue* test_queue;
	GValue value = {0};
	GValue _tmp2_ = {0};
	void* _tmp3_ = NULL;
	GCompareFunc _tmp4_;
	GCompareFunc _tmp5_;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((CollectionTests*) self)->test_collection;
	_tmp1_ = _g_object_ref0 (GEE_IS_PRIORITY_QUEUE (_tmp0_) ? ((GeePriorityQueue*) _tmp0_) : NULL);
	test_queue = _tmp1_;
	g_assert (test_queue != NULL);
	g_value_init (&_tmp2_, G_TYPE_POINTER);
	G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL;
	value = _tmp2_;
	g_object_get_property ((GObject*) test_queue, "compare-func", &value);
	_tmp3_ = g_value_get_pointer (&value);
	_tmp4_ = gee_priority_queue_get_compare_func (test_queue);
	_tmp5_ = _tmp4_;
	g_assert (_tmp3_ == ((void*) _tmp5_));
	g_value_unset (&value);
	G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL;
	_g_object_unref0 (test_queue);
}


static void priority_queue_tests_test_poll_gives_minimum (PriorityQueueTests* self) {
	GeeCollection* _tmp0_;
	GeeQueue* _tmp1_;
	GeeQueue* test_queue;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	gpointer _tmp4_ = NULL;
	gchar* _tmp5_;
	gboolean _tmp6_ = FALSE;
	gpointer _tmp7_ = NULL;
	gchar* _tmp8_;
	gpointer _tmp9_ = NULL;
	gchar* _tmp10_;
	gboolean _tmp11_ = FALSE;
	gboolean _tmp12_ = FALSE;
	gboolean _tmp13_ = FALSE;
	gboolean _tmp14_ = FALSE;
	gboolean _tmp15_ = FALSE;
	gboolean _tmp16_ = FALSE;
	gboolean _tmp17_ = FALSE;
	gboolean _tmp18_ = FALSE;
	gboolean _tmp19_ = FALSE;
	gboolean _tmp20_ = FALSE;
	gboolean _tmp21_ = FALSE;
	gboolean _tmp22_ = FALSE;
	gpointer _tmp23_ = NULL;
	gchar* _tmp24_;
	gpointer _tmp25_ = NULL;
	gchar* _tmp26_;
	gpointer _tmp27_ = NULL;
	gchar* _tmp28_;
	gpointer _tmp29_ = NULL;
	gchar* _tmp30_;
	gpointer _tmp31_ = NULL;
	gchar* _tmp32_;
	gpointer _tmp33_ = NULL;
	gchar* _tmp34_;
	gpointer _tmp35_ = NULL;
	gchar* _tmp36_;
	gpointer _tmp37_ = NULL;
	gchar* _tmp38_;
	gpointer _tmp39_ = NULL;
	gchar* _tmp40_;
	gpointer _tmp41_ = NULL;
	gchar* _tmp42_;
	gpointer _tmp43_ = NULL;
	gchar* _tmp44_;
	gpointer _tmp45_ = NULL;
	gchar* _tmp46_;
	gpointer _tmp47_ = NULL;
	gchar* _tmp48_;
	gpointer _tmp49_ = NULL;
	gchar* _tmp50_;
	gpointer _tmp51_ = NULL;
	gchar* _tmp52_;
	gpointer _tmp53_ = NULL;
	gchar* _tmp54_;
	gpointer _tmp55_ = NULL;
	gchar* _tmp56_;
	gpointer _tmp57_ = NULL;
	gchar* _tmp58_;
	gpointer _tmp59_ = NULL;
	gchar* _tmp60_;
	gpointer _tmp61_ = NULL;
	gchar* _tmp62_;
	gpointer _tmp63_ = NULL;
	gchar* _tmp64_;
	gpointer _tmp65_ = NULL;
	gchar* _tmp66_;
	gpointer _tmp67_ = NULL;
	gchar* _tmp68_;
	gpointer _tmp69_ = NULL;
	gchar* _tmp70_;
	gboolean _tmp71_ = FALSE;
	gboolean _tmp72_ = FALSE;
	gpointer _tmp73_ = NULL;
	gchar* _tmp74_;
	gpointer _tmp75_ = NULL;
	gchar* _tmp76_;
	gpointer _tmp77_ = NULL;
	gchar* _tmp78_;
	gpointer _tmp79_ = NULL;
	gchar* _tmp80_;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((CollectionTests*) self)->test_collection;
	_tmp1_ = _g_object_ref0 (GEE_IS_QUEUE (_tmp0_) ? ((GeeQueue*) _tmp0_) : NULL);
	test_queue = _tmp1_;
	g_assert (test_queue != NULL);
	_tmp2_ = gee_queue_offer (test_queue, "one");
	g_assert (_tmp2_);
	_tmp3_ = gee_queue_offer (test_queue, "two");
	g_assert (_tmp3_);
	_tmp4_ = gee_queue_peek (test_queue);
	_tmp5_ = (gchar*) _tmp4_;
	g_assert (g_strcmp0 (_tmp5_, "one") == 0);
	_g_free0 (_tmp5_);
	_tmp6_ = gee_collection_remove ((GeeCollection*) test_queue, "two");
	g_assert (_tmp6_);
	_tmp7_ = gee_queue_peek (test_queue);
	_tmp8_ = (gchar*) _tmp7_;
	g_assert (g_strcmp0 (_tmp8_, "one") == 0);
	_g_free0 (_tmp8_);
	_tmp9_ = gee_queue_poll (test_queue);
	_tmp10_ = (gchar*) _tmp9_;
	g_assert (g_strcmp0 (_tmp10_, "one") == 0);
	_g_free0 (_tmp10_);
	_tmp11_ = gee_queue_offer (test_queue, "one");
	g_assert (_tmp11_);
	_tmp12_ = gee_queue_offer (test_queue, "two");
	g_assert (_tmp12_);
	_tmp13_ = gee_queue_offer (test_queue, "three");
	g_assert (_tmp13_);
	_tmp14_ = gee_queue_offer (test_queue, "four");
	g_assert (_tmp14_);
	_tmp15_ = gee_queue_offer (test_queue, "five");
	g_assert (_tmp15_);
	_tmp16_ = gee_queue_offer (test_queue, "six");
	g_assert (_tmp16_);
	_tmp17_ = gee_queue_offer (test_queue, "seven");
	g_assert (_tmp17_);
	_tmp18_ = gee_queue_offer (test_queue, "eight");
	g_assert (_tmp18_);
	_tmp19_ = gee_queue_offer (test_queue, "nine");
	g_assert (_tmp19_);
	_tmp20_ = gee_queue_offer (test_queue, "ten");
	g_assert (_tmp20_);
	_tmp21_ = gee_queue_offer (test_queue, "eleven");
	g_assert (_tmp21_);
	_tmp22_ = gee_queue_offer (test_queue, "twelve");
	g_assert (_tmp22_);
	_tmp23_ = gee_queue_peek (test_queue);
	_tmp24_ = (gchar*) _tmp23_;
	g_assert (g_strcmp0 (_tmp24_, "eight") == 0);
	_g_free0 (_tmp24_);
	_tmp25_ = gee_queue_poll (test_queue);
	_tmp26_ = (gchar*) _tmp25_;
	g_assert (g_strcmp0 (_tmp26_, "eight") == 0);
	_g_free0 (_tmp26_);
	_tmp27_ = gee_queue_peek (test_queue);
	_tmp28_ = (gchar*) _tmp27_;
	g_assert (g_strcmp0 (_tmp28_, "eleven") == 0);
	_g_free0 (_tmp28_);
	_tmp29_ = gee_queue_poll (test_queue);
	_tmp30_ = (gchar*) _tmp29_;
	g_assert (g_strcmp0 (_tmp30_, "eleven") == 0);
	_g_free0 (_tmp30_);
	_tmp31_ = gee_queue_peek (test_queue);
	_tmp32_ = (gchar*) _tmp31_;
	g_assert (g_strcmp0 (_tmp32_, "five") == 0);
	_g_free0 (_tmp32_);
	_tmp33_ = gee_queue_poll (test_queue);
	_tmp34_ = (gchar*) _tmp33_;
	g_assert (g_strcmp0 (_tmp34_, "five") == 0);
	_g_free0 (_tmp34_);
	_tmp35_ = gee_queue_peek (test_queue);
	_tmp36_ = (gchar*) _tmp35_;
	g_assert (g_strcmp0 (_tmp36_, "four") == 0);
	_g_free0 (_tmp36_);
	_tmp37_ = gee_queue_poll (test_queue);
	_tmp38_ = (gchar*) _tmp37_;
	g_assert (g_strcmp0 (_tmp38_, "four") == 0);
	_g_free0 (_tmp38_);
	_tmp39_ = gee_queue_peek (test_queue);
	_tmp40_ = (gchar*) _tmp39_;
	g_assert (g_strcmp0 (_tmp40_, "nine") == 0);
	_g_free0 (_tmp40_);
	_tmp41_ = gee_queue_poll (test_queue);
	_tmp42_ = (gchar*) _tmp41_;
	g_assert (g_strcmp0 (_tmp42_, "nine") == 0);
	_g_free0 (_tmp42_);
	_tmp43_ = gee_queue_peek (test_queue);
	_tmp44_ = (gchar*) _tmp43_;
	g_assert (g_strcmp0 (_tmp44_, "one") == 0);
	_g_free0 (_tmp44_);
	_tmp45_ = gee_queue_poll (test_queue);
	_tmp46_ = (gchar*) _tmp45_;
	g_assert (g_strcmp0 (_tmp46_, "one") == 0);
	_g_free0 (_tmp46_);
	_tmp47_ = gee_queue_peek (test_queue);
	_tmp48_ = (gchar*) _tmp47_;
	g_assert (g_strcmp0 (_tmp48_, "seven") == 0);
	_g_free0 (_tmp48_);
	_tmp49_ = gee_queue_poll (test_queue);
	_tmp50_ = (gchar*) _tmp49_;
	g_assert (g_strcmp0 (_tmp50_, "seven") == 0);
	_g_free0 (_tmp50_);
	_tmp51_ = gee_queue_peek (test_queue);
	_tmp52_ = (gchar*) _tmp51_;
	g_assert (g_strcmp0 (_tmp52_, "six") == 0);
	_g_free0 (_tmp52_);
	_tmp53_ = gee_queue_poll (test_queue);
	_tmp54_ = (gchar*) _tmp53_;
	g_assert (g_strcmp0 (_tmp54_, "six") == 0);
	_g_free0 (_tmp54_);
	_tmp55_ = gee_queue_peek (test_queue);
	_tmp56_ = (gchar*) _tmp55_;
	g_assert (g_strcmp0 (_tmp56_, "ten") == 0);
	_g_free0 (_tmp56_);
	_tmp57_ = gee_queue_poll (test_queue);
	_tmp58_ = (gchar*) _tmp57_;
	g_assert (g_strcmp0 (_tmp58_, "ten") == 0);
	_g_free0 (_tmp58_);
	_tmp59_ = gee_queue_peek (test_queue);
	_tmp60_ = (gchar*) _tmp59_;
	g_assert (g_strcmp0 (_tmp60_, "three") == 0);
	_g_free0 (_tmp60_);
	_tmp61_ = gee_queue_poll (test_queue);
	_tmp62_ = (gchar*) _tmp61_;
	g_assert (g_strcmp0 (_tmp62_, "three") == 0);
	_g_free0 (_tmp62_);
	_tmp63_ = gee_queue_peek (test_queue);
	_tmp64_ = (gchar*) _tmp63_;
	g_assert (g_strcmp0 (_tmp64_, "twelve") == 0);
	_g_free0 (_tmp64_);
	_tmp65_ = gee_queue_poll (test_queue);
	_tmp66_ = (gchar*) _tmp65_;
	g_assert (g_strcmp0 (_tmp66_, "twelve") == 0);
	_g_free0 (_tmp66_);
	_tmp67_ = gee_queue_peek (test_queue);
	_tmp68_ = (gchar*) _tmp67_;
	g_assert (g_strcmp0 (_tmp68_, "two") == 0);
	_g_free0 (_tmp68_);
	_tmp69_ = gee_queue_poll (test_queue);
	_tmp70_ = (gchar*) _tmp69_;
	g_assert (g_strcmp0 (_tmp70_, "two") == 0);
	_g_free0 (_tmp70_);
	_tmp71_ = gee_queue_offer (test_queue, "2");
	g_assert (_tmp71_);
	_tmp72_ = gee_queue_offer (test_queue, "1");
	g_assert (_tmp72_);
	_tmp73_ = gee_queue_peek (test_queue);
	_tmp74_ = (gchar*) _tmp73_;
	g_assert (g_strcmp0 (_tmp74_, "1") == 0);
	_g_free0 (_tmp74_);
	_tmp75_ = gee_queue_poll (test_queue);
	_tmp76_ = (gchar*) _tmp75_;
	g_assert (g_strcmp0 (_tmp76_, "1") == 0);
	_g_free0 (_tmp76_);
	_tmp77_ = gee_queue_peek (test_queue);
	_tmp78_ = (gchar*) _tmp77_;
	g_assert (g_strcmp0 (_tmp78_, "2") == 0);
	_g_free0 (_tmp78_);
	_tmp79_ = gee_queue_poll (test_queue);
	_tmp80_ = (gchar*) _tmp79_;
	g_assert (g_strcmp0 (_tmp80_, "2") == 0);
	_g_free0 (_tmp80_);
	_g_object_unref0 (test_queue);
}


static void priority_queue_tests_class_init (PriorityQueueTestsClass * klass) {
	priority_queue_tests_parent_class = g_type_class_peek_parent (klass);
	GEE_TEST_CASE_CLASS (klass)->set_up = priority_queue_tests_real_set_up;
	GEE_TEST_CASE_CLASS (klass)->tear_down = priority_queue_tests_real_tear_down;
}


static void priority_queue_tests_instance_init (PriorityQueueTests * self) {
}


GType priority_queue_tests_get_type (void) {
	static volatile gsize priority_queue_tests_type_id__volatile = 0;
	if (g_once_init_enter (&priority_queue_tests_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (PriorityQueueTestsClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) priority_queue_tests_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PriorityQueueTests), 0, (GInstanceInitFunc) priority_queue_tests_instance_init, NULL };
		GType priority_queue_tests_type_id;
		priority_queue_tests_type_id = g_type_register_static (TYPE_QUEUE_TESTS, "PriorityQueueTests", &g_define_type_info, 0);
		g_once_init_leave (&priority_queue_tests_type_id__volatile, priority_queue_tests_type_id);
	}
	return priority_queue_tests_type_id__volatile;
}


