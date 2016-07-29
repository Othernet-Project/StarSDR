GCC_PATH=$(shell which $(CROSS_COMPILE)gcc)
PKGCONFIG=$(shell dirname $(GCC_PATH))/pkg-config
OUTDIR=$(PWD)/out/
LIBUSB_CFLAGS=$(shell $(PKGCONFIG) libusb-1.0 --cflags)
LIBUSB_LFLAGS=$(shell $(PKGCONFIG) libusb-1.0 --libs)

.PHONY: clean clean_all libs all libmirisdr librtlsdr starsdr rtl_fm star_fm outdir

libs: outdir libmirisdr librtlsdr starsdr

all: libs star_fm rtl_biast

clean:
	rm -rf $(OUTDIR)

clean_all: clean
	make -C star_fm clean
	rm -f rtl_biast

outdir: 
	mkdir -p $(OUTDIR)

libmirisdr: libmirisdr-2/src/libmirisdr.c
	$(CROSS_COMPILE)gcc -Wall -O3 -fPIC -shared -o $(OUTDIR)libmirisdr.so -Ilibmirisdr-2/include $(LIBUSB_CFLAGS) $^ $(LIBUSB_LFLAGS)

librtlsdr: $(addprefix librtlsdr/src/, librtlsdr.c tuner_e4k.c tuner_fc0012.c tuner_fc0013.c tuner_fc2580.c tuner_r82xx.c)
	$(CROSS_COMPILE)gcc -Wall -Wno-unused-function -Wno-unused-variable -O3 -fPIC -shared -o $(OUTDIR)librtlsdr.so \
		-Ilibrtlsdr/include $(LIBUSB_CFLAGS) $^ $(LIBUSB_LFLAGS)

starsdr:
	OUTDIR=$(OUTDIR) DEPS=$(OUTDIR) CROSS_COMPILE=$(CROSS_COMPILE) make -C starsdr
	cp starsdr/starsdr_ext.h $(OUTDIR)

star_fm:
	DEPS=$(OUTDIR) CROSS_COMPILE=$(CROSS_COMPILE) make -C star_fm

rtl_biast: librtlsdr/src/rtl_biast.c
	$(CROSS_COMPILE)gcc -Wall -O3 -o rtl_biast -Ilibrtlsdr/include -I$(OUTDIR) $(LIBUSB_CFLAGS) $^ $(LIBUSB_LFLAGS) -L$(OUTDIR) -lrtlsdr
