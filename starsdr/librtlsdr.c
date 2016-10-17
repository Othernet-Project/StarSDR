
#include "rtlsdr_rpc.h"
#include "rtl-sdr.h"

int rtlsdr_set_xtal_freq(rtlsdr_dev_t *dev, uint32_t rtl_freq, uint32_t tuner_freq)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_xtal_freq(dev, rtl_freq, tuner_freq);
	}
}

int rtlsdr_get_xtal_freq(rtlsdr_dev_t *dev, uint32_t *rtl_freq, uint32_t *tuner_freq)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_xtal_freq(dev, rtl_freq, tuner_freq);
	}
}

int rtlsdr_get_usb_strings(rtlsdr_dev_t *dev, char *manufact, char *product,
			    char *serial)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_usb_strings(dev, manufact, product, serial);
	}
}

int rtlsdr_write_eeprom(rtlsdr_dev_t *dev, uint8_t *data, uint8_t offset, uint16_t len)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_write_eeprom(dev, data, offset, len);
	}
}

int rtlsdr_read_eeprom(rtlsdr_dev_t *dev, uint8_t *data, uint8_t offset, uint16_t len)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_read_eeprom(dev, data, offset, len);
	}
}

int rtlsdr_set_center_freq(rtlsdr_dev_t *dev, uint32_t freq)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_center_freq(dev, freq);
	}
}

uint32_t rtlsdr_get_center_freq(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_center_freq(dev);
	}
}

int rtlsdr_set_freq_correction(rtlsdr_dev_t *dev, int ppm)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_freq_correction(dev, ppm);
	}
}

int rtlsdr_get_freq_correction(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_freq_correction(dev);
	}
}

enum rtlsdr_tuner rtlsdr_get_tuner_type(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return (enum rtlsdr_tuner)rtlsdr_rpc_get_tuner_type(dev);
	}
}

int rtlsdr_get_tuner_gains(rtlsdr_dev_t *dev, int *gains)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_tuner_gains(dev, gains);
	}
}

int rtlsdr_set_tuner_gain(rtlsdr_dev_t *dev, int gain)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_tuner_gain(dev, gain);
	}
}

int rtlsdr_get_tuner_gain(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_tuner_gain(dev);
	}
}

int rtlsdr_set_tuner_if_gain(rtlsdr_dev_t *dev, int stage, int gain)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_tuner_if_gain(dev, stage, gain);
	}
}

int rtlsdr_set_tuner_gain_mode(rtlsdr_dev_t *dev, int mode)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_tuner_gain_mode(dev, mode);
	}
}

int rtlsdr_set_sample_rate(rtlsdr_dev_t *dev, uint32_t samp_rate)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_sample_rate(dev, samp_rate);
	}
}

uint32_t rtlsdr_get_sample_rate(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_sample_rate(dev);
	}
}

int rtlsdr_set_testmode(rtlsdr_dev_t *dev, int on)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_testmode(dev, on);
	}
}

int rtlsdr_set_agc_mode(rtlsdr_dev_t *dev, int on)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_agc_mode(dev, on);
	}
}

int rtlsdr_set_direct_sampling(rtlsdr_dev_t *dev, int on)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_direct_sampling(dev, on);
	}
}

int rtlsdr_get_direct_sampling(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_direct_sampling(dev);
	}
}

int rtlsdr_set_offset_tuning(rtlsdr_dev_t *dev, int on)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_set_offset_tuning(dev, on);
	}
}

int rtlsdr_get_offset_tuning(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_offset_tuning(dev);
	}

}

uint32_t rtlsdr_get_device_count(void)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_device_count();
	}
}

const char *rtlsdr_get_device_name(uint32_t index)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_device_name(index);
	}
}

int rtlsdr_get_device_usb_strings(uint32_t index, char *manufact,
				   char *product, char *serial)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_device_usb_strings
	    (index, manufact, product, serial);
	}
}

int rtlsdr_get_index_by_serial(const char *serial)
{

	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_get_index_by_serial(serial);
	}

}

int rtlsdr_open(rtlsdr_dev_t **out_dev, uint32_t index)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_open((void**)out_dev, index);
	}

}

int rtlsdr_close(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_close(dev);
	}

}

int rtlsdr_reset_buffer(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_reset_buffer(dev);
	}

}

int rtlsdr_read_sync(rtlsdr_dev_t *dev, void *buf, int len, int *n_read)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_read_sync(dev, buf, len, n_read);
	}
}


int rtlsdr_wait_async(rtlsdr_dev_t *dev, rtlsdr_read_async_cb_t cb, void *ctx)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_wait_async(dev, cb, ctx);
	}

}

int rtlsdr_read_async(rtlsdr_dev_t *dev, rtlsdr_read_async_cb_t cb, void *ctx,
			  uint32_t buf_num, uint32_t buf_len)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_read_async(dev, cb, ctx, buf_num, buf_len);
	}

}

int rtlsdr_cancel_async(rtlsdr_dev_t *dev)
{
	if (rtlsdr_rpc_is_enabled())
	{
	  return rtlsdr_rpc_cancel_async(dev);
	}

}

