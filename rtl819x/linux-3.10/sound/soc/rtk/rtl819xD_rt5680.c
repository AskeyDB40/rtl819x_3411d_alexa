/*
 * rtl819xD_rt5621.c - Realtek machine ASoC driver.
 *
 * Author: Johnny Hsu <johnnyhsu@realtek.com>
 * Copyright 2012 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see the file COPYING, or write
 * to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/timer.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/tlv.h>
#include <sound/pcm_params.h>

#include "rtl819x-pcm.h"
#include "rtl8197d-i2s.h"

static int rtl819xd_rt5680_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	
	return 0;
}

static struct snd_soc_ops rtl819xd_rt5680_ops = {
	.hw_params = rtl819xd_rt5680_hw_params,
};

static const struct snd_soc_dapm_widget rtl819xd_dapm_widgets[] = {
	SND_SOC_DAPM_MIC("Int Mic", NULL),
};

static const struct snd_soc_dapm_route rtl819xd_audio_map[] = {
	{"Mic Bias1", NULL, "Int Mic"},
	{"Mic1", NULL, "Mic Bias1"},
};


static int rtl819xd_rt5680_rt5680_init(struct snd_soc_codec *codec)
{
		
	return 0;
}

static struct snd_soc_dai_link rtl819xd_rt5680_dai[] = {
	[0] ={ 
		.name = "rtl819xd_rt5680_dai_P",
		.stream_name = "AIF1 Playback",
		.cpu_dai_name = "rtl819x-iis",
		.codec_dai_name = "snd-soc-dummy-dai",
		.platform_name = "rtl819x-iis",
		.codec_name = "snd-soc-dummy",
		.ops = &rtl819xd_rt5680_ops,
		.init = rtl819xd_rt5680_rt5680_init,
	},
#if 0	
	[1] = { /* Primary Capture i/f */
		.name = "rtl819xd_rt5680_dai_C",
		.stream_name = "AIF1 Capture",
		.cpu_dai_name = "rtl819x-iis",
		.codec_dai_name = "snd-soc-dummy-dai",
		.platform_name = "rtl819x-iis",
		.codec_name = "snd-soc-dummy",
		.init = rtl819xd_rt5680_rt5680_init,
		.ops = &rtl819xd_rt5680_ops,
	},
#endif

		
};

static struct snd_soc_card rtl819xd_rt5680 = {
	.name = "rtl819xd_rt5680",
	.owner = THIS_MODULE,
	.dai_link = rtl819xd_rt5680_dai,
	.num_links = ARRAY_SIZE(rtl819xd_rt5680_dai),
};



static struct platform_device *rtl819xd_snd_device;


static int __init rtl819x_rt5680_modinit(void)
{
	int ret=0;
	rtl819xd_snd_device = platform_device_alloc("soc-audio", -1);
	if (!rtl819xd_snd_device)
		return -ENOMEM;

	platform_set_drvdata(rtl819xd_snd_device, &rtl819xd_rt5680);
	ret = platform_device_add(rtl819xd_snd_device);
	if (ret){
		platform_device_put(rtl819xd_snd_device);
	}
	return 0;
}
module_init(rtl819x_rt5680_modinit);

static void __exit rtl819x_rt5680_modexit(void)
{
	platform_device_unregister(rtl819xd_snd_device);
}
module_exit(rtl819x_rt5680_modexit);




MODULE_DESCRIPTION("ASoC CS4344 driver");
MODULE_AUTHOR("Johnny Hsu <johnnyhsu@realtek.com>");
MODULE_LICENSE("GPL");
