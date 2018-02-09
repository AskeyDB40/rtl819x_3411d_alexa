AC_PREREQ([2.63])
AC_INIT([gupnp-dlna],
        [0.6.6],
        [https://bugzilla.gnome.org/enter_bug.cgi?product=gupnp&component=gupnp-dlna],
        [gupnp-dlna],
        [http://www.gupnp.org/])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR(libgupnp-dlna/gupnp-dlna-profile.h)
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([1.11 tar-ustar no-dist-gzip dist-xz])

AM_SILENT_RULES([yes])

dnl library versioning
dnl Increase when changing the API
GUPNP_DLNA_CURRENT=2

dnl Update when changing implementation of current API,
dnl reset to 0 when changing CURRENT.  This is the revision of
dnl current API version
GUPNP_DLNA_REVISION=0

dnl Increase if API change is ABI compatible, otherwise reset to 0
GUPNP_DLNA_AGE=0

GUPNP_DLNA_VERSION_INFO="$GUPNP_DLNA_CURRENT:$GUPNP_DLNA_REVISION:$GUPNP_DLNA_AGE"
AC_SUBST(GUPNP_DLNA_VERSION_INFO)

# Check for programs
AC_PROG_CC
AC_HEADER_STDC

# Initialize libtool
LT_PREREQ([2.2])
LT_INIT([win32-dll])

PKG_CHECK_MODULES(LIBXML, libxml-2.0 >= 2.5.0)

GST_MAJORMINOR=0.10
GST_REQ=0.10.29.2
GSTPBU_REQ=0.10.32

PKG_CHECK_MODULES(GST, gstreamer-$GST_MAJORMINOR >= $GST_REQ)
PKG_CHECK_MODULES(GST_PBU, gstreamer-pbutils-$GST_MAJORMINOR >= $GSTPBU_REQ)
AC_SUBST(GST_MAJORMINOR)

GST_CFLAGS="$GST_CFLAGS -DGST_USE_UNSTABLE_API"
AC_SUBST(GST_CFLAGS)

# glib-genmarshal
GLIB_GENMARSHAL=`pkg-config --variable=glib_genmarshal glib-2.0`
AC_SUBST(GLIB_GENMARSHAL)

# Debugging
AC_ARG_ENABLE(debug,
	[  --enable-debug          enable debugging],,
        enable_debug=no)
if test "x$enable_debug" = "xyes"; then
        CFLAGS="$CFLAGS -g -Wall"
fi

GOBJECT_INTROSPECTION_CHECK([0.6.4])

GTK_DOC_CHECK([1.11],[--flavour no-tmpl])

AC_CONFIG_FILES([
Makefile
libgupnp-dlna/Makefile
tools/Makefile
tests/Makefile
tests/test-discoverer.sh
doc/Makefile
doc/version.xml
data/Makefile
gupnp-dlna-1.0.pc
gupnp-dlna-1.0-uninstalled.pc
])
AC_OUTPUT
