ifeq ($(DIR_LINUX),)
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






SUBDIR_CURL_LIB=./curl-7.51.0


SUB_EXECS = 
CURL_LIB=curl_lib


ALL_DEPEND_LIB=
ALL_DEPEND_LIB += curl_lib
ZLIB_INCLUDE=-I$(CURRENT_DIR)/../dlna_renderer/Renderer_Install/include
CFLAGS += -Os -DTCP_NODELAY $(ZLIB_INCLUDE)


all: $(ALL_DEPEND_LIB)


curl_lib:
	if [ ! -e $(SUBDIR_CURL_LIB)/Configured_Done ]; then \
			cd $(SUBDIR_CURL_LIB); \
			CC='msdk-linux-gcc -fPIC' AR=msdk-linux-ar LD='msdk-linux-ld -shared' STRIP='msdk-linux-strip -S' RANDLIB=msdk-linux-ranlib LDFLAGS='-L$(RSDK_LIB_DIR)/../lib -lc -lm -ldl -lpthread -lrt ' CFLAGS="-Os -DTCP_NODELAY -I$(RSDK_LIB_DIR)/../include $(ZLIB_INCLUDE)" ./configure --with-zlib="$(CURRENT_DIR)/../dlna_renderer/Renderer_Install/lib"  --host=mips-linux --enable-shared --disable-manual --disable-gopher --disable-imap --disable-pop3 --disable-telnet --disable-tftp --disable-smtp --disable-ftp --disable-dict --without-nghttp2   --without-cyassl --without-nss --disable-ldap --disable-tftp --disable-proxy --without-axtls  --without-winssl --disable-tls-srp  --disable-cookies --disable-soname-bump --disable-ntlm-wb  --disable-crypto-auth --disable-sspi --disable-ipv6 --disable-manual --disable-smtp --disable-smb  --disable-imap --disable-pop3  --disable-dict --without-polarssl --without-zlib --without-ssl  --without-gnutls --without-mbedtls --without-ca-fallback --without-libssh2 --prefix=`pwd`/build; \
			echo "configured done" > ./Configured_Done; \
			cd ..;\
	fi
	make -C $(SUBDIR_CURL_LIB) && if [ $$? -eq 0 ]; then \
	make -C $(SUBDIR_CURL_LIB) install; \
	fi 
	cd $(SUBDIR_CURL_LIB)/docs/examples; \
	`$(CURRENT_DIR)/$(SUBDIR_CURL_LIB)/build/bin/curl-config --cc --cflags --libs` -o rtsp rtsp.c; \
	cd -;


romfs:
	cp -a $(SUBDIR_CURL_LIB)/build/lib/libcurl.so* $(DIR_ROMFS)/lib
	$(ROMFSINST) $(SUBDIR_CURL_LIB)/build/bin/curl /bin/curl
	

clean:
	make -C $(SUBDIR_CURL_LIB) clean
	rm -rf $(SUBDIR_CURL_LIB)/build
	rm $(SUBDIR_CURL_LIB)/.built

distclean:
	make -C $(SUBDIR_CURL_LIB) distclean
	rm -rf $(SUBDIR_CURL_LIB)/build
	rm $(SUBDIR_CURL_LIB)/.built
