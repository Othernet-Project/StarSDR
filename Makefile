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

# cross compile examples
# for arm:
# CC=arm-buildroot-linux-gnueabihf-gcc make libs
# for x64
# make libs
# for x32
# CFLAGS=-m32 make libs

CC ?=gcc
CC_PATH=$(shell which $(CC))
PKGCONFIG=$(shell dirname $(CC_PATH))/pkg-config
OUTDIR=$(shell pwd)/out/
LIBUSB_CFLAGS=$(shell $(PKGCONFIG) libusb-1.0 --cflags)
LIBUSB_LFLAGS=$(shell $(PKGCONFIG) libusb-1.0 --libs)
PREFIX := /usr/local
SDRD = $(PREFIX)/sdr.d
RTLDIR = $(SDRD)/starsdr-rtlsdr
MIRDIR = $(SDRD)/starsdr-mirics


.PHONY: clean clean_all libs all libmirisdr librtlsdr starsdr rtl_fm star_fm \
	outdir release some install uninstall

libs: outdir libmirisdr librtlsdr starsdr

some: libs rtl_biast

all: libs star_fm rtl_biast

install:
	install -Dm755 {.,$(RTLDIR)}/rtl_biast
	install -Dm755 {$(OUTDIR),$(RTLDIR)/}librtlsdr.so
	install -Dm755 $(OUTDIR)libstarsdr_rtlsdr.so $(RTLDIR)/libstarsdr.so
	install -Dm755 {$(OUTDIR),$(MIRDIR)/}libmirisdr.so
	install -Dm755 $(OUTDIR)libstarsdr_mirics.so $(MIRDIR)/libstarsdr.so

uninstall:
	-rm -rf $(SDRD)

clean:
	rm -rf $(OUTDIR)

clean_all: clean
	make -C star_fm clean
	rm -f rtl_biast

outdir: 
	mkdir -p $(OUTDIR)

libmirisdr: libmirisdr-2/src/libmirisdr.c
	$(CC) -Wall -O3 -fPIC $(CFLAGS) $(LIBSDR_CFLAGS) -shared \
		-o $(OUTDIR)libmirisdr.so -Ilibmirisdr-2/include $(LIBUSB_CFLAGS) $^ $(LFLAGS) $(LIBSDR_LFLAGS) $(LIBUSB_LFLAGS)

librtlsdr: $(addprefix librtlsdr/src/, librtlsdr.c tuner_e4k.c tuner_fc0012.c tuner_fc0013.c tuner_fc2580.c tuner_r82xx.c)
	$(CC) -Wall -Wno-unused-function -Wno-unused-variable -O3 -fPIC $(CFLAGS) $(LIBSDR_CFLAGS) -shared -o $(OUTDIR)librtlsdr.so \
		-Ilibrtlsdr/include $(LIBUSB_CFLAGS) $^ $(LFLAGS) $(LIBSDR_LFLAGS) $(LIBUSB_LFLAGS)

starsdr:
	OUTDIR=$(OUTDIR) DEPS=$(OUTDIR) CC=$(CC) CFLAGS=$(CFLAGS) LFLAGS=$(LFLAGS) FLAGS=$(FLAGS) make -C starsdr
	cp starsdr/starsdr_ext.h $(OUTDIR)

star_fm:
	DEPS=$(OUTDIR) CC=$(CC) CFLAGS=$(CFLAGS) LFLAGS=$(LFLAGS) FLAGS=$(FLAGS) make -C star_fm

rtl_biast: librtlsdr/src/rtl_biast.c
	$(CC) -Wall -O3 $(CFLAGS) -o rtl_biast -Ilibrtlsdr/include -I$(OUTDIR)  $^  $(LFLAGS) -L$(OUTDIR) -lrtlsdr

release: libs
	mv $(OUTDIR) starsdr_release_$(VER)
	tar acf starsdr_release_$(VER).tgz starsdr_release_$(VER)
	mv starsdr_release_$(VER).tgz starsdr_release_$(VER) ..
	echo Made starsdr_release_$(VER)

