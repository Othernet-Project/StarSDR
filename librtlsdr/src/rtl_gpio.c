
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>

#include "rtl-sdr.h"
#include "convenience/convenience.h"

static rtlsdr_dev_t *dev = NULL;


void usage(void)
{
	fprintf(stderr,
		"rtl_gpio, read/write gpio on RTL2832 based DVB-T receivers\n\n"
		"Usage:\n"
		"\t[-g  gpio bit to read/write, default 0\n"
		"\t[-v  value to write: 0 or 1, default 0\n"
		"\t[-o  set gpio to output, default\n"
		"\t[-i  set gpio to input, read value, -v if given is ignored\n"
		"\t[-d  device\n");
	exit(1);
}



int main(int argc, char **argv)
{
	int dev_index = 0;
	int dev_given = 0;
	int gpio_bit = 0;
	int gpio_value = -1;
	int gpio_input = 0;
	int r;
	int opt;

	while ((opt = getopt(argc, argv, "d:g:v:oi")) != -1) {
		switch (opt) {
		case 'd':
			dev_index = verbose_device_search(optarg);
			dev_given = 1;
			break;
		case 'g':
			gpio_bit = (uint32_t)atof(optarg);
			break;
		case 'v':
			gpio_value = ((uint32_t)atof(optarg)==0)? 0 : 1;
			break;
		case 'o':
			gpio_input = 0;// output mode
			break;
		case 'i':
			gpio_input = 1;
			break;
		default:
			usage();
			break;
		}
	}

	if (!dev_given) {
		dev_index = verbose_device_search("0");
	}

	if (dev_index < 0) {
		exit(1);
	}

	r = rtlsdr_open(&dev, (uint32_t)dev_index);
	if (r < 0) {
		fprintf(stderr, "Failed to open rtlsdr device #%d.\n", dev_index);
		exit(1);
	}

	/* Reset endpoint before we start reading from it (mandatory) */
	verbose_reset_buffer(dev);

	if (gpio_input) { // put gpio in input mode, and read from it, print value
		rtlsdr_set_gpio_input(dev, gpio_bit);
		r = rtlsdr_get_gpio_bit(dev, gpio_bit);
		printf("%d\n", r);
	} else { // put gpio in output mode, write value to it, print old value.
		rtlsdr_set_gpio_output(dev, gpio_bit);
                r = rtlsdr_get_gpio_bit(dev, gpio_bit);
                printf("%d\n", r);
		if (gpio_value > -1)
			rtlsdr_set_gpio_bit(dev, gpio_bit, gpio_value);
	}

	rtlsdr_close(dev);

	return r >= 0 ? r : -r;
}

