CURRENT_DIR=$(shell pwd)

ifeq ($(wildcard $(DIR_LINUX)/.config),)
include ../../../../linux-3.10/.config
else
include $(DIR_LINUX)/.config
endif
#get rsdk dir
include ../../../.config
RSDK_LIB_DIR=$(shell  echo $(PATH) | cut -f2 -d:)
ifdef CONFIG_RSDKDIR
RSDK_LIB_DIR=$(CURRENT_DIR)/../../../../$(CONFIG_RSDKDIR)/bin
endif


all:
	echo "Do Nothing"

romfs:
	$(ROMFSINST) ./alexa /bin/alexa
	$(ROMFSINST) ./auth_web /bin/auth_web

clean:
	echo "Do Nothing"
	

