export PREFIX="/home/abhishek/build/usr/bin/"
export CROSS_COMPILE="${PREFIX}/arm-buildroot-linux-gnueabihf-"
export OUTDIR="$PWD/out/"
[ -d "$OUTDIR" ] || mkdir "$OUTDIR"

LIBUSB_CFLAGS=$(${PREFIX}pkg-config libusb-1.0 --cflags)
LIBUSB_LFLAGS=$(${PREFIX}pkg-config libusb-1.0 --libs)

# build libmirisdr
pushd libmirisdr-2/src
FILES="libmirisdr.c"
${CROSS_COMPILE}gcc -Wall -O3 -fPIC -shared -o ${OUTDIR}libmirisdr.so -I../include ${LIBUSB_CFLAGS} ${FILES} ${LIBUSB_LFLAGS}
popd

# build librtlsdr
pushd librtlsdr/src
FILES="librtlsdr.c tuner_e4k.c tuner_fc0012.c tuner_fc0013.c tuner_fc2580.c tuner_r82xx.c"
${CROSS_COMPILE}gcc -Wall -Wno-unused-function -Wno-unused-variable -O3 -fPIC -shared -o ${OUTDIR}librtlsdr.so -I../include ${LIBUSB_CFLAGS} ${FILES} ${LIBUSB_LFLAGS}
popd

# build starsdr
export DEPS=$OUTDIR
pushd starsdr
make
popd

cp starsdr/starsdr_ext.h $OUTDIR


