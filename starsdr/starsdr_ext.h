// modified from sdrio_ext.h, Copyright Scott Cutler

/*
# (c) 2016 Outernet Inc
# This file is part of StarSDR.

# StarSDR is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesseer General Public License as 
# published by the Free Software Foundation, either version 3 of 
# the License, or (at your option) any later version.

# StarSDR is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public 
# License along with StarSDR.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
typedef uint8_t starsdr_uint8;
typedef int8_t starsdr_int8;

typedef uint16_t starsdr_uint16;
typedef int16_t starsdr_int16;

typedef uint32_t starsdr_uint32;
typedef int32_t starsdr_int32;

typedef uint64_t starsdr_uint64;
typedef int64_t starsdr_int64;

typedef float starsdr_float32;
typedef double starsdr_float64;


struct starsdr_device_t;
typedef struct starsdr_device_t starsdr_device;

typedef enum
{
    starsdr_gain_mode_agc,
    starsdr_gain_mode_manual
} starsdr_gain_mode;

typedef enum
{
    starsdr_caps_rx,
    starsdr_caps_tx,
    starsdr_caps_agc
} starsdr_caps;


typedef starsdr_int32 (*starsdr_rx_async_callback)(void *context, starsdr_int16 *samples, starsdr_int32 num_samples);
typedef starsdr_int32 (*starsdr_tx_async_callback)(void *context, starsdr_int16 *samples, starsdr_int32 num_samples);



#if __GNUC__ >= 4
    #define STARSDREXPORT  __attribute__ ((visibility ("default")))
#else
    #define STARSDREXPORT
#endif


typedef starsdr_int32 (*starsdr_init_t)();

typedef starsdr_int32 (*starsdr_get_num_devices_t)();

typedef starsdr_device * (*starsdr_open_device_t)(starsdr_uint32 device_index);
typedef starsdr_int32 (*starsdr_close_device_t)(starsdr_device *dev);

typedef const char * (*starsdr_get_device_string_t)(starsdr_uint32 device_index);

typedef starsdr_int32 (*starsdr_set_rx_samplerate_t)(starsdr_device *dev, starsdr_uint64 sample_rate);
typedef starsdr_int32 (*starsdr_set_rx_frequency_t)(starsdr_device *dev, starsdr_uint64 frequency);

typedef starsdr_int32 (*starsdr_set_tx_samplerate_t)(starsdr_device *dev, starsdr_uint64 sample_rate);
typedef starsdr_int32 (*starsdr_set_tx_frequency_t)(starsdr_device *dev, starsdr_uint64 frequency);

typedef starsdr_int32 (*starsdr_start_rx_t)(starsdr_device *dev, starsdr_rx_async_callback callback, void *context, int usb_buffer_num_samples);
typedef starsdr_int32 (*starsdr_stop_rx_t)(starsdr_device *dev);

typedef starsdr_int32 (*starsdr_start_tx_t)(starsdr_device *dev, starsdr_tx_async_callback callback, void *context);
typedef starsdr_int32 (*starsdr_stop_tx_t)(starsdr_device *dev);

typedef starsdr_int32 (*starsdr_get_num_samplerates_t)(starsdr_device *dev);
typedef void        (*starsdr_get_samplerates_t)(starsdr_device *dev, starsdr_uint32 *sample_rates_out);

typedef starsdr_int64 (*starsdr_get_rx_frequency_t)(starsdr_device *dev);
typedef starsdr_int64 (*starsdr_get_rx_samplerate_t)(starsdr_device *dev);

typedef starsdr_int64 (*starsdr_get_tx_frequency_t)(starsdr_device *dev);
typedef starsdr_int64 (*starsdr_get_tx_samplerate_t)(starsdr_device *dev);

typedef starsdr_int32 (*starsdr_set_rx_gain_mode_t)(starsdr_device *dev, starsdr_gain_mode gain_mode);
typedef starsdr_int32 (*starsdr_get_rx_gain_range_t)(starsdr_device *dev, starsdr_float32 *min, starsdr_float32 *max);
typedef starsdr_int32 (*starsdr_set_rx_gain_t)(starsdr_device *dev, starsdr_float32 gain);

typedef starsdr_int32 (*starsdr_get_tx_gain_range_t)(starsdr_device *dev, starsdr_float32 *min, starsdr_float32 *max);
typedef starsdr_int32 (*starsdr_set_tx_gain_t)(starsdr_device *dev, starsdr_float32 gain);

typedef void        (*starsdr_get_tuning_range_t)(starsdr_device *dev, starsdr_uint64 *min, starsdr_uint64 *max);
typedef starsdr_int32 (*starsdr_get_caps_t)(starsdr_device *dev, starsdr_caps caps);

typedef starsdr_float32 (*starsdr_get_tuner_gain_t) (starsdr_device *dev);

typedef starsdr_int32 (*starsdr_get_tuner_gains_t) (starsdr_device *dev, starsdr_float32 *gains);

typedef starsdr_int32 (*starsdr_get_sample_bitsize_t) (starsdr_device *dev);

#ifdef __cplusplus
extern "C" {
#endif

    STARSDREXPORT starsdr_int32 starsdr_init();

    STARSDREXPORT starsdr_int32 starsdr_get_num_devices();

    STARSDREXPORT starsdr_device * starsdr_open_device(starsdr_uint32 device_index);
    STARSDREXPORT starsdr_int32 starsdr_close_device(starsdr_device *dev);

    STARSDREXPORT const char * starsdr_get_device_string(starsdr_uint32 device_index);

    STARSDREXPORT starsdr_int32 starsdr_set_rx_samplerate(starsdr_device *dev, starsdr_uint64 sample_rate);
    STARSDREXPORT starsdr_int32 starsdr_set_rx_frequency(starsdr_device *dev, starsdr_uint64 frequency);

    STARSDREXPORT starsdr_int32 starsdr_set_tx_samplerate(starsdr_device *dev, starsdr_uint64 sample_rate);
    STARSDREXPORT starsdr_int32 starsdr_set_tx_frequency(starsdr_device *dev, starsdr_uint64 frequency);

    STARSDREXPORT starsdr_int32 starsdr_start_rx(starsdr_device *dev, starsdr_rx_async_callback callback, void *context, int usb_buffer_num_samples);
    STARSDREXPORT starsdr_int32 starsdr_stop_rx(starsdr_device *dev);

    STARSDREXPORT starsdr_int32 starsdr_start_tx(starsdr_device *dev, starsdr_rx_async_callback callback, void *context);
    STARSDREXPORT starsdr_int32 starsdr_stop_tx(starsdr_device *dev);

    STARSDREXPORT starsdr_int32 starsdr_get_num_samplerates(starsdr_device *dev);
    STARSDREXPORT void        starsdr_get_samplerates(starsdr_device *dev, starsdr_uint32 *sample_rates_out);

    STARSDREXPORT starsdr_int64 starsdr_get_rx_frequency(starsdr_device *dev);
    STARSDREXPORT starsdr_int64 starsdr_get_rx_samplerate(starsdr_device *dev);

    STARSDREXPORT starsdr_int64 starsdr_get_tx_frequency(starsdr_device *dev);
    STARSDREXPORT starsdr_int64 starsdr_get_tx_samplerate(starsdr_device *dev);

    STARSDREXPORT starsdr_int32 starsdr_set_rx_gain_mode(starsdr_device *dev, starsdr_gain_mode gain_mode);
    STARSDREXPORT starsdr_int32 starsdr_get_rx_gain_range(starsdr_device *dev, starsdr_float32 *min, starsdr_float32 *max);
    STARSDREXPORT starsdr_int32 starsdr_set_rx_gain(starsdr_device *dev, starsdr_float32 gain);

    STARSDREXPORT starsdr_int32 starsdr_get_tx_gain_range(starsdr_device *dev, starsdr_float32 *min, starsdr_float32 *max);
    STARSDREXPORT starsdr_int32 starsdr_set_tx_gain(starsdr_device *dev, starsdr_float32 gain);

    STARSDREXPORT void        starsdr_get_tuning_range(starsdr_device *dev, starsdr_uint64 *min, starsdr_uint64 *max);
    STARSDREXPORT starsdr_int32 starsdr_get_caps(starsdr_device *dev, starsdr_caps caps);

    STARSDREXPORT starsdr_float32 starsdr_get_tuner_gain(starsdr_device *dev);

    STARSDREXPORT starsdr_int32 starsdr_get_tuner_gains(starsdr_device *dev, starsdr_float32 *gains);

    STARSDREXPORT starsdr_int32 starsdr_get_sample_bitsize(starsdr_device *dev);

#ifdef __cplusplus
}
#endif
