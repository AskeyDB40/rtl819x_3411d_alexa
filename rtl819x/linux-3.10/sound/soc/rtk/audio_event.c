/*
 */
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/timer.h>
#include <linux/net.h>
#include <asm/byteorder.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/file.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/platform_data/rtl819x-gpio.h>
#include <linux/gpio.h>
#include "bspchip.h"
#include "audio_event.h"

//leo add for TE
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/syscalls.h>
#include <linux/fcntl.h>


#define EU_VE3 4
#define E_VE3 7

#define BIT(nr)                 (1UL << (nr))
#define RTL_GPIO_DIR_GPIOB5 (1<<13)
#define RTL_GPIO_DIR_GPIOD6 (1<<14)
#define USE_GPIO_INTERRUPT	 1

#if defined(USE_GPIO_INTERRUPT)	
#define GPIO_PROBE_TIMER_GAP 1000 //in ms
#else
#define GPIO_PROBE_TIMER_GAP 200 //in ms
#endif
#define RTL_R32(addr)		(*(volatile unsigned long *)(addr))
#define RTL_W32(addr, l)	((*(volatile unsigned long*)(addr)) = (l))
struct timer_list audio_event_gpio_probe_timer;
void audio_event_nl_send_msg(unsigned int pid, struct audio_event_nl_hdr *hdr);
void audio_event_send_nl_gpio_state(unsigned int pid, unsigned int state);
void audio_event_sink_init(void);
struct sock *audio_event_nl_sock = NULL;
EXPORT_SYMBOL_GPL(audio_event_nl_sock);
struct netlink_kernel_cfg *audio_event_nl_cfg = NULL;
struct audio_event_task audio_event_gpio_probe;
wait_queue_head_t audio_event_probe_waitq;
unsigned int audio_event_probe_flag=0;
static unsigned int    audio_event_probe_counter;
static unsigned int    audio_event_probe_state;
unsigned int audio_event_user_pid=0;

#define GPIO_IRQ_NUM		1	

/* GPIO Register Set */
#define GPIO_BASE                           (0xB8003500)	
#define PAB_IMR                             (GPIO_BASE + 0x14)
#define PABCD_ISR                           (GPIO_BASE + 0x10)
#define PABCD_CNR                           (GPIO_BASE + 0x00)
#define PABCD_PTYPE                         (GPIO_BASE + 0x04)
#define PABCD_DIR                           (GPIO_BASE + 0x08)
#define PABCD_DAT                           (GPIO_BASE + 0x0C)

#define RESET_PIN_IOBASE 	PABCD_CNR	//RTL_GPIO_PABCD_CNR
#define RESET_PIN_DIRBASE 	PABCD_DIR //RTL_GPIO_PABCD_DIR 
#define RESET_PIN_DATABASE 	PABCD_DAT //RTL_GPIO_PABCD_DATA
#define RESET_PIN_IMR		 (GPIO_BASE + 0x14)

#define RESET_BTN_PIN	14

#if defined(USE_GPIO_INTERRUPT)
#define PROBE_TIME	3
#else
#define PROBE_TIME	60
#endif

#define PROBE_NULL	0
#define PROBE_ACTIVE	1
#define PROBE_RESET	2
#define PROBE_RELOAD	3
#define RTL_R32(addr)	(*(volatile unsigned long *)(addr))
#define RTL_W32(addr, l)	((*(volatile unsigned long*)(addr)) = (l))
 
int led_on_duration=0;
int led_state=0;
int start_blinking=0;
int blinking_frequency=0; //ms
int idle_led_on_duration=0;
int idle_start_blinking=0;


int detect_count = 10;//leo add for TE
int gbfd=0;//leo add for TE
void Active_led_on(void)
{
//	gpio_set_value(BSP_GPIO_PIN_H0, 0);
	gpio_set_value(BSP_GPIO_PIN_D7, 0);
}

void Active_led_off(void)
{
//	gpio_set_value(BSP_GPIO_PIN_H0, 1);
	gpio_set_value(BSP_GPIO_PIN_D7, 1);
}


struct audio_event_gpio_device
{
	unsigned int name;
};
struct audio_event_gpio_device priv_audio_event_gpio_device;

void audio_event_stop_threads(void);

 static void audio_event_gpio_probe_task(unsigned long data)
{
	unsigned int pressed=1;
	int gpio_status=0;
#if defined(CONFIG_RTL_8196E)
	if(RTL96E_BOND == EU_VE3)
		gpio_status = (RTL_R32(RESET_PIN_DATABASE) & (1 << RESET_BTN_PIN));
	else if(RTL96E_BOND == E_VE3){
		gpio_status = RTLWIFINIC_GPIO_read(0);
		gpio_status = !gpio_status;
	}
#else	
	gpio_status =1;
#endif
	
	if (gpio_status)
	{
		pressed = 0;
	}
	else
	{
		//printk("Key pressed %d!\n", audio_event_probe_counter+1);
	}

	if (audio_event_probe_state == PROBE_NULL)
	{
		if (pressed)
		{
			audio_event_probe_state = PROBE_ACTIVE;
			audio_event_probe_counter++;
		}
		else {
			audio_event_probe_counter = 0;
			//leo start

			if (detect_count==0){
				mm_segment_t old_fs = get_fs();
				set_fs(KERNEL_DS);
				gbfd = sys_open("/var/led", O_RDONLY, 0);
				//printk("gbfd is %d\n",gbfd);
				if (gbfd>0)
					sys_close(gbfd);
				set_fs(old_fs);
				detect_count = 10;
			}else{
				detect_count--;
			}
			//if(audio_event_user_pid==0){
			if(audio_event_user_pid==0 && gbfd<0){
				//printk("shine gbfd is %d\n",gbfd);
				if (idle_start_blinking ==0)
					idle_start_blinking=1;
				if (idle_start_blinking==1) {
					idle_led_on_duration++;
					if (idle_led_on_duration & 1)	{
						Active_led_on();
					}else {
						Active_led_off();
					}
				}
			}

		}
	}
	else if (audio_event_probe_state == PROBE_ACTIVE)
	{
		if (pressed)
		{
			audio_event_probe_counter++;
			
			//push button has been pressed
			if ((audio_event_probe_counter >=2 ) && (audio_event_probe_counter <=PROBE_TIME))
			{
				
			}
			else if (audio_event_probe_counter >= PROBE_TIME)
			{
				
			}
		}
		else
		{
			//push button has been release
			if (audio_event_probe_counter < PROBE_TIME)
			{
				
			#if !defined(USE_GPIO_INTERRUPT)	
				audio_event_send_nl_gpio_state(audio_event_user_pid, GPIO_TIME_SHORT);
				audio_event_probe_state = PROBE_NULL;
				audio_event_probe_counter = 0;
			#else
			if (start_blinking==1){
				led_on_duration++;
/* Askey modified start, Cooper, 12/04/2017 */
/* Modified for LED status when wake word detected. Fixed issue QV0017-20. */
#if 0
				if (led_on_duration & 1)	{
					Active_led_on();
				}else {
					Active_led_off();
				}
#else
				Active_led_on();
#endif
/* Askey modified end, Cooper, 11/20/2017 */
			}
			#endif	
				
			}
			else
			{
				//printk("result >=%d\n", PROBE_TIME);
				audio_event_probe_counter = 0;
				audio_event_probe_state = PROBE_NULL;
			#if !defined(USE_GPIO_INTERRUPT)		
				audio_event_send_nl_gpio_state(audio_event_user_pid, GPIO_TIME_LONG);
			#endif	
			}
		}
	}
	if (idle_start_blinking ==1)
		mod_timer(&audio_event_gpio_probe_timer, jiffies + msecs_to_jiffies(250));
	else
		mod_timer(&audio_event_gpio_probe_timer, jiffies + HZ/2);
}
 
 
 static void timer_audio_event_gpio_probe(unsigned long data)
{
	audio_event_probe_flag |= AUDIO_EVENT_GPIO_PROBE_TIMEOUT;
	wake_up(&audio_event_probe_waitq);
}
void Init_audio_event_probe_timer(void)
{
 	init_timer(&audio_event_gpio_probe_timer);
    	audio_event_gpio_probe_timer.function = &audio_event_gpio_probe_task;
    	audio_event_gpio_probe_timer.data = (unsigned long)NULL;
    	audio_event_gpio_probe_timer.expires = jiffies + HZ/2;//msecs_to_jiffies(GPIO_PROBE_TIMER_GAP);
    	add_timer(&audio_event_gpio_probe_timer);
}


void audio_event_send_nl_gpio_state(unsigned int pid, unsigned int state)
{
    struct audio_event_nl_gpio_state nl_msg;

    memset(&nl_msg, 0, sizeof(nl_msg));

    nl_msg.hdr.msgtype = NL_GPIO_PROBE;
    nl_msg.hdr.msglen = sizeof (struct audio_event_nl_gpio_state);

    nl_msg.gpio_state = state;
    audio_event_nl_send_msg(pid, &nl_msg.hdr);
}



static void audio_event_nl_rcv_msg(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	struct audio_event_nl_hdr *hdr;
	//unsigned long flags;
	u32 rlen;
	int err;
	//int table_idx;
	
	union {
	    struct audio_event_nl_reg *preg;
	    struct audio_event_nl_gpio_state *gpioState;
	    struct audio_event_nl_led_blinking *ledState;
	    struct audio_event_nl_led_on_off *ledonoff;
	} nl_cmd;

	while (skb->len >= NLMSG_SPACE(0)) {
		err = 0;

		nlh = nlmsg_hdr(skb);
		if ((nlh->nlmsg_len < (sizeof(*nlh) + sizeof(*hdr))) ||
		    (skb->len < nlh->nlmsg_len)) {
			printk("%s: discarding partial skb(#1)\n", __func__);
			return;
		}

		rlen = NLMSG_ALIGN(nlh->nlmsg_len);
		if (rlen > skb->len)
			rlen = skb->len;

		if (nlh->nlmsg_type != NLMSG_TYPE_AUDIO_EVENT) 
		{
			err = -EBADMSG;
			printk("!!!! %s %d nlh->nlmsg_type=%x!!!!\n", __FUNCTION__, __LINE__, nlh->nlmsg_type);
			goto next_msg;
		}

		hdr = NLMSG_DATA(nlh);
		nl_cmd.preg = (struct audio_event_nl_reg *)hdr;


        switch (hdr->msgtype)
        {
	case NL_USER_REG:
            //printk("\n\nKnl Rcv NL_USER_REG: %d %d\n", nl_cmd.preg->pid, nl_cmd.preg->userid);
	audio_event_user_pid=nl_cmd.preg->pid;
	Active_led_off();
	audio_event_probe_state = PROBE_NULL;
	audio_event_probe_counter = 0;
	led_on_duration =0;
	start_blinking=0;
	led_state = 0;
	idle_start_blinking = 0;
	idle_led_on_duration = 0;
	audio_event_sink_init();
            break;
	case NL_LED_BLINKING:
		//printk("\n\nKnl Rcv NL_LED_BLINKING: %d %d\n", nl_cmd.ledState->led_blinking, nl_cmd.ledState->frequency);
/* Askey modified start, Cooper, 11/20/2017 */
/* Modified for LED status when wake word detected. */
#if 1	// re-open to fixed issue QV0017-20 on 12/04/2017
		start_blinking = nl_cmd.ledState->led_blinking;
		blinking_frequency = nl_cmd.ledState->frequency;
		led_on_duration =0;
		audio_event_probe_counter=0;
		led_state = 2;
#else
		Active_led_on();
		led_state =1;
		audio_event_probe_counter=0;
#endif
/* Askey modified end, Cooper, 11/20/2017 */
		if (audio_event_probe_state == PROBE_NULL)
			audio_event_probe_state = PROBE_ACTIVE;
	break;
	case NL_LED_ON_OFF:
		if (nl_cmd.ledonoff->led_on_off ==1) {
			Active_led_on();
			led_state =1;
		} else if (nl_cmd.ledonoff->led_on_off ==0) {
			Active_led_off();
			led_state = 0;
			if (start_blinking==1 || audio_event_probe_state != NULL){
				Active_led_off();
				audio_event_probe_state = PROBE_NULL;
				audio_event_probe_counter = 0;
				led_on_duration =0;
				start_blinking=0;
			}
		}
	break;

	case NL_USER_UN_REG:
		audio_event_stop_threads();
		//back to init
		audio_event_probe_state = PROBE_NULL;
		audio_event_probe_counter = 0;
		led_on_duration =0;
		start_blinking=0;
		Init_audio_event_probe_timer();
	break;
        default:
            err = 1;
            printk("%s %d netlink rcv an unknown command %d\n", __FUNCTION__, __LINE__, hdr->msgtype);
        }
        
next_msg:
		if ((err) || (nlh->nlmsg_flags & NLM_F_ACK))
			netlink_ack(skb, nlh, err);

		skb_pull(skb, rlen);
	}
}

void audio_event_nl_send_msg(u32 pid, struct audio_event_nl_hdr *hdr)
{
	struct sk_buff *skb;
	struct nlmsghdr	*nlh;
	const char *fn;
	char *datab;
	u32 len, skblen;
	int err;
	uint16_t msglen;

	if (!audio_event_nl_sock) 
	{
		err = -ENOENT;
		fn = "netlink socket";
		goto msg_fail;
	}

    msglen = hdr->msglen;
	len = NLMSG_SPACE(msglen);
	skblen = NLMSG_SPACE(len);

	skb = alloc_skb(skblen, GFP_KERNEL);
	if (!skb) 
	{
		err = -ENOBUFS;
		fn = "alloc_skb";
		goto msg_fail;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,16)
	nlh = nlmsg_put(skb, pid, 0, NETLINK_RTK_AUDIO_EVENT, len - sizeof(*nlh), 0);
#else
	nlh = __nlmsg_put(skb, pid, 0, NETLINK_RTK_AUDIO_EVENT, len - sizeof(*nlh));
#endif	
	if (!nlh) 
	{
		err = -ENOBUFS;
		fn = "nlmsg_put";
		goto msg_fail_skb;
	}
	datab = NLMSG_DATA(nlh);	
	memcpy(datab, hdr, msglen);

	err = nlmsg_unicast(audio_event_nl_sock, skb, pid);
	if (err < 0) {
		fn = "nlmsg_unicast";
		/* nlmsg_unicast already kfree_skb'd */
		goto msg_fail;
	}

	return;

msg_fail_skb:
	kfree_skb(skb);
msg_fail:
	printk(KERN_WARNING
		"%s: Dropped Message : pid %d , msgtype x%x, "
		"msglen %d: %s : err %d\n",
		__func__, pid, hdr->msgtype, hdr->msglen,
		fn, err);
	return;
}
EXPORT_SYMBOL_GPL(audio_event_nl_send_msg);

#if(LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))
static void audio_event_netlink_rcv(struct sock *sk, int len)
{
	unsigned int qlen = skb_queue_len(&sk->sk_receive_queue);

	do {
		struct sk_buff *skb;

		if (qlen > skb_queue_len(&sk->sk_receive_queue))
			qlen = skb_queue_len(&sk->sk_receive_queue);

		for (; qlen; qlen--) 
		{
	    	skb = skb_dequeue(&sk->sk_receive_queue);
		audio_event_nl_rcv_msg(skb);
	        	kfree_skb(skb);
		}
	}while (qlen);
}
#endif	/* #if(LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)) */
#if defined(USE_GPIO_INTERRUPT)
irqreturn_t audio_event_gpio_interrupt_isr(int irq, void *dev_instance)
{
printk("Got Audio event IRQ!\n");
		if(audio_event_probe_state == PROBE_NULL){
			audio_event_probe_state = PROBE_ACTIVE;	
			audio_event_probe_counter++;
			if(audio_event_user_pid>0)
			{
				printk("Send IRQ Event!\n");
				if (led_state ==0) {
					led_on_duration=0;
					audio_event_send_nl_gpio_state(audio_event_user_pid, GPIO_TIME_SHORT);
				}else {
						printk("SKIP 0 led state=%d\n", led_state);
				}
			}else {
				printk("SKIP 1\n");
				audio_event_probe_state = PROBE_NULL;	
				audio_event_probe_counter=0;
			}
		} else {
			if (start_blinking ==1 || led_state > 0) {
				printk("SKIP 2, but is progress\n");
				
				if (start_blinking ==1 && led_state==2) {
					printk("Send IRQ Event! Let users for judgment\n");
					audio_event_send_nl_gpio_state(audio_event_user_pid, GPIO_TIME_SHORT);
				}
				
			}else {
				audio_event_probe_state = PROBE_NULL;	
				audio_event_probe_counter=0;
			}
		}
	return IRQ_HANDLED;
}

#endif






void audio_event_nl_init(void)
{
	int irq = gpio_to_irq(BSP_GPIO_PIN_D6);
	int ret=0;
#if(LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18))
	audio_event_nl_sock = netlink_kernel_create(NETLINK_RTK_AUDIO_EVENT, audio_event_netlink_rcv);
#elif(LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))
	audio_event_nl_sock = netlink_kernel_create(NETLINK_RTK_AUDIO_EVENT, 0, audio_event_netlink_rcv, 
			NULL, THIS_MODULE);
#elif(LINUX_VERSION_CODE < KERNEL_VERSION(3,6,0))
	audio_event_nl_sock = netlink_kernel_create(&init_net, NETLINK_RTK_AUDIO_EVENT,
				0, audio_event_nl_rcv_msg, NULL,
				THIS_MODULE);
#elif(LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0))
	audio_event_nl_cfg = (struct netlink_kernel_cfg *)kmalloc(sizeof(struct netlink_kernel_cfg), GFP_KERNEL);
	audio_event_nl_cfg->groups = 0;
	audio_event_nl_cfg->input = audio_event_nl_rcv_msg;
	audio_event_nl_cfg->cb_mutex = NULL;
	audio_event_nl_cfg->bind = NULL;
	audio_event_nl_sock = netlink_kernel_create(&init_net, NETLINK_RTK_AUDIO_EVENT,
				THIS_MODULE, audio_event_nl_cfg);
#else
	audio_event_nl_cfg = (struct netlink_kernel_cfg *)kmalloc(sizeof(struct netlink_kernel_cfg), GFP_KERNEL);
	audio_event_nl_cfg->groups = 0;
	audio_event_nl_cfg->flags = NL_CFG_F_NONROOT_RECV | NL_CFG_F_NONROOT_SEND;
	audio_event_nl_cfg->input = audio_event_nl_rcv_msg;
	audio_event_nl_cfg->cb_mutex = NULL;
	audio_event_nl_cfg->bind = NULL;
	audio_event_nl_sock = netlink_kernel_create(&init_net, NETLINK_RTK_AUDIO_EVENT,
				 audio_event_nl_cfg);
#endif

	if (!audio_event_nl_sock) 
	{
		printk("%s: netlink create failed\n", __func__);
	}
#if 0 //defined(CONFIG_RTL_8196E)	
	if(RTL96E_BOND == EU_VE3){
		//set shared pin GPIO PIN, GPIOB5 in GPIO mode
		RTL_W32(0xB8000044, (RTL_R32(0xB8000044) | 0x600));
		//set GPIO PIN, GPIOB[5]
		RTL_W32(PABCD_CNR, (RTL_R32(PABCD_CNR) & (~(RTL_GPIO_DIR_GPIOB5))));
		//set direction, GPIOB[5] INPUT
		RTL_W32(PABCD_DIR, (RTL_R32(PABCD_DIR) & (~(RTL_GPIO_DIR_GPIOB5))));
	}else if(RTL96E_BOND ==E_VE3){
		RTLWIFINIC_GPIO_config(0, 0x01); //read direction
	}
#endif	
//for 5680
	RTL_W32(0xB8000864, (RTL_R32(0xB8000864) & (~(RTL_GPIO_DIR_GPIOD6))));
	
	ret = gpio_request_one(BSP_GPIO_PIN_D6, GPIOF_IN | GPIOF_EXPORT_DIR_FIXED, "audio_gpio_irq");

	if (ret <0 ) {
		printk("gpio_request_one fail ret=%d\n", ret);
	}
	
	
#if defined(USE_GPIO_INTERRUPT)
	ret = request_irq(irq, audio_event_gpio_interrupt_isr, IRQF_SHARED|IRQF_TRIGGER_RISING, "audio_ev_int", (void *)&priv_audio_event_gpio_device);
	if (ret != 0) {
		printk("gpio request_irq(%d) error! ret=%d\n", irq, ret);	
	}
	
#endif	
//	ret=gpio_request_one(BSP_GPIO_PIN_H0, GPIOF_OUT_INIT_HIGH | GPIOF_EXPORT_DIR_FIXED, "Audio Event Led");
	ret=gpio_request_one(BSP_GPIO_PIN_D7, GPIOF_OUT_INIT_HIGH | GPIOF_EXPORT_DIR_FIXED, "Audio Event Led");
	if (ret <0 ) {
//		printk("BSP_GPIO_PIN_H0 gpio_request_one fail ret=%d\n", ret);
		printk("BSP_GPIO_PIN_D7 gpio_request_one fail ret=%d\n", ret);
	}
	Active_led_off();
	audio_event_probe_state = PROBE_NULL;
	audio_event_probe_counter = 0;
	led_on_duration =0;
	start_blinking=0;
	audio_event_user_pid = 0;
	idle_led_on_duration = 0;
	idle_start_blinking = 0;
	Init_audio_event_probe_timer();
	led_state =0;
	return;
}

void audio_event_nl_exit(void)
{
    if (audio_event_nl_sock)
    {
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,24)
        sock_release (audio_event_nl_sock->sk_socket);
#else
        netlink_kernel_release(audio_event_nl_sock);
#endif
        audio_event_nl_sock = NULL;
    }

	if(audio_event_nl_cfg) {
		kfree(audio_event_nl_cfg);
		audio_event_nl_cfg = NULL;
	}
}

int audio_event_thread(void *param)
{
	struct audio_event_task *ut = (struct audio_event_task *) param;

	if (!ut)
		return -EINVAL;
	
#if(LINUX_VERSION_CODE == KERNEL_VERSION(2,6,30))
	lock_kernel();
	daemonize(ut->name);
#else
	spin_lock(&ut->lock);
#endif
	allow_signal(SIGKILL);
	ut->thread = current;
	set_user_nice(current, -19);
#if(LINUX_VERSION_CODE == KERNEL_VERSION(2,6,30))
	unlock_kernel();
#else
	spin_unlock(&ut->lock);
#endif

	/* srv.rb must wait for rx_thread starting */
	complete(&ut->thread_done);

	/* start of while loop */
	ut->loop_ops(ut);

	/* end of loop */
	ut->thread = NULL;

	complete_and_exit(&ut->thread_done, 0);
}

void audio_event_task_init(struct audio_event_task *ut, char *name,void (*loop_ops)(struct audio_event_task *))
{
	ut->thread = NULL;
	init_completion(&ut->thread_done);
	strncpy (ut->name, name, 16);
	ut->loop_ops = loop_ops;
}
EXPORT_SYMBOL_GPL(audio_event_task_init);


static void stop_audio_event_timer_thread(void) {
	if (audio_event_gpio_probe.thread != NULL) {
		send_sig(SIGKILL, audio_event_gpio_probe.thread, 1);
		wait_for_completion(&audio_event_gpio_probe.thread_done);
	}
}
int audio_event_start_threads(void)
{
	struct task_struct *th;
    	int err = 0;
	
	th = kthread_run(audio_event_thread, (void *)&audio_event_gpio_probe, "gpio_probe_ae");
	if (IS_ERR(th)) {
		printk(KERN_WARNING"Unable to start control thread\n");
        		err = PTR_ERR(th);
        		goto thread_err;
	}

	/* confirm threads are starting */
	wait_for_completion(&audio_event_gpio_probe.thread_done);
	
	return 0;

    thread_err:
        return err;
	
}
 
void audio_event_timer_loop(struct audio_event_task *audio_event_gpio_probe)
{
	
	while (1) {
		if (signal_pending(current)) {
			break;
		}
	
	        if (audio_event_probe_flag & AUDIO_EVENT_GPIO_PROBE_TIMEOUT)
	        {
	            //audio_event_gpio_probe_task(0);
	            audio_event_probe_flag&= ~AUDIO_EVENT_GPIO_PROBE_TIMEOUT;
	        }
		wait_event_interruptible(audio_event_probe_waitq,audio_event_probe_flag);
	}
	//printk("audio_event_timer_loop stop");
}


void audio_event_sink_init(void)
{
	audio_event_task_init(&audio_event_gpio_probe, "audio_ev_probe", audio_event_timer_loop);
	
	init_waitqueue_head(&audio_event_probe_waitq);
	audio_event_start_threads();
}

void audio_event_stop_threads(void)
{
	printk("audio_event_stop_threads go\n");
	
	if (timer_pending(&audio_event_gpio_probe_timer))
		del_timer(&audio_event_gpio_probe_timer);

	audio_event_user_pid = 0;
	audio_event_probe_state = PROBE_NULL;
	audio_event_probe_counter=0;
		
    stop_audio_event_timer_thread();
	
	printk("audio_event_stop_threads end\n");
}
