#ifndef INCLUDE_WFSHM_H
#define INCLUDE_WFSHM_H

int wfshm_sem_lock(void);
int wfshm_sem_unlock(void);
int wfshm_shm_free(void *shm_memory, int shm_key);
int wfshm_init(void);
int wfshm_set(int id, void *value);
int wfshm_get(int id, void *value);
void wfshm_Restore_setting(void);
unsigned int GetAudioSinkState(void);
#define WFSHM_TOKEN_OWNER	0
#define WFSHM_SERIAL_NUMBER	1

#define WFSHM_RTPSINK_SN		2
#define WFSHM_DLNA_SN		3
#define WFSHM_ASINK_COMP_SN		4
#define WFSHM_ASINKP_SN		5
#define WFSHM_NETRADIO_SN	6
#define WFSHM_AIRFUN_SN		7

#define WFSHM_RTPSINK_STATE	8
#define WFSHM_DLNA_STATE		9
#define WFSHM_ASINK_COMP_STATE		10
#define WFSHM_ASINKP_STATE	11
#define WFSHM_NETRADIO_STATE	12
#define WFSHM_AIRFUN_STATE	13

#define WFSHM_ISINITED		14
#define WFSHM_KILL_DONE		15
#define WFSHM_ALSA_RELEASE		16


#define WFSHM_PA_BT_SN		17
#define WFSHM_PA_BT_STATE		18
#define WFSHM_PA_BT_PLAYING_STATE		19
#define WFSHM_DLNA_BYPASS_ALSA 20
#define WFSHM_NETRADIO_BYPASS_ALSA 21
#define WFSHM_ASINKP_BYPASS_ALSA 22
#define WFSHM_BYPASS_ALSA_DONE 23

#define WFSHM_AMZ_ALSA_STATE 24
#define WFSHM_AMZ_PLAYBACK_SN 25
#define WFSHM_AMZ_PLAYBACK_STATE 26

typedef enum {
  STATE_VOID_PENDING	= 0,
  STATE_NULL			= 1,
  STATE_READY			= 2,
  STATE_PAUSED		= 3,
  STATE_PLAYING		= 4
} WF_State;

typedef enum {
  OWNED_IDLE			= 0,
  OWNED_RTPSINK		= 1,
  OWNED_DLNA_RENDER	= 2,
  OWNED_ASINK_COMP			= 3,
  OWNED_ASINKP		= 4,
  OWNED_AIRFUN		= 5,
  OWNED_NETRADIO	= 6,
  OWNED_PA_BT	= 7,
  OWNED_AMZ	= 8
} WF_OWNER;

typedef struct shm_setting {
	unsigned int token_owner;
	unsigned int serial_number;
	
	unsigned int rtpsink_sn;
	unsigned int dlna_sn;
	unsigned int asink_comp_sn;
	unsigned int asinkp_sn;
	unsigned int netradio_sn;
	unsigned int airfun_sn;
	
	unsigned int rtpsink_st;
	unsigned int dlna_st;
	unsigned int asink_comp_st;
	unsigned int asinkp_st;
	unsigned int netradio_st;
	unsigned int airfun_st;
	
	
	
	unsigned int IsInited;
	unsigned int kill_done;
	unsigned int alsa_release;
	
	unsigned int pa_bt_sn;
	unsigned int pa_bt_st;
	unsigned int pa_bt_playing;
	unsigned int dlna_bypass_alsa;
	unsigned int netradio_bypass_alsa;
	unsigned int asinkp_bypass_alsa;
	unsigned int bypass_alsa_done;
	
	unsigned int amz_alsa_state;
	unsigned int amz_playback_sn;
	unsigned int amz_playback_st;
	
	
}WFSHM_T, *WFSHM_Tp;

int wfshm_setMemory(WFSHM_Tp NewValue);
int wfshm_getMemory(WFSHM_Tp DestBuff);
unsigned int AnnocsStopWFOwner(void);
unsigned int GetAudioSinkState(void);
unsigned int AnnocsByPassALSA(void);
unsigned int PrivateAnnocsStopWFOwner(void);
unsigned int GetALLAudioSinkState(void);
#endif