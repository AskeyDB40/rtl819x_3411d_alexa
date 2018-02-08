#ifndef __AUDIOEVENT_NETLINK_H
#define __AUDIOEVENT_NETLINK_H

#define UNIX_SOCK_PATH "/tmp/mysocket"



struct audio_event_task {
	struct task_struct *thread;
	struct completion thread_done;
	char name[16];
	void (*loop_ops)(struct audio_event_task *);
#if(LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0))
	spinlock_t lock;
#endif
};

enum {
    	NL_RESERVED=0,          // reserved
    	NL_USER_REG=1,          // register a NL service
	NL_GPIO_PROBE=2,
	NL_LED_ON_OFF=3,
	NL_LED_BLINKING=4,
	NL_USER_UN_REG = 5
};
enum {
    WFD_USERID_WFAUDIO=0
};

enum {
    GPIO_TIME_SHORT=0,
    GPIO_TIME_LONG=1
};

struct audio_event_nl_hdr {
    unsigned short msgtype;
    unsigned short msglen;
};

struct audio_event_nl_reg {
    struct audio_event_nl_hdr hdr;
    unsigned int pid;
    unsigned int userid;
};
struct audio_event_nl_gpio_state {
    struct audio_event_nl_hdr hdr;
    unsigned int  gpio_state;
};

struct audio_event_nl_led_blinking {
    struct audio_event_nl_hdr hdr;
    unsigned int  led_blinking;
    unsigned int frequency;
};

struct audio_event_nl_led_on_off {
    struct audio_event_nl_hdr hdr;
    unsigned int  led_on_off;
};

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,15)
#define NLMSG_MIN_TYPE		0x10
#endif
#define NLMSG_TYPE_AUDIO_EVENT    (NLMSG_MIN_TYPE+3)
#define NETLINK_RTK_AUDIO_EVENT       27

#define AUDIO_EVENT_GPIO_PROBE_TIMEOUT       (1 << 0)

#endif
