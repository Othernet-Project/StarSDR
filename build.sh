#PREFIX="/home/abhishek/build/usr/bin/"
#CROSS_COMPILE="${PREFIX}/arm-buildroot-linux-gnueabihf-"
OUTDIR="$PWD/out/"
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
DEPS=$OUTDIR
pushd starsdr
OUTDIR=${OUTDIR} make
popd

cp starsdr/starsdr_ext.h $OUTDIR

pushd star_fm
FILES="star_fm.c  convenience.c"
[ -f ${OUTDIR}/libstarsdr.so ] && unlink ${OUTDIR}/libstarsdr.so
ln -s ${OUTDIR}/libstarsdr_mirics.so ${OUTDIR}/libstarsdr.so
#${CROSS_COMPILE}gcc -Wall -O3 -o ${OUTDIR}/star_fm -I../include ${LIBUSB_CFLAGS} ${FILES} -z muldefs ${LIBUSB_LFLAGS} -L${OUTDIR} -lpthread -lm -lstarsdr_mirics -lstarsdr_rtlsdr -lmirisdr -lrtlsdr
${CROSS_COMPILE}gcc -Wall -O3 -o ${OUTDIR}/star_fm -I../include ${LIBUSB_CFLAGS} ${FILES} ${LIBUSB_LFLAGS} -L${OUTDIR} -lpthread -lm -lstarsdr -lmirisdr -lrtlsdr
popd

