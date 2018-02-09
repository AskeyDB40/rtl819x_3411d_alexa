
DIR_USERS := ..
include $(DIR_USERS)/.config

DIR_KERNEL := ../../linux-3.10
include $(DIR_KERNEL)/.config

ALL_SUBDIR =
SUBDIR_SHM = shm
SUBDIR_DLNA = dlna_renderer
SUBDIR_CURL = curl
SUBDIR_NETRADIO = internet_radio
SUBDIR_AVSALEXA = avs

APP=
APP_ROMFS=

APP = prog_shm
APP_ROMFS = romfs_shm
ALL_SUBDIR += $(SUBDIR_SHM)

ifeq ($(CONFIG_DLNA_RENDERER_SUPPORT),y)
APP += prog_dlna_renderer
APP_ROMFS += romfs_dlna_renderer
ALL_SUBDIR += $(SUBDIR_DLNA)
else
ifeq ($(CONFIG_INTERNET_RADIO_SUPPORT),y)
APP += prog_dlna_renderer
APP_ROMFS += romfs_dlna_renderer
ALL_SUBDIR += $(SUBDIR_DLNA)
endif
endif

APP += prog_curl
APP_ROMFS += romfs_curl
ALL_SUBDIR += $(SUBDIR_CURL)

ifeq ($(CONFIG_INTERNET_RADIO_SUPPORT),y)
APP += prog_internet_radio
APP_ROMFS += romfs_internet_radio
ALL_SUBDIR += $(SUBDIR_NETRADIO)
endif

ifeq ($(CONFIG_AMAZON_ALEXA_SUPPORT),y)
APP += prog_avs
APP_ROMFS += romfs_avs
ALL_SUBDIR += $(SUBDIR_AVSALEXA)
endif

all:$(APP)


prog_shm:
	make -C ./shm
	
prog_dlna_renderer:
	make -C ./dlna_renderer

prog_internet_radio:
	make -C ./internet_radio
	
prog_curl:
	make -C ./curl

prog_avs:
	make -C ./avs
	

romfs:$(APP_ROMFS)


romfs_shm:
	make -C ./shm romfs
	
romfs_dlna_renderer:
	make -C ./dlna_renderer romfs

romfs_internet_radio:
	make -C ./internet_radio romfs
	
romfs_curl:
	make -C ./curl romfs
	
romfs_avs:
	make -C ./avs romfs
	
clean:
	for i in $(ALL_SUBDIR) ; do \
		echo "CLEAN $$i"; \
    		make -C ./$$i clean; \
    	done
	
distclean:
	make -C ./curl distclean
	make -C ./dlna_renderer distclean
