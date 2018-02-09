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




all: 
	make -C ./alexa

romfs:
	make -C ./alexa romfs

clean:
	make -C ./alexa clean

