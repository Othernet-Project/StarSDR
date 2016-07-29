#! /bin/bash

silent () {
$@ 2>&1 > /dev/null
}

if [[ "$ARCH" != "x64" ]]
then
CROSS_COMPILE="arm-buildroot-linux-gnueabihf-"
fi

PKGCONFIG=$(dirname $(which ${CROSS_COMPILE}gcc))/pkg-config

OUTDIR="$PWD/out/"
[ -d "$OUTDIR" ] || mkdir "$OUTDIR"

LIBUSB_CFLAGS=$(${PKGCONFIG} libusb-1.0 --cflags)
LIBUSB_LFLAGS=$(${PKGCONFIG} libusb-1.0 --libs)

# build libmirisdr
silent pushd libmirisdr-2/src
FILES="libmirisdr.c"
${CROSS_COMPILE}gcc -Wall -O3 -fPIC -shared -o ${OUTDIR}libmirisdr.so -I../include ${LIBUSB_CFLAGS} ${FILES} ${LIBUSB_LFLAGS}
silent popd > /dev/null

# build librtlsdr
silent pushd librtlsdr/src
FILES="librtlsdr.c tuner_e4k.c tuner_fc0012.c tuner_fc0013.c tuner_fc2580.c tuner_r82xx.c"
${CROSS_COMPILE}gcc -Wall -Wno-unused-function -Wno-unused-variable -O3 -fPIC -shared -o ${OUTDIR}librtlsdr.so -I../include ${LIBUSB_CFLAGS} ${FILES} ${LIBUSB_LFLAGS}
silent popd

# build starsdr
silent pushd starsdr
OUTDIR=${OUTDIR} DEPS=${OUTDIR} make
silent popd

cp starsdr/starsdr_ext.h $OUTDIR


silent pushd star_fm
DEPS=${OUTDIR} make
silent popd

