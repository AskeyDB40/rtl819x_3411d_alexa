
ifeq ($(wildcard $(DIR_LINUX)/.config),)
include ../../../linux-3.10/.config
else
include $(DIR_LINUX)/.config
endif
#get rsdk dir
include ../../../.config
RSDK_LIB_DIR=$(shell  echo $(PATH) | cut -f2 -d:)
CURRENT_DIR=$(shell pwd)
TEMP_PATH=$(PATH)
ifdef CONFIG_RSDKDIR
RSDK_LIB_DIR=$(CURRENT_DIR)/../../../$(CONFIG_RSDKDIR)/bin
endif
export RSDK_LIB_DIR

include $(CURRENT_DIR)/../../boa/wfaudio_platform.include.mk
ALL_SUBDIR=

INCLUDE_DLNA=1


GLIB_INSTALL_DIR=$(CURRENT_DIR)/Renderer_Install/bin

RENDER_INSTALL_DIR=/usr/Dlna_Rygel

PATH:= $(GLIB_INSTALL_DIR):$(PATH)
export PATH
INCLUDES=-I$(GLIB_INSTALL_DIR)/../include/glib-2.0
INCLUDES+=-I$(GLIB_INSTALL_DIR)/../lib/glib-2.0/include
export INCLUDES
export PKG_CONFIG_PATH=$(GLIB_INSTALL_DIR)/../lib/pkgconfig

GSTREAMER_VER=gstreamer-0.10

SUBDIR_INTL_LIB = gettext-0.18.1.1/gettext-runtime
SUBDIR_ICONV_LIB = libiconv-1.14
SUBDIR_FFI_LIB = libffi-3.0.11
SUBDIR_XML2_LIB = libxml2-2.8.0
SUBDIR_Z_LIB = zlib-1.2.7
SUBDIR_MAD_LIB = libmad-0.15.1b
SUBDIR_SOUP_LIB = libsoup-2.38.1
SUBDIR_UUID_LIB = e2fsprogs-1.42.4
SUBDIR_G_LIB = glib-2.32.4
SUBDIR_OGG_LIB = libogg-1.3.0
SUBDIR_VOSBIS_LIB = libvorbis-1.3.3
SUBDIR_MMS_LIB = libmms-0.5

SUBDIR_GEE_LIB = libgee-0.6.4
SUBDIR_GUPNP_LIB = gupnp-0.18.3
SUBDIR_GSSDP_LIB = gssdp-0.12.1
SUBDIR_GUPNP_AV_LIB = gupnp-av-0.10.2
SUBDIR_GUPNP_DLNA_LIB = gupnp-dlna-0.6.6

########################################
SUBDIR_GSTREAM_LIB = gstreamer-0.10.36
SUBDIR_GSTREAM_PLUGIN_LIB = gst-plugins-base-0.10.36
SUBDIR_GSTREAM_GOODPLUGIN_LIB = gst-plugins-good-0.10.31
SUBDIR_GSTREAM_UGLYPLUGIN_LIB = gst-plugins-ugly-0.10.19
SUBDIR_GSTREAM_BADPLUGIN_LIB = gst-plugins-bad-0.10.23
SUBDIR_GSTREAM_FFMPEG_LIB = gst-ffmpeg-0.10.13
############################################

SUBDIR_SHARED_MIME_LIB = shared-mime-info-1.0
SUBDIR_AV_LIB = libav-0.8.16
SUBDIR_DCA_LIB = libdca-0.0.5
SUBDIR_FAAD_LIB = faad2-2.7
SUBDIR_FLAC_LIB = flac-1.2.1

SUBDIR_RYGEL_RENDER = rygel-0.16.3


ALL_SUBDIR = $(SUBDIR_ICONV_LIB) 
ALL_SUBDIR += $(SUBDIR_FFI_LIB) $(SUBDIR_XML2_LIB) $(SUBDIR_Z_LIB) $(SUBDIR_MAD_LIB) $(SUBDIR_SOUP_LIB) 
ALL_SUBDIR +=  $(SUBDIR_G_LIB) $(SUBDIR_OGG_LIB) $(SUBDIR_VOSBIS_LIB) $(SUBDIR_MMS_LIB)
ALL_SUBDIR += $(SUBDIR_GSTREAM_LIB) $(SUBDIR_GSTREAM_PLUGIN_LIB) $(SUBDIR_GSTREAM_GOODPLUGIN_LIB)
ALL_SUBDIR += $(SUBDIR_GSTREAM_UGLYPLUGIN_LIB) $(SUBDIR_GSTREAM_BADPLUGIN_LIB) 
ALL_SUBDIR += $(SUBDIR_SHARED_MIME_LIB) $(SUBDIR_DCA_LIB) 
ALL_SUBDIR += $(SUBDIR_FAAD_LIB) $(SUBDIR_FLAC_LIB)

ifeq ($(INCLUDE_DLNA), 1)
ALL_SUBDIR +=  $(SUBDIR_GEE_LIB) $(SUBDIR_UUID_LIB) $(SUBDIR_GUPNP_LIB) $(SUBDIR_GSSDP_LIB) $(SUBDIR_GUPNP_AV_LIB) $(SUBDIR_GUPNP_DLNA_LIB)
endif


FLAC_LIB = flac_lib
DCA_LIB = dca_lib
FAAC_LIB = faac_lib
FAAD_LIB = faad_lib
AV_LIB= av_lib

INTL_LIB = intl_lib
ICONV_LIB= iconv_lib
FFI_LIB = ffi_lib
XML2_LIB = xml2_lib
Z_LIB = z_lib
SOUP_LIB = soup_lib
MAD_LIB = mad_lib
G_LIB = g_lib
GSTREAM_LIB = gtream_lib
OGG_LIB = ogg_lib
VORBIS_LIB = vorbis_lib
GSTREAM_PLUGIN_LIB = gtream_plugin_lib
GSTREAM_GOODPLUGIN_LIB = gtream_goodplugin_lib
GSTREAM_UGLYPLUGIN_LIB = gtream_uglyplugin_lib
GSTREAM_FFMPEGPLUGIN_LIB = gtream_ffmpegplugin_lib
GSTREAM_BADPLUGIN_LIB = gtream_badplugin_lib


UUID_LIB = uuid_lib
GEE_LIB = gee_lib
GUPNP_LIB = gupnp_lib
GSSDP_LIB = gssdp_lib
GUPNP_AV_LIB = gupnp_av_lib
GUPNP_DLNA_LIB = gupnp_dlna_lib

SHARED_MIME_LIB=shared_mime_lib
MMS_LIB=mms_lib



ALL_DEPEND_LIB=
#############
ALL_DEPEND_LIB =$(Z_LIB) $(XML2_LIB) $(FFI_LIB)  $(ICONV_LIB) $(INTL_LIB) $(G_LIB) $(MAD_LIB) $(SOUP_LIB) 
ALL_DEPEND_LIB += $(FLAC_LIB) $(FAAD_LIB) $(DCA_LIB) $(OGG_LIB) $(VORBIS_LIB) $(MMS_LIB) $(AV_LIB) 
ALL_DEPEND_LIB += $(GSTREAM_LIB) $(GSTREAM_PLUGIN_LIB) $(GSTREAM_GOODPLUGIN_LIB) $(GSTREAM_UGLYPLUGIN_LIB) 
ALL_DEPEND_LIB += $(GSTREAM_BADPLUGIN_LIB) $(GSTREAM_FFMPEGPLUGIN_LIB)

ifeq ($(INCLUDE_DLNA), 1)
ALL_DEPEND_LIB += $(UUID_LIB) $(GEE_LIB) $(GSSDP_LIB) $(GUPNP_LIB) $(GUPNP_AV_LIB) 
endif

ALL_DEPEND_LIB += $(SHARED_MIME_LIB) 
##############

CONFIG_RTL_PRE_EMPTIVE=y
export CONFIG_RTL_PRE_EMPTIVE

#get users config
include ../../.config
MR_INCLUDE=
MR_LIBS=

.PHONY: all clean

PLATFORM_CFLAGS +=-DCONFIG_RTL_PRE_EMPTIVE
export PLATFORM_CFLAGS
GCC_OPTIMIZATION=-Os $(PLATFORM_CFLAGS)
CFLAGS += -Os -I$(GLIB_INSTALL_DIR)/../include

all:$(ALL_DEPEND_LIB)
ifeq ($(INCLUDE_DLNA), 1)
	if [ ! -e ./$(SUBDIR_RYGEL_RENDER)/Configured_Done ]; then \
		cd ./$(SUBDIR_RYGEL_RENDER); \
		find -name "*.stamp" -exec touch {} \; ; \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" UUID_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/uuid" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include -I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) -I$(CURRENT_DIR)/../shm -I$(RSDK_LIB_DIR)/../include" LDFLAGS="-L$(CURRENT_DIR)/../shm -lwfshm -L$(RSDK_LIB_DIR)/../lib -lasound -lm -L$(GLIB_INSTALL_DIR)/../lib -luuid -L$(GLIB_INSTALL_DIR)/../lib -liconv -lintl" GEE_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgee" GEE_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/gee-1.0" ./configure --without-ui  --disable-nls --enable-strict-valac=no --enable-tests=no --enable-media-export-plugin=no --enable-mediathek-plugin=no --enable-gst-launch-plugin=no  --enable-valadoc=no --enable-vala=no --enable-playbin-plugin=yes --enable-test-plugin=no --enable-external-plugin=no --enable-tracker-plugin=no --enable-debug=no --enable-mpris-plugin=no --build=i686-pc-linux-gnu --host=mips-linux --enable-shared=yes --sysconfdir=/etc/rygel-1.0 --prefix=$(RENDER_INSTALL_DIR); \
		touch ./configure; \
		touch ./config.status; \
		touch ./config.h; \
		touch ./config.h.in; \
		touch ./rygel-1.0.pc.in; \
		touch ./rygel-1.0.pc; \
		touch ./Makefile; \
		touch ./Makefile.in; \
		touch ./src/rygel/rygel_vala.stamp; \
		touch ./src/plugins/external/librygel_external_la_vala.stamp; \
		touch ./src/plugins/gst-launch/librygel_gst_launch_la_vala.stamp; \
		touch ./src/plugins/media-export/librygel_media_export_la_vala.stamp; \
		touch ./src/plugins/playbin/librygel_playbin_la_vala.stamp; \
		touch ./src/plugins/mediathek/librygel_mediathek_la_vala.stamp; \
		touch ./src/plugins/mpris/librygel_mpris_la_vala.stamp; \
		touch ./src/plugins/test/librygel_test_la_vala.stamp; \
		touch ./src/plugins/tracker/librygel_tracker_la_vala.stamp; \
		echo "configured done" > ./Configured_Done; \
	fi
	make -C $(SUBDIR_RYGEL_RENDER)
	rm -Rf $(RENDER_INSTALL_DIR)/*
	make -C $(SUBDIR_RYGEL_RENDER) install
endif

iconv_lib:
	if [ ! -e ./$(SUBDIR_ICONV_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_ICONV_LIB); \
		touch ./Makefile.in; \
		touch ./configure; \
		touch ./config.h.in; \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" ./configure --disable-nls --enable-static=yes --build=i686-pc-linux-gnu --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
		touch ./Makefile; \
		touch ./config.h; \
	fi
	if [ ! -e ./$(SUBDIR_ICONV_LIB)/.built ]; then \
	make -C $(SUBDIR_ICONV_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_ICONV_LIB) install; \
	echo "build done" > ./$(SUBDIR_ICONV_LIB)/.built; \
	fi \
	fi

z_lib:
	if [ ! -e ./$(SUBDIR_Z_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_Z_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" ./configure --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_Z_LIB)/.built ]; then \
	make -C $(SUBDIR_Z_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_Z_LIB) install; \
	echo "build done" > ./$(SUBDIR_Z_LIB)/.built; \
	fi \
	fi
	
xml2_lib:
	if [ ! -e ./$(SUBDIR_XML2_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_XML2_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" ./configure   --with-minimum=yes --with-c14n=no --with-catalog=no --with-debug=no --with-run-debug=no --with-docbook=no --with-fexceptions=no --with-ftp=no --with-history=no --with-http=no --with-iconv=no --with-iso8859x=no --with-legacy=no --with-mem-debug=no --with-output=yes --with-pattern=no --with-push=no --with-python=no --with-regexps=no --with-sax1=yes --with-schemas=no --with-schematron=no --with-threads=no --with-thread-alloc=no --with-tree=yes --with-valid=no --with-writer=no --with-xinclude=no --with-xpath=yes --with-xptr=no --with-zlib=no --with-modules=no --with-reader=yes --build=i686-pc-linux-gnu --host=mips-linux --enable-ipv6=no --enable-rebuild-docs=no --enable-static=yes   --with-html=no --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_XML2_LIB)/.built ]; then \
	make -C $(SUBDIR_XML2_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_XML2_LIB) install; \
	rm -f $(GLIB_INSTALL_DIR)/xmllint; \
	rm -f $(GLIB_INSTALL_DIR)/xmlcatalog; \
	rm -f $(GLIB_INSTALL_DIR)/xml2-config; \
	echo "build done" > ./$(SUBDIR_XML2_LIB)/.built; \
	fi \
	fi
	
ffi_lib:
	if [ ! -e ./$(SUBDIR_FFI_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_FFI_LIB); \
		touch ./Makefile.in; \
		touch ./configure; \
		touch ./fficonfig.h.in; \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" ./configure --build=i686-pc-linux-gnu --enable-debug=no --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
		touch ./Makefile; \
		touch ./fficonfig.h; \
	fi
	if [ ! -e ./$(SUBDIR_FFI_LIB)/.built ]; then \
	make -C $(SUBDIR_FFI_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_FFI_LIB) install; \
	echo "build done" > ./$(SUBDIR_FFI_LIB)/.built; \
	fi \
	fi
	
intl_lib:
	if [ ! -e ./$(SUBDIR_INTL_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_INTL_LIB); \
		touch ./Makefile.in; \
		touch ./configure; \
		touch ./config.h.in; \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" CPPFLAGS=-I$(GLIB_INSTALL_DIR)/../include LIBS="-L$(GLIB_INSTALL_DIR)/../lib -liconv" ./configure --with-included-gettext --without-csharp --disable-libasprintf -disable-rpath --build=i686-pc-linux-gnu --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
		touch ./Makefile; \
		touch ./config.h; \
	fi
	if [ ! -e ./$(SUBDIR_INTL_LIB)/.built ]; then \
	make -C $(SUBDIR_INTL_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_INTL_LIB) install; \
	echo "build done" > ./$(SUBDIR_INTL_LIB)/.built; \
	fi \
	fi

uuid_lib:
	if [ ! -e ./$(SUBDIR_UUID_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_UUID_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include -fPIC" LDFLAGS="-L$(GLIB_INSTALL_DIR)/../lib" ./configure --build=i686-pc-linux-gnu --disable-nls --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_UUID_LIB)/.built ]; then \
	make -C $(SUBDIR_UUID_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_UUID_LIB) install; \
	cp -pf $(SUBDIR_UUID_LIB)/lib/libuuid.a $(GLIB_INSTALL_DIR)/../lib; \
	rm -Rf $(GLIB_INSTALL_DIR)/../include/uuid; \
	mkdir -p $(GLIB_INSTALL_DIR)/../include/uuid; \
	cp -pf $(SUBDIR_UUID_LIB)/lib/uuid/uuid.h $(GLIB_INSTALL_DIR)/../include/uuid; \
	echo "build done" > ./$(SUBDIR_UUID_LIB)/.built; \
	fi \
	fi
	
g_lib:
	if [ ! -e ./$(SUBDIR_G_LIB)/.built ]; then \
	rm -f $(GLIB_INSTALL_DIR)/glib-gettextize 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/gtester 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/gtester-report 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/glib-genmarshal 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/glib-mkenums 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/gobject-query 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/gdbus-codegen 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/gdbus 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/gio-querymodules 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/glib-compile-schemas 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/gsettings 2> /dev/null; \
	rm -f $(GLIB_INSTALL_DIR)/glib-compile-resources 2> /dev/null; \
	ln -s /usr/local/bin/glib-compile-resources $(GLIB_INSTALL_DIR)/glib-compile-resources; \
	fi
	if [ ! -e ./$(SUBDIR_G_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_G_LIB); \
		cp -pf ../mips-linux.cache ./mips-linux.cache; \
		touch ./Makefile.in; \
		touch ./configure; \
		touch ./config.h.in; \
		LD="mips-linux-ld" CC="msdk-linux-gcc" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include" CPPFLAGS=-I$(GLIB_INSTALL_DIR)/../include LIBS="-L$(GLIB_INSTALL_DIR)/../lib -liconv" LIBFFI_CFLAGS=-I$(GLIB_INSTALL_DIR)/../lib/libffi-3.0.11/include LIBFFI_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lffi" ZLIB_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lz" ZLIB_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include DBUS1_LIBS="-L$(RSDK_LIB_DIR)/../lib -ldbus-1" ./configure --cache-file=mips-linux.cache --with-libiconv=gnu --build=i686-pc-linux-gnu --host=mips-linux --target=mips-linux --disable-gtk-doc --disable-man --prefix=$(GLIB_INSTALL_DIR)/.. --disable-dtrace --disable-xattr --disable-systemtap --disable-fam --disable-gcov -disable-mem-pools --with-threads=posix --disable-selinux --disable-static --enable-gcov=no --enable-systemtap=no --enable-dtrace=no --disable-Bsymbolic --enable-debug=no; \
		echo "configured done" > ./Configured_Done; \
		touch ./Makefile; \
		touch ./config.h; \
	fi
	if [ ! -e ./$(SUBDIR_G_LIB)/.built ]; then \
	make -C $(SUBDIR_G_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_G_LIB) install; \
	cp -fp ./$(SUBDIR_G_LIB)/glib/glibconfig.h $(GLIB_INSTALL_DIR)/../include/glib-2.0/glibconfig.h; \
	rm -f $(GLIB_INSTALL_DIR)/glib-gettextize; \
	rm -f $(GLIB_INSTALL_DIR)/gtester; \
	rm -f $(GLIB_INSTALL_DIR)/gtester-report; \
	rm -f $(GLIB_INSTALL_DIR)/glib-genmarshal; \
	rm -f $(GLIB_INSTALL_DIR)/glib-mkenums; \
	rm -f $(GLIB_INSTALL_DIR)/gobject-query; \
	rm -f $(GLIB_INSTALL_DIR)/gdbus-codegen; \
	rm -f $(GLIB_INSTALL_DIR)/gdbus; \
	rm -f $(GLIB_INSTALL_DIR)/gio-querymodules; \
	rm -f $(GLIB_INSTALL_DIR)/glib-compile-schemas; \
	rm -f $(GLIB_INSTALL_DIR)/gsettings; \
	rm -f $(GLIB_INSTALL_DIR)/glib-compile-resources 2> /dev/null; \
	ln -s /usr/local/bin/glib-compile-resources $(GLIB_INSTALL_DIR)/glib-compile-resources; \
	echo "build done" > ./$(SUBDIR_G_LIB)/.built; \
	fi \
	fi
	
	
mad_lib:
	if [ ! -e ./$(SUBDIR_MAD_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_MAD_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="-Os -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" ./configure --build=i686-pc-linux-gnu --enable-speed=yes --host=mips-linux --disable-debugging --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_MAD_LIB)/.built ]; then \
	make -C $(SUBDIR_MAD_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_MAD_LIB) install; \
	echo "build done" > ./$(SUBDIR_MAD_LIB)/.built; \
	fi \
	fi
	
ogg_lib:
	if [ ! -e ./$(SUBDIR_OGG_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_OGG_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" ./configure --build=i686-pc-linux-gnu --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_OGG_LIB)/.built ]; then \
	make -C $(SUBDIR_OGG_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_OGG_LIB) install; \
	echo "build done" > ./$(SUBDIR_OGG_LIB)/.built; \
	fi \
	fi

vorbis_lib:
	if [ ! -e ./$(SUBDIR_VOSBIS_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_VOSBIS_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" ./configure --build=i686-pc-linux-gnu --disable-oggtest --disable-examples --disable-docs --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_VOSBIS_LIB)/.built ]; then \
	make -C $(SUBDIR_VOSBIS_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_VOSBIS_LIB) install; \
	echo "build done" > ./$(SUBDIR_VOSBIS_LIB)/.built; \
	fi \
	fi

gtream_plugin_lib:
	if [ ! -e ./$(SUBDIR_GSTREAM_PLUGIN_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_GSTREAM_PLUGIN_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="-I$(CURRENT_DIR)/../shm $(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include $(MR_INCLUDE)" ALSA_CFLAGS="-I$(RSDK_LIB_DIR)/../include" ALSA_LIBS="-L$(RSDK_LIB_DIR)/../lib -lasound"  GST_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstbase-0.10 -lgstcheck-0.10 -lgstcontroller-0.10 -lgstdataprotocol-0.10 -lgstnet-0.10 -lgstreamer-0.10" GST_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER)" LDFLAGS="-L$(CURRENT_DIR)/../shm -lwfshm $(MR_LIBS) -L$(GLIB_INSTALL_DIR)/../lib -lgstbase-0.10 -lgstcheck-0.10 -lgstcontroller-0.10 -lgstdataprotocol-0.10 -lgstnet-0.10 -lgstreamer-0.10 -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0 -lintl -liconv -lgthread-2.0 -lffi -lz" ./configure --build=i686-pc-linux-gnu --host=mips-linux  --disable-valgrind --disable-freetypetest --disable-ffmpegcolorspace --disable-nls --disable-examples --disable-x --with-audioresample-format=int --disable-xvideo --enable-introspection=no --disable-xshm --disable-theora --disable-oggtest --disable-vorbistest --disable-cdparanoia --disable-gst_v4l --disable-xshm --disable-xvideo --disable-videotestsrc --disable-videorate --disable-videoscale  --disable-gdp --disable-pango --disable-debug --disable-libvisual --disable-encoding --disable-subparse --disable-ivorbis --enable-static=yes --disable-gio --disable-rpath --disable-gnome_vfs --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GSTREAM_PLUGIN_LIB)/.built ]; then \
	make -C $(SUBDIR_GSTREAM_PLUGIN_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GSTREAM_PLUGIN_LIB) install; \
	fi \
	fi

gtream_goodplugin_lib:
	if [ ! -e ./$(SUBDIR_GSTREAM_GOODPLUGIN_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_GSTREAM_GOODPLUGIN_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include" GLIB_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/glib-2.0 -I$(GLIB_INSTALL_DIR)/../lib/glib-2.0/include" GLIB_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0" GST_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstbase-0.10 -lgstcheck-0.10 -lgstcontroller-0.10 -lgstdataprotocol-0.10 -lgstnet-0.10 -lgstreamer-0.10" GST_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_BASE_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_CHECK_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_CONTROLLER_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) SOUP_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/libsoup-2.4 SOUP_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lsoup-2.4" LDFLAGS="-L$(GLIB_INSTALL_DIR)/../lib -lgstbase-0.10 -lgstcheck-0.10 -lgstcontroller-0.10 -lgstdataprotocol-0.10 -lgstnet-0.10 -lgstreamer-0.10 -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0 -lintl -liconv -lgthread-2.0 -lffi -lz" ./configure --build=i686-pc-linux-gnu --host=mips-linux  --disable-nls --disable-static --disable-examples  --disable-jpeg --disable-libdv --disable-shout2 --disable-speex --disable-bz2 --disable-matroska --disable-gdk_pixbuf --disable-gconf --disable-esdtest --disable-esd --disable-cairo_gobject --disable-cairo --disable-annodex --disable-aalibtest --disable-aalib --disable-xvideo --disable-xshm --disable-x --disable-gst_v4l2 --disable-osx_video --disable-osx_audio --disable-sunaudio --disable-oss4 --disable-oss --disable-y4m --disable-videomixer --disable-videocrop --disable-videobox --disable-spectrum --disable-smpte --disable-shapewipe --disable-imagefreeze --disable-goom2k1 --disable-goom --disable-flx --disable-videofilter --disable-flv --disable-avi --disable-auparse --disable-audiofx --disable-alpha --disable-libpng --disable-dv1394 --disable-valgrind --disable-gconftool --disable-cutter --disable-debugutils --disable-deinterlace --disable-effectv --disable-wavpack --disable-pulse --disable-libcaca --disable-jack --disable-hal --disable-wavenc --disable-udp --disable-rtp --disable-rtpmanager --disable-rtsp --disable-multifile --disable-multipart --disable-replaygain --disable-debug --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GSTREAM_GOODPLUGIN_LIB)/.built ]; then \
	make -C $(SUBDIR_GSTREAM_GOODPLUGIN_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GSTREAM_GOODPLUGIN_LIB) install; \
	echo "build done" > ./$(SUBDIR_GSTREAM_GOODPLUGIN_LIB)/.built; \
	fi \
	fi
	   

gtream_uglyplugin_lib:
	if [ ! -e ./$(SUBDIR_GSTREAM_UGLYPLUGIN_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_GSTREAM_UGLYPLUGIN_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include" GLIB_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0" GST_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstbase-0.10 -lgstcheck-0.10 -lgstcontroller-0.10 -lgstdataprotocol-0.10 -lgstnet-0.10 -lgstreamer-0.10" GST_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER)" MAD_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include" MAD_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lmad" GLIB_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/glib-2.0 -I$(GLIB_INSTALL_DIR)/../lib/glib-2.0/include" GST_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_BASE_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_CHECK_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_CONTROLLER_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) ./configure --build=i686-pc-linux-gnu --disable-nls --disable-static --host=mips-linux  --disable-examples  --disable-dvdsub --disable-iec958 --disable-synaesthesia --disable-a52dec --disable-amrnb --disable-amrwb --disable-cdio --disable-dvdread --disable-sidplay --disable-x264 --disable-lame --disable-twolame --disable-sidplay  --disable-realmedia --disable-synaesthesia  --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GSTREAM_UGLYPLUGIN_LIB)/.built ]; then \
	make -C $(SUBDIR_GSTREAM_UGLYPLUGIN_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GSTREAM_UGLYPLUGIN_LIB) install; \
	echo "build done" > ./$(SUBDIR_GSTREAM_UGLYPLUGIN_LIB)/.built; \
	fi \
	fi

av_lib:
	if [ ! -e ./$(SUBDIR_AV_LIB)/Configured_Done ]; then \
	cd ./$(SUBDIR_AV_LIB); \
	LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" ./configure --enable-cross-compile \
		--enable-shared --disable-doc --disable-ffmpeg --disable-doc --disable-avconv --disable-avplay \
			--disable-avprobe  --disable-avserver \
			--enable-pic --disable-encoder=flac --disable-decoder=cavs \
			--disable-protocols --disable-network --disable-hwaccels --disable-filters --disable-doc \
			--enable-optimizations --enable-gpl --enable-cross-compile --target-os=linux \
			--arch=mips --cross-prefix=mips-linux- --disable-yasm --disable-vis --disable-neon --disable-mmi \
			--disable-iwmmxt --disable-armvfp --disable-armv6t2 --disable-armv6 --disable-armv5te --disable-avx \
			--disable-ssse3 --disable-sse --disable-mmx2 --disable-mmx --disable-amd3dnowext --disable-amd3dnow \
			--disable-altivec  --disable-everything --disable-demuxers --enable-demuxer=ape  --disable-parsers \
			--disable-filters --disable-indevs --disable-outdev=oss --disable-outdev=sndio \
			--disable-decoders --enable-decoder=alac,wmav1,wmav2,wmapro,wmavoice,ape \
			--disable-hwaccels --disable-bsfs --disable-muxers --disable-encoders --disable-protocols  --disable-dxva2 --disable-rdft \
			--disable-lpc --disable-huffman --disable-swscale-alpha --disable-fastdiv --enable-small --disable-aandct --prefix=$(GLIB_INSTALL_DIR)/..; \
	echo "configured done" > ./Configured_Done; \
	cd ..; \
	fi
	if [ ! -e ./$(SUBDIR_AV_LIB)/.built ]; then \
	make -C $(SUBDIR_AV_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_AV_LIB) install; \
	echo "build done" > ./$(SUBDIR_AV_LIB)/.built; \
	fi \
	fi
	
	
gtream_ffmpegplugin_lib:
	if [ ! -e ./$(SUBDIR_GSTREAM_FFMPEG_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_GSTREAM_FFMPEG_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include" SWSCALE_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include" SWSCALE_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lswscale" POSTPROC_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include" POSTPROC_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lpostproc" FFMPEG_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include" FFMPEG_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lavcodec -lavdevice -lavutil -lavformat -lavfilter" GST_BASE_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstbase-0.10" GST_BASE_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_CHECK_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstcheck-0.10" GST_CHECK_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_PLUGINS_BASE_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstapp-0.10 -lgstaudio-0.10 -lgstcdda-0.10 -lgstfft-0.10 -lgstinterfaces-0.10 -lgstnetbuffer-0.10 -lgstpbutils-0.10 -lgstriff-0.10" GST_PLUGINS_BASE_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GLIB_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/glib-2.0 -I$(GLIB_INSTALL_DIR)/../lib/glib-2.0/include" GST_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_BASE_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_CHECK_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_CONTROLLER_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) ./configure --build=i686-pc-linux-gnu --host=mips-linux --disable-valgrind --enable-shared=yes  --enable-lgpl --with-system-ffmpeg --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GSTREAM_FFMPEG_LIB)/.built ]; then \
	make -C $(SUBDIR_GSTREAM_FFMPEG_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GSTREAM_FFMPEG_LIB) install; \
	echo "build done" > ./$(SUBDIR_GSTREAM_FFMPEG_LIB)/.built; \
	fi \
	fi

gtream_badplugin_lib:
	if [ ! -e ./$(SUBDIR_GSTREAM_BADPLUGIN_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_GSTREAM_BADPLUGIN_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include" GLIB_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/glib-2.0" \
		GLIB_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0" GST_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstbase-0.10 -lgstcheck-0.10 -lgstcontroller-0.10 -lgstdataprotocol-0.10 -lgstnet-0.10 -lgstreamer-0.10" \
		GST_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER)" LIBS="-L$(GLIB_INSTALL_DIR)/../lib -ldts_pic -ldca" GST_PLUGINS_BASE_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstapp-0.10 -lgstaudio-0.10 -lgstcdda-0.10 -lgstfft-0.10 -lgstinterfaces-0.10 -lgstnetbuffer-0.10 -lgstpbutils-0.10 -lgstriff-0.10" \
		GST_PLUGINS_BASE_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lglib-2.0" GLIB_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/glib-2.0 -I$(GLIB_INSTALL_DIR)/../lib/glib-2.0/include" GST_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstreamer-0.10" GST_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_BASE_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstbase-0.10" GST_BASE_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_CHECK_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstcheck-0.10" GST_CHECK_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER) GST_CONTROLLER_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lgstcontroller-0.10" GST_CONTROLLER_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER)  LDFLAGS="-L$(GLIB_INSTALL_DIR)/../lib -lgstbase-0.10 -lgstcheck-0.10 -lgstcontroller-0.10 -lgstdataprotocol-0.10 -lgstnet-0.10 -lgstreamer-0.10 -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0 -lintl -liconv -lgthread-2.0 -lffi -lz" ./configure --build=i686-pc-linux-gnu --host=mips-linux  --disable-examples  --prefix=$(GLIB_INSTALL_DIR)/.. --disable-nls --enable-dts --disable-asfmux --disable-audiovisualizers --disable-autoconvert --disable-bayer --disable-camerabin --disable-camerabin2 --disable-cdxaparse --disable-coloreffects --disable-colorspace  --disable-dataurisrc --disable-dccp --disable-debugutils --disable-dtmf --disable-dvbsuboverlay --disable-dvdspu --disable-faceoverlay --disable-festival --disable-fieldanalysis --disable-freeze --disable-freeverb --disable-frei0r --disable-gaudieffects --disable-geometrictransform --disable-h264parse --disable-hdvparse --disable-hls --disable-id3tag --disable-inter --disable-interlace --disable-ivfparse --disable-jp2kdecimator --disable-jpegformat --disable-librfb --disable-liveadder --disable-mpegpsmux --disable-mve --disable-mxf --disable-nsf --disable-nuvdemux --disable-patchdetect --disable-pcapparse --disable-pnm --disable-rawparse --disable-real --disable-removesilence --disable-rtpmux --disable-rtpvp8 --disable-scaletempo --disable-sdi --disable-sdp --disable-segmentclip --disable-siren --disable-smooth --disable-speed --disable-subenc --disable-stereo --disable-tta --disable-videofilters --disable-videomaxrate --disable-videomeasure --disable-videoparsers --disable-videosignal  --disable-vmnc --disable-y4m --disable-directsound --disable-direct3d --disable-directdraw --disable-apple_media --disable-osx_video --disable-avc --disable-quicktime --disable-shm --disable-vcd --disable-assrender --disable-voamrwbenc --disable-voaacenc --disable-apexsink --disable-bz2 --disable-cdaudio --disable-celt --disable-cog --disable-curl --disable-dc1394 --disable-decklink --disable-directfb --disable-dirac --disable-divx --disable-resindvd --disable-fbdev --disable-flite --disable-gsm --disable-jp2k --disable-kate --disable-ladspa --disable-lv2 --disable-linsys --disable-modplug --disable-mimic --disable-mpeg2enc --disable-mplex --disable-musepack --disable-musicbrainz --disable-mythtv --disable-nas --disable-neon --disable-ofa --disable-openal --disable-opencv --disable-opus --disable-pvr --disable-rsvg --disable-timidity --disable-teletextdec --disable-wildmidi --disable-sdl --disable-sdltest --disable-sndfile --disable-soundtouch --disable-spc --disable-gme  --disable-swfdec  --disable-xvid --disable-dvb --disable-wininet --disable-acm --disable-vdpau --disable-schro --disable-zbar --disable-vp8 --disable-rtmp --disable-spandsp --disable-gsettings  --disable-schemas-compile  --with-x=no --with-pvr-external-headers=no --disable-valgrind --disable-debug --disable-mpegtsmux --disable-mpegpsmux --disable-mpegvideoparse --disable-adpcmenc --disable-debug --disable-legacyresample --disable-mpegtsdemux; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GSTREAM_BADPLUGIN_LIB)/.built ]; then \
	make -C $(SUBDIR_GSTREAM_BADPLUGIN_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GSTREAM_BADPLUGIN_LIB) install; \
	echo "build done" > ./$(SUBDIR_GSTREAM_BADPLUGIN_LIB)/.built; \
	fi \
	fi
	

flac_lib:
	if [ ! -e ./$(SUBDIR_FLAC_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_FLAC_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include" ./configure --build=i686-pc-linux-gnu --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..  --disable-3dnow --disable-altivec --disable-thorough-tests --disable-xmms-plugin --disable-cpplibs  --disable-ogg --disable-oggtest; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_FLAC_LIB)/.built ]; then \
	make -C $(SUBDIR_FLAC_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_FLAC_LIB) install; \
	echo "build done" > ./$(SUBDIR_FLAC_LIB)/.built; \
	fi \
	fi 
	
faac_lib:
	if [ ! -e ./$(SUBDIR_FAAC_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_FAAC_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include" ./configure --build=i686-pc-linux-gnu --host=mips-linux  --with-mp4v2=no --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_FLAC_LIB)/.built ]; then \
	make -C $(SUBDIR_FAAC_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_FAAC_LIB) install	; \
	echo "build done" > ./$(SUBDIR_FAAC_LIB)/.built; \
	fi \
	fi
	
faad_lib:
	if [ ! -e ./$(SUBDIR_FAAD_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_FAAD_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include" ./configure --build=i686-pc-linux-gnu --enable-shared --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_FAAD_LIB)/.built ]; then \
	make -C $(SUBDIR_FAAD_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_FAAD_LIB) install; \
	echo "build done" > ./$(SUBDIR_FAAD_LIB)/.built; \
	fi \
	fi
	
dca_lib:
	if [ ! -e ./$(SUBDIR_DCA_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_DCA_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include" ./configure --disable-al-audio --disable-solaris-audio --disable-oss --enable-fixed --disable-win --build=i686-pc-linux-gnu --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_DCA_LIB)/.built ]; then \
	make -C $(SUBDIR_DCA_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_DCA_LIB) install; \
	rm -f $(GLIB_INSTALL_DIR)/../lib/libdts_pic.so; \
	rm -f $(GLIB_INSTALL_DIR)/../lib/libdts_pic.so.0; \
	rm -f $(GLIB_INSTALL_DIR)/../lib/libdts_pic.so.0.0.0; \
	cp -pf $(GLIB_INSTALL_DIR)/../lib/libdca.so.0.0.0 $(GLIB_INSTALL_DIR)/../lib/libdts_pic.so.0.0.0; \
	ln -s libdts_pic.so.0.0.0 $(GLIB_INSTALL_DIR)/../lib/libdts_pic.so.0; \
	ln -s libdts_pic.so.0.0.0 $(GLIB_INSTALL_DIR)/../lib/libdts_pic.so; \
	echo "build done" > ./$(SUBDIR_DCA_LIB)/.built; \
	fi \
	fi
	
soup_lib:
	if [ ! -e ./$(SUBDIR_SOUP_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_SOUP_LIB); \
		touch ./Makefile.in; \
		touch ./configure; \
		touch ./config.h.in; \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include" LIBS="-L$(GLIB_INSTALL_DIR)/../lib -liconv" XML_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/libxml2" XML_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lxml2" ./configure --build=i686-pc-linux-gnu --host=mips-linux --enable-debug=no --disable-glibtest --enable-gtk-doc-html=no --without-apache-httpd --enable-introspection=no  --disable-tls-check --prefix=$(GLIB_INSTALL_DIR)/.. --enable-gtk-doc-html=no  --disable-glibtest --enable-gtk-doc=no --without-ntlm-auth --without-gnome; \
		echo "configured done" > ./Configured_Done; \
		touch ./Makefile; \
		touch ./config.h; \
	fi
	if [ ! -e ./$(SUBDIR_SOUP_LIB)/.built ]; then \
	make -C $(SUBDIR_SOUP_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_SOUP_LIB) install; \
	echo "build done" > ./$(SUBDIR_SOUP_LIB)/.built; \
	fi \
	fi

gtream_lib:
	if [ ! -e ./$(SUBDIR_GSTREAM_LIB)/Configured_Done ]; then \
		cd ./$(SUBDIR_GSTREAM_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="-I$(CURRENT_DIR)/../shm $(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include" LDFLAGS="-L$(CURRENT_DIR)/../shm -lwfshm" GLIB_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/glib-2.0" GLIB_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0"  LIBS="-L$(GLIB_INSTALL_DIR)/../lib -liconv -lgthread-2.0 -lffi -lz -lintl" LDFLAGS="-L$(CURRENT_DIR)/../shm -lwfshm -L$(GLIB_INSTALL_DIR)/../lib -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0 -lintl -liconv -lgthread-2.0 -lffi -lz" ./configure --build=i686-pc-linux-gnu  --host=mips-linux  --exec-prefix=$(GLIB_INSTALL_DIR)/.. --prefix=$(GLIB_INSTALL_DIR)/.. --disable-nls --disable-valgrind --disable-static --disable-gobject-cast-checks  --enable-binary-registry --disable-trace --disable-tests  --disable-failing-tests --disable-debug --disable-loadsave --enable-static=yes --enable-introspection=no; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GSTREAM_LIB)/.built ]; then \
	make -C $(SUBDIR_GSTREAM_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GSTREAM_LIB) install; \
	echo "build done" > ./$(SUBDIR_GSTREAM_LIB)/.built; \
	fi \
	fi
	

gee_lib:
	if [ ! -e ./$(SUBDIR_GEE_LIB)/Configured_Done ]; then \
		cd $(SUBDIR_GEE_LIB); \
		find -name "*.stamp" -exec touch {} \; ; \
		touch ./Makefile.in; \
		touch ./configure; \
		touch ./config.h.in; \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" GLIB_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/glib-2.0" GLIB_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0" LDFLAGS="-L$(GLIB_INSTALL_DIR)/../lib -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0 -lintl -liconv -lgthread-2.0 -lffi -lz" ./configure --build=i686-pc-linux-gnu --host=mips-linux --enable-static=yes --enable-shared=no --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
		touch ./Makefile; \
		touch ./config.h; \
	fi
	if [ ! -e ./$(SUBDIR_GEE_LIB)/.built ]; then \
	make -C $(SUBDIR_GEE_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GEE_LIB) install; \
	echo "build done" > ./$(SUBDIR_GEE_LIB)/.built; \
	fi \
	fi
gssdp_lib:
	if [ ! -e ./$(SUBDIR_GSSDP_LIB)/Configured_Done ]; then \
		cd $(SUBDIR_GSSDP_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include -I$(GLIB_INSTALL_DIR)/../include/libsoup-2.4" LDFLAGS="-L$(GLIB_INSTALL_DIR)/../lib -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgio-2.0 -lintl -liconv -lgthread-2.0 -lffi -lz" ./configure --build=i686-pc-linux-gnu --without-gtk --enable-gtk-doc-html=no --enable-introspection=no --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GSSDP_LIB)/.built ]; then \
	make -C $(SUBDIR_GSSDP_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GSSDP_LIB) install; \
	echo "build done" > ./$(SUBDIR_GSSDP_LIB)/.built; \
	fi \
	fi
	
gupnp_lib:
	if [ ! -e ./$(SUBDIR_GUPNP_LIB)/Configured_Done ]; then \
		cd $(SUBDIR_GUPNP_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include" LIBGUPNP_CFLAGS="-pthread -I$(GLIB_INSTALL_DIR)/../include/glib-2.0 -I$(GLIB_INSTALL_DIR)/../lib/glib-2.0/include -I$(GLIB_INSTALL_DIR)/../include/gssdp-1.0 -I$(GLIB_INSTALL_DIR)/../include/libsoup-2.4 -I$(GLIB_INSTALL_DIR)/../include/libxml2 -I$(GLIB_INSTALL_DIR)/../include" LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lintl -liconv -lffi -lz -lxml2 -lglib-2.0 -lgio-2.0 -lgthread-2.0 -lgmodule-2.0 -lgobject-2.0 -L$(GLIB_INSTALL_DIR)/../lib -luuid -l$(GSTREAMER_VER)" ./configure --with-context-manager=linux --oldincludedir=$(GLIB_INSTALL_DIR)/../include --enable-introspection=no --enable-gtk-doc-html=no --build=i686-pc-linux-gnu --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GUPNP_LIB)/.built ]; then \
	make -C $(SUBDIR_GUPNP_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GUPNP_LIB) install; \
	echo "build done" > ./$(SUBDIR_GUPNP_LIB)/.built; \
	fi \
	fi

gupnp_av_lib:
	if [ ! -e ./$(SUBDIR_GUPNP_AV_LIB)/Configured_Done ]; then \
		cd $(SUBDIR_GUPNP_AV_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include/gupnp-1.0" LIBGUPNP_CFLAGS="-pthread -I$(GLIB_INSTALL_DIR)/../include/glib-2.0 -I$(GLIB_INSTALL_DIR)/../lib/glib-2.0/include -I$(GLIB_INSTALL_DIR)/../include/gssdp-1.0 -I$(GLIB_INSTALL_DIR)/../include/libsoup-2.4 -I$(GLIB_INSTALL_DIR)/../include/libxml2 -I$(GLIB_INSTALL_DIR)/../include/gupnp-1.0" LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lintl -liconv -lffi -lz -lxml2 -lglib-2.0 -lgio-2.0 -lgthread-2.0 -lgmodule-2.0 -lgobject-2.0 -l$(GSTREAMER_VER) -lgupnp-1.0 -lgssdp-1.0 -lsoup-2.4" ./configure --oldincludedir=$(GLIB_INSTALL_DIR)/../include/gupnp-1.0 --enable-gtk-doc-html=no --build=i686-pc-linux-gnu --host=mips-linux --enable-introspection=no --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GUPNP_AV_LIB)/.built ]; then \
	make -C $(SUBDIR_GUPNP_AV_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GUPNP_AV_LIB) install; \
	cp -p ./fake_gupnp-dlna-1.0.pc $(GLIB_INSTALL_DIR)/../lib/pkgconfig/gupnp-dlna-1.0.pc; \
	echo "build done" > ./$(SUBDIR_GUPNP_AV_LIB)/.built; \
	fi \
	fi

gupnp_dlna_lib:
	if [ ! -e ./$(SUBDIR_GUPNP_DLNA_LIB)/Configured_Done ]; then \
		cd $(SUBDIR_GUPNP_DLNA_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" GST_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -l$(GSTREAMER_VER)" GST_CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/$(GSTREAMER_VER)" LIBXML_CFLAGS=-I$(GLIB_INSTALL_DIR)/../include/libxml2 LIBXML_LIBS="-L$(GLIB_INSTALL_DIR)/../lib -lxml2" ./configure --build=i686-pc-linux-gnu --enable-gtk-doc-html=no --host=mips-linux --enable-introspection=no --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_GUPNP_DLNA_LIB)/.built ]; then \
	make -C $(SUBDIR_GUPNP_DLNA_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_GUPNP_DLNA_LIB) install; \
	echo "build done" > ./$(SUBDIR_GUPNP_DLNA_LIB)/.built; \
	fi \
	fi

shared_mime_lib:
	if [ ! -e ./$(SUBDIR_SHARED_MIME_LIB)/Configured_Done ]; then \
		cd $(SUBDIR_SHARED_MIME_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="-I$(GLIB_INSTALL_DIR)/../include/glib-2.0 -I$(GLIB_INSTALL_DIR)/../include/libxml2" CPPFLAGS="-I$(GLIB_INSTALL_DIR)/../include" LDFLAGS="-L$(GLIB_INSTALL_DIR)/../lib -liconv -lintl -lz -lffi -lglib-2.0 -lgthread-2.0 -lgmodule-2.0 -lgobject-2.0 -l$(GSTREAMER_VER)" ./configure --build=i686-pc-linux-gnu --host=mips-linux --disable-nls --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_SHARED_MIME_LIB)/.built ]; then \
	cp -pf ./freedesktop.org.xml ./$(SUBDIR_SHARED_MIME_LIB)/freedesktop.org.xml; \
	make -C $(SUBDIR_SHARED_MIME_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_SHARED_MIME_LIB) install; \
	/usr/bin/update-mime-database $(GLIB_INSTALL_DIR)/../share/mime; \
	echo "build done" > ./$(SUBDIR_SHARED_MIME_LIB)/.built; \
	fi \
	fi

mms_lib:
	if [ ! -e ./$(SUBDIR_MMS_LIB)/Configured_Done ]; then \
		cd $(SUBDIR_MMS_LIB); \
		LD="mips-linux-ld" CC="msdk-linux-gcc -fPIC" CFLAGS="$(GCC_OPTIMIZATION) -I$(GLIB_INSTALL_DIR)/../include -I$(RSDK_LIB_DIR)/../include" GLIB_CFLAGS="-I$(GLIB_INSTALL_DIR)/../lib/glib-2.0/include -I$(GLIB_INSTALL_DIR)/../include/glib-2.0" GLIB_LIBS=-L$(GLIB_INSTALL_DIR)/../lib ./configure --build=i686-pc-linux-gnu --host=mips-linux --prefix=$(GLIB_INSTALL_DIR)/..; \
		echo "configured done" > ./Configured_Done; \
	fi
	if [ ! -e ./$(SUBDIR_MMS_LIB)/.built ]; then \
	make -C $(SUBDIR_MMS_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_MMS_LIB) install; \
	echo "build done" > ./$(SUBDIR_MMS_LIB)/.built; \
	fi \
	fi
	
romfs:
	chmod 755 $(GLIB_INSTALL_DIR)/../lib/*.so
	cp -R $(GLIB_INSTALL_DIR)/../lib/*.so $(DIR_ROMFS)/lib
	cp -R $(GLIB_INSTALL_DIR)/../lib/*.so.* $(DIR_ROMFS)/lib
ifeq ($(INCLUDE_DLNA), 1)
	rm -f $(RENDER_INSTALL_DIR)/lib/librygel-server-1.0*
	rm -Rf $(DIR_ROMFS)/var/Dlna_Rygel
	chmod 755 $(RENDER_INSTALL_DIR)/lib/rygel-1.0/*.so
	cp -R $(RENDER_INSTALL_DIR)/lib/rygel-1.0/*.so $(DIR_ROMFS)/lib
endif
	cp ./asound.conf $(DIR_ROMFS)/etc/asound.conf
	$(ROMFSINST) ./$(SUBDIR_GSTREAM_LIB)/libs/gst/helpers/.libs/gst-plugin-scanner /bin/gst-plugin-scanner
	mkdir -p $(DIR_ROMFS)/etc/$(GSTREAMER_VER)
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstwavparse.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstalsa.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstaudioconvert.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstaudioparsers.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstaudiorate.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstaudioresample.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstautodetect.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstcoreelements.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstcoreindexers.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstdecodebin2.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstdecodebin.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstid3demux.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstinterleave.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstmad.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstmpegaudioparse.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstplaybin.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstsouphttpsrc.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgsttcp.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgsttypefindfunctions.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstvolume.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstfaad.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	##DEBUG
	#cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstdebug.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstapp.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstffmpeg.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstogg.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstvorbis.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstadpcmdec.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstaiff.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstflac.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstisomp4.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstasf.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	##Demux ICY tags from a stream for internet radio
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgsticydemux.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	##(MMS) protocol source from a stream
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstmms.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	##(MPEG demuxer) 
	cp -pf $(GLIB_INSTALL_DIR)/../lib/$(GSTREAMER_VER)/libgstmpegdemux.so $(DIR_ROMFS)/etc/$(GSTREAMER_VER)/
	
ifeq ($(INCLUDE_DLNA), 1)
	$(ROMFSINST) -s /var/rygel-1.0 /etc/rygel-1.0
	mkdir -p $(DIR_ROMFS)/usr/Dlna_Rygel
	mkdir -p $(DIR_ROMFS)/usr/Dlna_Rygel/
	mkdir -p $(DIR_ROMFS)/usr/Dlna_Rygel/share
	mkdir -p $(DIR_ROMFS)/usr/Dlna_Rygel/share/icons
	mkdir -p $(DIR_ROMFS)/usr/Dlna_Rygel/share/icons/hicolor
	mkdir -p $(DIR_ROMFS)/usr/Dlna_Rygel/share/rygel
	
	cp -Rf $(RENDER_INSTALL_DIR)/share/applications $(DIR_ROMFS)/usr/Dlna_Rygel/share

	cp -Rf $(RENDER_INSTALL_DIR)/share/rygel/xml $(DIR_ROMFS)/usr/Dlna_Rygel/share/rygel
	cp -Rf $(RENDER_INSTALL_DIR)/share/rygel/icons $(DIR_ROMFS)/usr/Dlna_Rygel/share/rygel
	cp -Rf $(RENDER_INSTALL_DIR)/share/vala $(DIR_ROMFS)/usr/Dlna_Rygel/share
	cp -Rf $(RENDER_INSTALL_DIR)/share/icons/hicolor/128x128 $(DIR_ROMFS)/usr/Dlna_Rygel/share/icons/hicolor
	cp -Rf $(RENDER_INSTALL_DIR)/share/icons/hicolor/32x32 $(DIR_ROMFS)/usr/Dlna_Rygel/share/icons/hicolor
	cp -Rf $(RENDER_INSTALL_DIR)/share/icons/hicolor/48x48 $(DIR_ROMFS)/usr/Dlna_Rygel/share/icons/hicolor
	
	mkdir $(DIR_ROMFS)/usr/Dlna_Rygel/lib
	mkdir $(DIR_ROMFS)/usr/Dlna_Rygel/lib/rygel-1.0
	cp -pf $(RENDER_INSTALL_DIR)/lib/rygel-1.0/librygel-playbin.so $(DIR_ROMFS)/usr/Dlna_Rygel/lib/rygel-1.0

	$(ROMFSINST) $(RENDER_INSTALL_DIR)/bin/rygel /usr/bin/rygel
	mkdir $(DIR_ROMFS)/usr/Dlna_Rygel/config

	cp -pf $(CURRENT_DIR)/rygel.conf $(DIR_ROMFS)/usr/Dlna_Rygel/config/rygel.conf
	cp -pf $(CURRENT_DIR)/Playbin.xml $(DIR_ROMFS)/usr/Dlna_Rygel/config/Playbin.xml
	mkdir $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime
	cp -Rf $(GLIB_INSTALL_DIR)/../share/mime/application $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/application
	cp -Rf $(GLIB_INSTALL_DIR)/../share/mime/audio $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/audio
	cp -Rf $(GLIB_INSTALL_DIR)/../share/mime/video $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/video
	cp -Rf $(GLIB_INSTALL_DIR)/../share/mime/image $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/image
	cp -Rf $(GLIB_INSTALL_DIR)/../share/mime/text $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/text
	cp -Rf $(GLIB_INSTALL_DIR)/../share/mime/x-content $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/x-content

	cp -f $(GLIB_INSTALL_DIR)/../share/mime/aliases $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/aliases
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/generic-icons $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/generic-icons
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/globs $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/globs
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/globs2 $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/globs2
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/icons $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/icons
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/magic $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/magic
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/mime.cache $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/mime.cache
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/subclasses $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/subclasses
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/treemagic $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/treemagic
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/types $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/types
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/version $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/version
	cp -f $(GLIB_INSTALL_DIR)/../share/mime/XMLnamespaces $(DIR_ROMFS)/usr/Dlna_Rygel/share/mime/XMLnamespaces
	rm -rf $(RENDER_INSTALL_DIR)/bin
	rm -rf $(RENDER_INSTALL_DIR)/include
	rm -rf $(RENDER_INSTALL_DIR)/lib
	rm -rf $(RENDER_INSTALL_DIR)/share
endif
	
clean:
	rm -Rf $(GLIB_INSTALL_DIR)/../include
	rm -Rf $(GLIB_INSTALL_DIR)/../lib
	rm -Rf $(GLIB_INSTALL_DIR)/../man
	rm -Rf $(GLIB_INSTALL_DIR)/../share
	rm -Rf $(GLIB_INSTALL_DIR)/../sbin
	rm -Rf $(GLIB_INSTALL_DIR)/../etc
	rm -Rf $(GLIB_INSTALL_DIR)/../bin
	rm -Rf ./$(SUBDIR_AV_LIB)
	tar xvf ./libav-0.8.16.tar.gz
	rm -Rf ./$(SUBDIR_INTL_LIB)
	tar xvf ./gettext-0.18.1.1.tar.gz
	rm -Rf ./$(SUBDIR_GSTREAM_FFMPEG_LIB)
	tar xvf ./gst-ffmpeg-0.10.13.tar.gz
	
	for i in $(ALL_SUBDIR) ; do \
    		if [  -e ./$$i/.built ]; then \
    			echo "CLEAN $$i"; \
    			make -C ./$$i clean; \
    			rm -f ./$$i/.built; \
    		fi; \
	done
	ifeq ($(INCLUDE_DLNA), 1)
	make -C ./$(SUBDIR_RYGEL_RENDER) clean
	endif


distclean:
	rm -Rf $(GLIB_INSTALL_DIR)/../include
	rm -Rf $(GLIB_INSTALL_DIR)/../lib
	rm -Rf $(GLIB_INSTALL_DIR)/../man
	rm -Rf $(GLIB_INSTALL_DIR)/../share
	rm -Rf $(GLIB_INSTALL_DIR)/../sbin
	rm -Rf $(GLIB_INSTALL_DIR)/../etc
	rm -Rf $(GLIB_INSTALL_DIR)/../bin
	rm -Rf ./$(SUBDIR_AV_LIB)
	tar xvf ./libav-0.8.16.tar.gz
	rm -Rf ./$(SUBDIR_INTL_LIB)
	tar xvf ./gettext-0.18.1.1.tar.gz
	rm -Rf ./$(SUBDIR_GSTREAM_FFMPEG_LIB)
	tar xvf ./gst-ffmpeg-0.10.13.tar.gz
	
	for i in $(ALL_SUBDIR) ; do \
    		if [  -e ./$$i/Configured_Done ]; then \
    			echo "CLEAN $$i"; \
    			make -C ./$$i distclean; \
    			rm -f ./$$i/.built; \
    			rm -f ./$$i/Configured_Done; \
    		fi; \
    		rm -f ./$$i/.built; \
	done
ifeq ($(INCLUDE_DLNA), 1)
	make -C ./$(SUBDIR_RYGEL_RENDER) distclean
	rm -f ./$(SUBDIR_RYGEL_RENDER)/Configured_Done
endif
	rm -f ./$(SUBDIR_Z_LIB)/Makefile
	
	
	
