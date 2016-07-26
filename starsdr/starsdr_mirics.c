// Copyright Outernet Inc,2016
// based on SDRIO - Copyright Scott Cutler
// This source file is licensed under the GNU Lesser General Public License (LGPL)

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "starsdr_ext.h"

#define mirisdr_STATIC
#include "mirisdr.h"

#include "pthread.h"

#ifdef _WIN32
#include <Windows.h>
void usleep(unsigned long us) { Sleep(us / 1000); }
#endif

typedef struct starsdr_device_t
{
    starsdr_uint32 device_index;

    mirisdr_dev_t *mirics_device;

    starsdr_rx_async_callback callback;
    void *callback_context;
    pthread_t tid;

    starsdr_int16 *samples;
    starsdr_uint32 num_samples;

    starsdr_uint64 min_freq;
    starsdr_uint64 max_freq;
} starsdr_device;


// must be multiple of 512!
#define DEFAULT_USB_BULK_BUFFER_SIZE ((128 * 512))
static int usb_bulk_buffer_size = DEFAULT_USB_BULK_BUFFER_SIZE;


STARSDREXPORT starsdr_int32 starsdr_init()
{
    return 1;
}

STARSDREXPORT starsdr_int32 starsdr_get_num_devices()
{
    return mirisdr_get_device_count();
}

STARSDREXPORT starsdr_device * starsdr_open_device(starsdr_uint32 device_index)
{
    starsdr_device *dev = (starsdr_device *)malloc(sizeof(starsdr_device));

    if (dev)
    {
        memset(dev, 0, sizeof(starsdr_device));
        dev->device_index = device_index;

        mirisdr_open (&dev->mirics_device, dev->device_index);

        if (dev->mirics_device)
        {
            // we only do format 252_S16. Rest are for applications involving MUCH higher sample rates
            mirisdr_set_sample_format(dev->mirics_device, "252_S16");
            mirisdr_set_sample_rate(dev->mirics_device, 2*1024*1000);
            mirisdr_set_center_freq(dev->mirics_device, 100000000);
            mirisdr_set_tuner_gain_mode(dev->mirics_device, 0);

            dev->min_freq = 150000;
            dev->max_freq = 1900000000;
        }
        else
        {
            free(dev);
            return 0;
        }
    }

    return dev;
}

STARSDREXPORT starsdr_int32 starsdr_close_device(starsdr_device *dev)
{
    if (dev)
    {
        int ret = mirisdr_close(dev->mirics_device);
        dev->mirics_device = 0;
        return (ret == 0);
    }
    else
    {
        return 0;
    }
}

STARSDREXPORT const char * starsdr_get_device_string(starsdr_device *dev)
{
    if (dev)
    {
        return mirisdr_get_device_name(dev->device_index);
    }
    else
    {
        return 0;

    }
}

STARSDREXPORT starsdr_int32 starsdr_set_rx_samplerate(starsdr_device *dev, starsdr_uint64 sample_rate)
{
    if (dev)
    {
        return (mirisdr_set_sample_rate(dev->mirics_device, (uint32_t)sample_rate) == 0);
    }
    else
    {
        return 0;
    }
}

STARSDREXPORT starsdr_int32 starsdr_set_rx_frequency(starsdr_device *dev, starsdr_uint64 frequency)
{
    if (dev)
    {
        return (mirisdr_set_center_freq(dev->mirics_device, (uint32_t)frequency) == 0);
    }
    else
    {
        return 0;
    }
}

STARSDREXPORT starsdr_int32 starsdr_set_tx_samplerate(starsdr_device *dev, starsdr_uint64 sample_rate)
{
    return 0;
}

STARSDREXPORT starsdr_int32 starsdr_set_tx_frequency(starsdr_device *dev, starsdr_uint64 frequency)
{
    return 0;
}

void mirics_read_async_cb(unsigned char *buf, uint32_t len, void *ctx)
{
    starsdr_device *dev = (starsdr_device *)ctx;

    if (dev->callback)
    {
        starsdr_uint32 num_samples = len / (sizeof(starsdr_int16) * 2) ; // 4 bytes per sample

        if (dev->num_samples != num_samples)
        {
            dev->num_samples = num_samples;

            if (dev->samples)
            {
                free(dev->samples);
            }

            dev->samples = (starsdr_int16 *)malloc(dev->num_samples * sizeof(starsdr_int16) * 2);
        }

        if (dev->samples)
        {

            memcpy(dev->samples,buf,4 * dev->num_samples);

            dev->callback(dev->callback_context, dev->samples, dev->num_samples);
        }
    }
}

STARSDREXPORT void * start_rx_routine(void *ctx)
{
    starsdr_device *dev = (starsdr_device *)ctx;

    if (dev)
    {
        mirisdr_reset_buffer(dev->mirics_device);
        mirisdr_read_async(dev->mirics_device, mirics_read_async_cb, dev, 32, usb_bulk_buffer_size);
        pthread_exit(0);
    }

    return 0;
}

STARSDREXPORT starsdr_int32 starsdr_start_rx(starsdr_device *dev, starsdr_rx_async_callback callback, void *context, int usb_buffer_num_samples)
{

    // if buffer size not a multiple of 512
    if (usb_buffer_num_samples % 256)
        return 0;

    // if passed-in size is 0, use DEFAULT size
    if (usb_buffer_num_samples > 0)
        usb_bulk_buffer_size = usb_buffer_num_samples * 4; // 1 complex sample = 2 x int16 values
    else
        usb_bulk_buffer_size = DEFAULT_USB_BULK_BUFFER_SIZE;

    if (dev)
    {
        dev->callback = callback;
        dev->callback_context = context;
        return pthread_create(&dev->tid, 0, start_rx_routine, (void *)dev) == 0;
    }
    else
    {
        return 0;
    }
}

STARSDREXPORT starsdr_int32 starsdr_stop_rx(starsdr_device *dev)
{
    if (dev)
    {
        mirisdr_cancel_async(dev->mirics_device);
        mirisdr_stop_async(dev->mirics_device);
        pthread_join(dev->tid, 0);
        return 1;
    }
    else
    {
        return 0;
    }

}

STARSDREXPORT starsdr_int32 starsdr_start_tx(starsdr_device *dev, starsdr_tx_async_callback callback, void *context)
{
    return 0;
}

STARSDREXPORT starsdr_int32 starsdr_stop_tx(starsdr_device *dev)
{
    return 0;
}

STARSDREXPORT starsdr_int64 starsdr_get_rx_frequency(starsdr_device *dev)
{
    if (dev)
    {
        return mirisdr_get_center_freq(dev->mirics_device);
    }
    else
    {
        return 0;
    }
}

static const starsdr_uint32 sample_rates[] = {3*512*1024, 2*1024*1024, 4*1024*1024, 23*256*1024};

STARSDREXPORT starsdr_int32 starsdr_get_num_samplerates(starsdr_device *dev)
{
    return sizeof(sample_rates) / sizeof(sample_rates[0]);
}

STARSDREXPORT void starsdr_get_samplerates(starsdr_device *dev, starsdr_uint32 *sample_rates_out)
{
    memcpy(sample_rates_out, sample_rates, sizeof(sample_rates));
}

STARSDREXPORT starsdr_int64 starsdr_get_rx_samplerate(starsdr_device *dev)
{
    if (dev)
    {
        return mirisdr_get_sample_rate(dev->mirics_device);
    }
    else
    {
        return 0;
    }
}

STARSDREXPORT starsdr_int64 starsdr_get_tx_frequency(starsdr_device *dev)
{
    return 0;
}

STARSDREXPORT starsdr_int64 starsdr_get_tx_samplerate(starsdr_device *dev)
{
    return 0;
}

STARSDREXPORT starsdr_int32 starsdr_set_rx_gain_mode(starsdr_device *dev, starsdr_gain_mode gain_mode)
{
    if (dev)
    {
        switch (gain_mode)
        {
        case starsdr_gain_mode_agc:
            mirisdr_set_tuner_gain_mode(dev->mirics_device, 0);
            break;
        case starsdr_gain_mode_manual:
            mirisdr_set_tuner_gain_mode(dev->mirics_device, 1);
            break;
        default:
            return 0;
        }
    }
    return 1;
}

STARSDREXPORT starsdr_int32 starsdr_get_rx_gain_range(starsdr_device *dev, starsdr_float32 *min, starsdr_float32 *max)
{
    if (dev)
    {
        if (min) *min = 0.0f;
        if (max) *max = 102.0f;
        return 1;
    }
    else
    {
        return 0;
    }
}

STARSDREXPORT starsdr_int32 starsdr_set_rx_gain(starsdr_device *dev, starsdr_float32 gain)
{
    if (dev)
    {
        return (mirisdr_set_tuner_gain(dev->mirics_device, (int) floor(gain)) == 0);
    }
    else
    {
        return 0;
    }
}

STARSDREXPORT starsdr_int32 starsdr_get_tx_gain_range(starsdr_device *dev, starsdr_float32 *min, starsdr_float32 *max)
{
    return 0;
}

STARSDREXPORT starsdr_int32 starsdr_set_tx_gain(starsdr_device *dev, starsdr_float32 gain)
{
    return 0;
}

STARSDREXPORT void starsdr_get_tuning_range(starsdr_device *dev, starsdr_uint64 *min, starsdr_uint64 *max)
{
    if (dev)
    {
        if (min) *min = dev->min_freq;
        if (max) *max = dev->max_freq;
    }
}

STARSDREXPORT starsdr_int32 starsdr_get_caps(starsdr_device *dev, starsdr_caps caps)
{
    switch (caps)
    {
    case starsdr_caps_rx:  return  1;
    case starsdr_caps_tx:  return  0;
    case starsdr_caps_agc: return  1;
    default:             return -1;
    }
}


STARSDREXPORT starsdr_float32 starsdr_get_tuner_gain(starsdr_device *dev)
{
    return (starsdr_float32) mirisdr_get_tuner_gain(dev->mirics_device);
}

STARSDREXPORT starsdr_int32 starsdr_get_tuner_gains(starsdr_device *dev, starsdr_float32 *gains)
{
    return (starsdr_int32) mirisdr_get_tuner_gains(dev->mirics_device, (float *) gains);
}

STARSDREXPORT starsdr_int32 starsdr_get_sample_bitsize(starsdr_device *dev)
{
    return (starsdr_int32) 14;
}

