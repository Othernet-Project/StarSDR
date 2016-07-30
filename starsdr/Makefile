
.PHONY: all starsdr_mirics starsdr_rtlsdr

all: starsdr_mirics starsdr_rtlsdr

starsdr_mirics: starsdr_mirics.c starsdr_ext.h
	$(CROSS_COMPILE)gcc -Wall -O3 -fPIC -shared -o ${OUTDIR}libstarsdr_mirics.so starsdr_mirics.c  -I. -L${DEPS} -lmirisdr
	
starsdr_rtlsdr: starsdr_rtlsdr.c starsdr_ext.h
	$(CROSS_COMPILE)gcc -Wall -O3 -fPIC -shared -o ${OUTDIR}libstarsdr_rtlsdr.so starsdr_rtlsdr.c  -I. -L${DEPS} -lrtlsdr

