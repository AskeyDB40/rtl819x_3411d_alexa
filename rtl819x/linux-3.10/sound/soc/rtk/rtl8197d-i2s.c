/*
 * rtl8197d-i2s.c  --  ALSA Soc Audio Layer
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  Revision history
 *    24th Feb 2012   Initial version.
 *    4th May 2012    add capture support
 *    6th Nov 2013    add mono channel support
 */
// #define DEBUG


#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/jiffies.h>
#include <linux/io.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/initval.h>
#include <sound/soc.h>
#include <sound/info.h>
#include <linux/kconfig.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/ioctl.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>



#if 0
  #define DEBUG(format, args...) printk("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
  #define DEBUG(args...)
#endif


  #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30))
#include "bspchip.h"
#define IIS_IRQ BSP_I2S_IRQ
  #else
#define IIS_IRQ	26
  #endif


#include "rtl819x-pcm.h"
#include "rtl8197d-i2s.h"

#define I2S_D2A_OUT	1
#define I2S_A2D_IN	2

#define IIS_PAGE_NUM	4
#define IIS_PAGE_SIZE	(80*3)	// 80 * 32bit, 160sample, 20ms
extern int iis_44100_enabled;
static short iis_tx_buf[IIS_PAGE_NUM*IIS_PAGE_SIZE*2*4+256]__attribute__ ((aligned (32)));


/*this iis_counter is used for counting how many pcm streams are opened*/
int iis_counter=0;
/* size :byte unit */
#if 1 //For debug 

int16_t sinus(int32_t x)
{
	int16_t i;
	int32_t x2;												// Q15
	int32_t q;
	int32_t res=0;
	int16_t coef[5] = { (int16_t)0x3240, (int16_t)0x0054, (int16_t)0xaacc,
					   (int16_t)0x08B7, (int16_t)0x1cce };	// Q12
	if (x > 0x00008000L)
		x2 = x - 0x00008000L;
	else
		x2 = x;

	if (x2 > 0x00004000L)
		x2 = 0x00008000L - x2;
	q = x2;


	for (i=0; i<5; i++)
	{
		res += coef[i]*x2;											// Q27
		x2 *= q;													// Q30
		x2 >>= 15;													// Q15
	}

	res >>= 12;	 /* back to 0x0000-0xFFFF */						// Q15
	if (x > 0x00008000L)
		res = -res;
	if (res > 0 && res > 32767)
		res = 32767;
	else
		if (res < 0 && res < -32768)
			res = -32768;

	return (int16_t)res;
}

int32_t iis_allchannel=2;
int32_t tone_phase=0;

int32_t tone_phase_ad;

int32_t play_channel=0;
int32_t play_channel_now=0;

static int sample_count;
void tone_gens(int32_t sample_num, int16_t *buffPtr)
{
	int32_t i;

	tone_phase_ad = (1014 * 16777) >> 11;		// 65535/8000 in Q11

	if (play_channel>=iis_allchannel) {
		if (iis_allchannel==1)
			play_channel_now=0;
		else
			play_channel_now=play_channel%iis_allchannel;
	} else
		play_channel_now = play_channel;

	for(i=0;i<sample_num;i++)
	{

		if (sample_count==play_channel_now) {
			*buffPtr=sinus(tone_phase)>>2;
			tone_phase += tone_phase_ad;
			if (tone_phase > 65535)
				tone_phase -= 65535;
		} else {
			*buffPtr=sinus(tone_phase)>>2;
		}
		sample_count++;
		if (sample_count==iis_allchannel)
			sample_count=0;
		buffPtr++;
	}
}

#endif
/*
 * Check whether CPU is the master or slave
 */
static inline int rtl8197d_snd_is_clkmaster(void)
{
	return 1; // 8197d alway master
}

/*
 * Set RTL8197D I2S DAI format
 */
static int rtl8197d_i2s_set_fmt(struct snd_soc_dai *cpu_dai,
		unsigned int fmt)
{
	return 0;
}

static int rtl8197d_i2s_startup(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	DEBUG("\n");
	DEBUG("%s, %d\n", __FUNCTION__, __LINE__);
	return 0;
}

static int rtl8197d_i2s_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	//struct snd_soc_pcm_runtime *rtd = substream->private_data;

	DEBUG("\n");
#if 0
    DEBUG("rate %d format %x\n", params_rate(params),params_format(params));
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_BE:
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		break;
	case SNDRV_PCM_FORMAT_S24_BE:
		break;
	}
#endif	
	return 0;
}

static int rtl8197d_i2s_trigger(struct snd_pcm_substream *substream, int cmd,
			       struct snd_soc_dai *dai)
{
	int ret = 0;
	DEBUG("\n");
	DEBUG("%s, %d\n", __FUNCTION__, __LINE__);
	return ret;
}

/*
 * Set S3C24xx Clock source
 */
static int rtl8197d_i2s_set_sysclk(struct snd_soc_dai *cpu_dai,
	int clk_id, unsigned int freq, int dir)
{
	DEBUG("\n");
	DEBUG("%s, %d\n", __FUNCTION__, __LINE__);

	return 0;
}

/*
 * Set S3C24xx Clock dividers
 */
static int rtl8197d_i2s_set_clkdiv(struct snd_soc_dai *cpu_dai,
	int div_id, int div)
{
	DEBUG("\n");
	DEBUG("%s, %d\n", __FUNCTION__, __LINE__);

	return 0;
}

static void rtl8197d_i2s_shutdown(struct snd_pcm_substream *substream,
			       struct snd_soc_dai *dai)
{
    DEBUG ("rtl8197d_i2s_shutdown.\n");
}

static int rtl8197d_i2s_probe(struct platform_device *pdev,
			     struct snd_soc_dai *dai)
{
	DEBUG("\n");
    DEBUG("%s, %d\n", __FUNCTION__, __LINE__);
	return 0;
}

#define rtl8197d_i2s_suspend NULL
#define rtl8197d_i2s_resume NULL



static struct snd_soc_dai_ops rtl8197d_i2s_dai_ops = {
	.trigger	= rtl8197d_i2s_trigger,
	.hw_params	= rtl8197d_i2s_hw_params,
	.set_fmt	= rtl8197d_i2s_set_fmt,
	.startup	= rtl8197d_i2s_startup,
	.shutdown	= rtl8197d_i2s_shutdown,
	.set_clkdiv	= rtl8197d_i2s_set_clkdiv,
	.set_sysclk	= rtl8197d_i2s_set_sysclk,
};
#if defined(CONFIG_RTL_8197F)
struct snd_soc_dai_driver rtl8197d_i2s_dai = {
	.name = "rtl819x-iis",
	.id = 0,
	.probe = rtl8197d_i2s_probe,
	.suspend = rtl8197d_i2s_suspend,
	.resume = rtl8197d_i2s_resume,
	.playback = {
		.channels_min = 1,
		.channels_max = 2,
		//.rates = SNDRV_PCM_RATE_8000_192000,
		.rates = SNDRV_PCM_RATE_48000,
#if defined(CONFIG_SND_RTL819XD_SOC_ALC5659) || defined(CONFIG_SND_RTL819XD_SOC_ALC5680)
		//.formats = SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_S16_LE|SNDRV_PCM_FMTBIT_S24_LE|SNDRV_PCM_FMTBIT_S24_BE,
		.formats = SNDRV_PCM_FMTBIT_S16_LE,
#else		
		.formats = SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_S16_LE|SNDRV_PCM_FMTBIT_S24_LE|SNDRV_PCM_FMTBIT_S32_LE|SNDRV_PCM_FMTBIT_S24_BE|SNDRV_PCM_FMTBIT_S32_BE,
#endif		
	},
	.capture = {
		.channels_min = 1,
		.channels_max = 2,
		//.rates = SNDRV_PCM_RATE_8000_192000,
		.rates = SNDRV_PCM_RATE_48000,
		
#if defined(CONFIG_SND_RTL819XD_SOC_ALC5659) || defined(CONFIG_SND_RTL819XD_SOC_ALC5680)
		//.formats = SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_S16_LE|SNDRV_PCM_FMTBIT_S24_LE|SNDRV_PCM_FMTBIT_S24_BE,
		.formats = SNDRV_PCM_FMTBIT_S16_LE,
#else		
		.formats = SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_S16_LE|SNDRV_PCM_FMTBIT_S24_LE|SNDRV_PCM_FMTBIT_S32_LE|SNDRV_PCM_FMTBIT_S24_BE|SNDRV_PCM_FMTBIT_S32_BE,
#endif		
	},
	.ops = &rtl8197d_i2s_dai_ops,
};
#else
struct snd_soc_dai_driver rtl8197d_i2s_dai = {
	.name = "rtl819x-iis",
	.id = 0,
	.probe = rtl8197d_i2s_probe,
	.suspend = rtl8197d_i2s_suspend,
	.resume = rtl8197d_i2s_resume,
	.playback = {
		.channels_min = 1,
		.channels_max = 2,
#if defined(CONFIG_RTL_8881A)	
		 .rates = (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000),	
#else
		.rates = SNDRV_PCM_RATE_48000,
#endif
		.formats = SNDRV_PCM_FMTBIT_S16_BE,
	},
	.capture = {
		.channels_min = 1,
		.channels_max = 2,
#if defined(CONFIG_RTL_8881A)	
		  .rates = (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000),	
#else
		.rates = SNDRV_PCM_RATE_48000,
#endif
		.formats = SNDRV_PCM_FMTBIT_S16_BE,
	},
	.ops = &rtl8197d_i2s_dai_ops,
};
#endif

EXPORT_SYMBOL_GPL(rtl8197d_i2s_dai);


static struct snd_info_entry *snd_info_rtl8197d_i2s_entry;
extern unsigned int serial_in_i2c(unsigned int addr, int offset);

static void snd_info_rtl8197d_i2s_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	int temp;
        snd_iprintf(buffer,"snd_info_rtl8197d_i2s_read \n");
//        snd_iprintf(buffer, "i2s sampling rate=%d\n", SNDRV_PCM_RATE_NUM);
        snd_iprintf(buffer, "i2s:00=%x, 10=%x, 40=%x\n", rtlRegRead(0xb8000000), rtlRegRead(0xb8000010), rtlRegRead(0xb8000040));
        snd_iprintf(buffer, "    44=%x, 58=%x, %x\n", rtlRegRead(0xb8000044), rtlRegRead(0xb8000058), rtlRegRead(0xb8000040));
        snd_iprintf(buffer, "    3000=%x, 3004=%x, 3014=%x\n", rtlRegRead(0xb8003000), rtlRegRead(0xb8003004), rtlRegRead(0xb8003014));

        snd_iprintf(buffer, "    IISCR=%x, TX_PAGE_PTR=%x, RX_PAGE_PTR=%x\n", rtlRegRead(IISCR), rtlRegRead(TX_PAGE_PTR), rtlRegRead(RX_PAGE_PTR));
        snd_iprintf(buffer, "    IIS_SETTING=%x, IIS_TX_IMR=%x, IIS_TX_ISR=%x\n", rtlRegRead(IIS_SETTING), rtlRegRead(IIS_TX_IMR), rtlRegRead(IIS_TX_ISR));
        snd_iprintf(buffer, "    IIS_TX_P0OWN=%x, IIS_TX_P1OWN=%x, IIS_TX_P2OWN=%x, IIS_TX_P3OWN=%x\n", rtlRegRead(IIS_TX_P0OWN), rtlRegRead(IIS_TX_P1OWN), rtlRegRead(IIS_TX_P2OWN), rtlRegRead(IIS_TX_P3OWN));
        snd_iprintf(buffer, "    IIS_SETTING=%x, IIS_RX_IMR=%x, IIS_RX_ISR=%x\n", rtlRegRead(IIS_SETTING), rtlRegRead(IIS_RX_IMR), rtlRegRead(IIS_RX_ISR));
        snd_iprintf(buffer, "    IIS_RX_P0OWN=%x, IIS_RX_P1OWN=%x, IIS_RX_P2OWN=%x, IIS_RX_P3OWN=%x\n", rtlRegRead(IIS_RX_P0OWN), rtlRegRead(IIS_RX_P1OWN), rtlRegRead(IIS_RX_P2OWN), rtlRegRead(IIS_RX_P3OWN));
#ifdef CONFIG_SND_RTL819XD_SOC_ALC5642
	temp = serial_in_i2c( 0x38, 0xfe);
	snd_iprintf(buffer, "    reg_fe=%x,\n ", temp);
#endif

#ifdef CONFIG_SND_RTL819XD_SOC_ALC5628
	temp = serial_in_i2c( 0x30, 0x0);
	snd_iprintf(buffer, "    reg_0=%x,\n ", temp);
#endif

#ifdef CONFIG_SND_RTL819XD_SOC_ALC5633Q
	temp = serial_in_i2c( 0x38, 0x0);
	snd_iprintf(buffer, "    reg_0=%x,\n ", temp);
#endif
#ifdef CONFIG_SND_RTL819XD_SOC_ALC5670
	temp = serial_in_i2c( 0x38, 0x0);
	snd_iprintf(buffer, "    reg_0=%x,\n ", temp);
#endif		
#ifdef CONFIG_SND_RTL819XD_SOC_ALC5651
	temp = serial_in_i2c( 0x34, 0x0);
	snd_iprintf(buffer, "    reg_0=%x,\n ", temp);
#endif	

}

static struct snd_info_entry *snd_info_rtl8197d_i2s_start_entry;

static void snd_info_rtl8197d_i2s_start_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
        snd_iprintf(buffer,"snd_info_rtl8197d_i2s_start_read \n");
	rtlRegWrite(IISCR,0x80000000 | (0x2) | IIS_ENABLE | (0<<15)|iis_44100_enabled );	// 0->1 enable IIS
}

static int snd_info_rtl8197d_i2s_init(void)
{
        return 0;
}



static const struct snd_soc_component_driver rtl819x_i2s_component = {
	.name		= "rtl819x-iis",
};
#ifdef CONFIG_SND_RTL819XD_SOC_ALC5659
extern unsigned int rt5659_read(void *context, unsigned int reg,  unsigned int *value);
#endif
#include <linux/delay.h>


extern struct proc_dir_entry proc_root;
static int iis_read_proc(struct seq_file *s, void *v)
{
	printk("IIS read\n");
	printk("IISCR=0x%08X\n", rtlRegRead(IISCR));
	printk("TX_PAGE_PTR=0x%08X\n", rtlRegRead(TX_PAGE_PTR));
	printk("RX_PAGE_PTR=0x%08X\n", rtlRegRead(RX_PAGE_PTR));
	printk("IIS_SETTING=0x%08X\n", rtlRegRead(IIS_SETTING));
	printk("IIS_TX_IMR=0x%08X\n", rtlRegRead(IIS_TX_IMR));
	printk("IIS_TX_ISR=0x%08X\n", rtlRegRead(IIS_TX_ISR));
	printk("IIS_RX_IMR=0x%08X\n", rtlRegRead(IIS_RX_IMR));
	printk("IIS_RX_ISR=0x%08X\n", rtlRegRead(IIS_RX_ISR));
	printk("IIS_TX_P0OWN=0x%08X\n", rtlRegRead(IIS_TX_P0OWN));
	printk("IIS_TX_P1OWN=0x%08X\n", rtlRegRead(IIS_TX_P1OWN));
	printk("IIS_TX_P2OWN=0x%08X\n", rtlRegRead(IIS_TX_P2OWN));
	printk("IIS_TX_P3OWN=0x%08X\n", rtlRegRead(IIS_TX_P3OWN));
	printk("IIS_RX_P0OWN=0x%08X\n", rtlRegRead(IIS_RX_P0OWN));
	printk("IIS_RX_P1OWN=0x%08X\n", rtlRegRead(IIS_RX_P1OWN));
	printk("IIS_RX_P2OWN=0x%08X\n", rtlRegRead(IIS_RX_P2OWN));
	printk("IIS_RX_P3OWN=0x%08X\n", rtlRegRead(IIS_RX_P3OWN));
	printk("0xB800083C=0x%08X\n", rtlRegRead(0xB800083C));
	printk("0xB8003508=0x%08X\n", rtlRegRead(0xB8003508));
	printk("0xB800350C=0x%08X\n", rtlRegRead(0xB800350C));
	printk("0xB8003518=0x%08X\n", rtlRegRead(0xB8003518));
	return 0;
}
static int iis_write_proc(struct file *file, const char *buffer, unsigned long count, void *data)
{
	char flag[20];
	unsigned int addr;
	unsigned int reg_value;
	if (count < 2)
		return -EFAULT;

	printk("file: %08x, buffer: %s, count: %lu, data: %08x\n",
		(unsigned int)file, buffer, count, (unsigned int)data);
	memset(flag, 0, sizeof(flag));
	if (buffer && !copy_from_user(&flag, buffer, count)) {
		sscanf(flag, "%u", &addr);
		printk("addr=%u, %X\n", addr, addr);
#ifdef CONFIG_SND_RTL819XD_SOC_ALC5659		
		rt5659_read(NULL, addr, &reg_value);
		printk("5659 reg_value=%X\n",reg_value);
#endif
		return count;
	}
	else
		return -EFAULT;
}

int iis_single_open(struct inode *inode, struct file *file)
{
        return(single_open(file, iis_read_proc, NULL));
}

static ssize_t iis_single_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	return iis_write_proc(file, userbuf,count, off);
}



struct file_operations iis_proc_fops = {
        .open           = iis_single_open,
	 .write		= iis_single_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};

extern void audio_event_nl_init(void);
static int rtl819x_iis_dev_probe(struct platform_device *pdev)
{
	int ret = 0;
	int i, j;
unsigned int reg_value;
    

#if defined(CONFIG_RTL_8197F)
	/* reset */
    /* Disable the I2S first, and reset to default */
	rtlRegMask(0xB8000010, 1 <<  0, 0 <<  0); //BIT_CTRL_CTLX_I2S_EN(0)
	rtlRegMask(0xB8000010, 1 << 31, 1 << 31); //BIT_CTRL_CTLX_I2S_SW_RSTN(1)

	/* enable hw */
	rtlRegMask(0xB8000010, 1 << 22, 1 << 22); //active I2S
	rtlRegMask(0xB8000024, 3 << 20, 3 << 20); //clock

	rtlRegMask(0xB8000010, 3 << 12, 3 << 12); //active BIT_ACTIVE_LX1ARB, BIT_ACTIVE_LX1
	//rtlRegMask(0xB8000010, 3 << 19, 3 << 19); //active BIT_ACTIVE_LX2ARB, BIT_ACTIVE_LX2

	/* init pin mux */
	
	rtlRegMask(0xB800083C, 0xF<<12 | 0xF<<8|0xF<<4 , 0x2<<12| 0x6<<8|0x7<<4 ); 

	//set GPIO B[2], P0_RXD3  to I2S_MCLK  //0x804h, [19:16] 0101
	//set GPIO B[3], P0_RXD2  to I2S_SCLK  //0x804h, [23:20] 0101
	//set GPIO B[4], P0_RXD1  to I2S_WS    //0x804h, [27:24] 0101
	//set GPIO B[5], P0_RXD0  to I2S_SD1_O //0x804h, [31:28] 0100
	rtlRegMask(0xB8000840, 0xF<<12 | 0xF<<8 | 0xF<<4 | 0xF<<0|0xF<<16, 0x3<<12 | 0x5<<8 | 0x3<<4 | 3<<0|0x2<<16); 
	//printk("0xB800083C:\t%08X 0xB8000840:\t%08X\n", rtlRegRead(0xB800083C), rtlRegRead(0xB8000840));
    
#elif defined(CONFIG_RTL_8198C)
	rtlRegMask(0xb8000010, 0x400000, 0x400000);//enable iis controller clock
    	rtlRegMask(0xb8000010, 0x2000000, 0x000000);//enable 24p576mHz clock


    // rtlRegMask(0xb8000108, 0x3FFFF, 0x0001F924);
    // LED_S0 (2:0)     [100] -> IIS
    // LED_S1 (5:3)     [100] -> IIS
    // LED_S2 (8:6)     [100] -> IIS
    // LED_S3 (11:9)    [100] -> IIS
    // LED_P0 (14:12)   [111] -> ISI
    
    // GPIO_F2(18,GM0_RXD0) & GPIO_F1(21,GM0_RXD1) for audio driver 
    rtlRegMask(0xB8000108, (7<<18)|(7<<21), (3<<18)|(3<<21)); 
    
    // LED_S1,LED_S2,LED_S3, for IIS
    rtlRegMask(0xB8000108, (7<<3)|(7<<6)|(7<<9), (4<<3)|(4<<6)|(4<<9)); 
    
    // LED_S0,P5_GTXC for IIS
    rtlRegMask(0xB8000108, (7<<0), (4<<0));
    
    // GM5_GTXC for IIS
    rtlRegMask(0xB800010C, (0xF<<3), (5<<3));
		
	rtlRegMask(0xb800002c, (1<<0|1<<11),  (1<<0|1<<11));
#else
	rtlRegMask(0xb8003014, 0x00000F00, 0x00000200);//route iis interrupt
	rtlRegMask(0xb8000010, 0x03DCB000, 0x01DCB000);//enable iis controller clock
	rtlRegMask(0xb8000058, 0x00000001, 0x00000001);//enable 24p576mHz clock
	/* Configure the I2S pins in correct mode */
	// set the jtag as iis-audio
	#if defined(CONFIG_RTL_8881A)
		// set the led-sig0 as iis-sd1_out
		rtlRegMask(0xb8000044, 0x0000FFF9, 0x000000D9);
		//enable 44.1K PLL setting
		rtlRegWrite(0xB8000058, (rtlRegRead(0xB8000058) | 0x800));
	#else
		rtlRegMask(0xb8000040, 0x00000007, 0x00000003);//change pin mux to iis-voice pin
		// set the led-sig0 as iis-sd1_out
		rtlRegMask(0xb8000044, 0x00000003, 0x00000001);//change pin mux to iis-voice pin
	#endif
#endif
   #if 0
#if defined(CONFIG_RTL_8881A)
		printk("PABCD_CNR:\t%08X\nPABCD_DIR:\t%08X\nPABCD_DAT:\t%08X\n"
				"PIN_MUX_SEL:\t%08X\nPIN_MUX_SEL_2:\t%08X\nPIN_MUX_SEL_3:\t%08X\n",
					rtlRegRead(0xB8003500), rtlRegRead(0xB8003508),
					rtlRegRead(0xB800350C), rtlRegRead(0xB8000040),
					rtlRegRead(0xB8000044),rtlRegRead(0xB800004C));
#else
		printk("PABCD_CNR:\t%08X\nPABCD_DIR:\t%08X\nPABCD_DAT:\t%08X\n"
				"PIN_MUX_SEL:\t%08X\nPIN_MUX_SEL_2:\t%08X\n",
					rtlRegRead(0xB8003500), rtlRegRead(0xB8003508),
					rtlRegRead(0xB800350C), rtlRegRead(0xB8000040),
					rtlRegRead(0xB8000044));
#endif
#endif	
#if 0
#if defined(CONFIG_RTL_8881A)
	rtlRegWrite(0xB800004C, ((rtlRegRead(0xB800004C) & ~0xFFFFFF) | 0x33333));
	printk("PABCD_CNR:\t%08X\nPABCD_DIR:\t%08X\nPABCD_DAT:\t%08X\n"
					"PIN_MUX_SEL:\t%08X\nPIN_MUX_SEL_2:\t%08X\nPIN_MUX_SEL_3:\t%08X\n",
						rtlRegRead(0xB8003500), rtlRegRead(0xB8003508),
						rtlRegRead(0xB800350C), rtlRegRead(0xB8000040),
						rtlRegRead(0xB8000044),rtlRegRead(0xB800004C));
#else
	rtlRegWrite(0xB8000044, ((rtlRegRead(0xB8000044) & ~0x3FFF9) | 0x100D9));
	printk("PABCD_CNR:\t%08X\nPABCD_DIR:\t%08X\nPABCD_DAT:\t%08X\n"
					"PIN_MUX_SEL:\t%08X\nPIN_MUX_SEL_2:\t%08X\n",
						rtlRegRead(0xB8003500), rtlRegRead(0xB8003508),
						rtlRegRead(0xB800350C), rtlRegRead(0xB8000040),
						rtlRegRead(0xB8000044));
#endif
#endif	
	
	
	

	rtlRegWrite(IISCR, 0x80000000);	// stop IIS
for (j=0;j<5000;j++);
	rtlRegWrite(IISCR, 0x0000);	// stop IIS
for (j=0;j<5000;j++);
	rtlRegWrite(IISCR, 0x80000000);
for (j=0;j<5000;j++);
	/* clear tx rx isr status */

	rtlRegWrite(IIS_TX_ISR, IIS_TX_P0OK | IIS_TX_P1OK | IIS_TX_P2OK | IIS_TX_P3OK | IIS_TX_PAGEUNAVA | IIS_TX_FIFO_EMPTY);
	rtlRegWrite(IIS_RX_ISR, IIS_RX_P0OK | IIS_RX_P1OK | IIS_RX_P2OK | IIS_RX_P3OK | IIS_RX_PAGEUNAVA | IIS_RX_FIFO_FULL);

	
	// allocate buffer address
	rtlRegWrite(TX_PAGE_PTR,(unsigned int)iis_tx_buf & 0xfffffff);
	rtlRegWrite(IIS_TX_P0OWN,BIT(31));
	rtlRegWrite(IIS_TX_P1OWN,BIT(31));
	rtlRegWrite(IIS_TX_P2OWN,BIT(31));
	rtlRegWrite(IIS_TX_P3OWN,BIT(31));
	
	rtlRegWrite(IIS_RX_P0OWN,BIT(31));
	rtlRegWrite(IIS_RX_P1OWN,BIT(31));
	rtlRegWrite(IIS_RX_P2OWN,BIT(31));
	rtlRegWrite(IIS_RX_P3OWN,BIT(31));

	
	//printf("enable IIS  interrupt\n");
	rtlRegWrite(IIS_TX_IMR, 0x0f);
	rtlRegWrite(IIS_RX_IMR, 0x0f);
	rtlRegWrite(IIS_SETTING, (PAGE_SIZE - 1) | ((IIS_PAGE_NUM-1)<<12) | (1<<14));	//set page size
	/*register platform device*/
	//rtlRegMask(0xB801F000, 0x3 << 3, 0x2 << 3);
	//rtlRegMask(0xB801F000, 1 << 12, 0 << 12);
	//rtlRegMask(0xB801F000, 0x3 << 29, 0x0 << 29);
	//rtlRegMask(0xB801F000, 0x3 << 1, 0x1 <<1);
	//rtlRegMask(0xB801F000, 0x1 << 0, 0x1 <<0);	// 0->1 enable IIS
	ret = snd_soc_register_component(&pdev->dev, &rtl819x_i2s_component,&rtl8197d_i2s_dai, 1);
	if (ret) {
		pr_err("failed to register the dai\n");
		return ret;
	}

	ret = rtl819x_soc_platform_init(&pdev->dev);
	if (ret) {
		pr_err("failed to register the dma: %d\n", ret);
		goto err;
	}
	proc_create_data("iis", 0, &proc_root, &iis_proc_fops, NULL);
	audio_event_nl_init();
	return 0;
err:
	snd_soc_unregister_component(&pdev->dev);
	return ret;
}

static int rtl819x_iis_dev_remove(struct platform_device *pdev)
{
	rtl819x_soc_platform_exit(&pdev->dev);
	snd_soc_unregister_component(&pdev->dev);
	snd_info_free_entry(snd_info_rtl8197d_i2s_entry);
	snd_info_free_entry(snd_info_rtl8197d_i2s_start_entry);
	return 0;
}


struct platform_driver rtl819x_iis_driver = {
	.probe  = rtl819x_iis_dev_probe,
	.remove = rtl819x_iis_dev_remove,
	.driver = {
		.name = "rtl819x-iis",
		.owner = THIS_MODULE,
	},
};
module_platform_driver(rtl819x_iis_driver);


/* Module information */
MODULE_AUTHOR("XU JUNWEI, <jwsyu@realtek.com>");
MODULE_DESCRIPTION("Realtek I2S DMA module");
MODULE_LICENSE("GP1");

