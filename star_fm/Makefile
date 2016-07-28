PREFIX=/home/abhishek/build/usr/bin
CROSS_COMPILE=$(PREFIX)/arm-buildroot-linux-gnueabihf-
DEPS=.

star_fm: star_fm.c starsdr_ext.h convenience.c convenience.h
	$(CROSS_COMPILE)gcc -Wall -O3  -shared -o star_fm star_fm.c  convenience.c  -I. -L$(DEPS) -lstarsdr


