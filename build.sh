export PREFIX="/home/abhishek/build/usr/bin/"
export CROSS_COMPILE="${PREFIX}/arm-buildroot-linux-gnueabihf-"
export OUTDIR="$PWD/out/"
[ -d "$OUTDIR" ] || mkdir "$OUTDIR"

# build libmirisdr
pushd libmirisdr-2/src
${CROSS_COMPILE}gcc -Wall -fPIC -shared -o ${OUTDIR}libmirisdr.so -I../include `${PREFIX}pkg-config libusb-1.0 --cflags` libmirisdr.c `${PREFIX}pkg-config libusb-1.0 --libs`
popd

# build librtlsdr
pushd librtlsdr/src
${CROSS_COMPILE}gcc -Wall -fPIC -shared -o ${OUTDIR}librtlsdr.so -I../include `${PREFIX}pkg-config libusb-1.0 --cflags` librtlsdr.c `${PREFIX}pkg-config libusb-1.0 --libs`
popd

# build starsdr
export DEPS=$OUTDIR
pushd starsdr
make
popd

cp starsdr/starsdr_ext.h $OUTDIR


