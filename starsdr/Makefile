
.PHONY: all starsdr_mirics starsdr_rtlsdr

ifneq (,$(findstring GUI,$(FLAGS)))
    CFLAGS += -DGUI
    LFLAGS += -lX11
endif

ifneq (,$(findstring DCFILTER,$(FLAGS)))
    CFLAGS += -DDCFILTER
endif

all: starsdr_mirics starsdr_rtlsdr

starsdr_mirics: starsdr_mirics.c starsdr_ext.h
	$(CC) -Wall -O3 -fPIC $(CFLAGS) -shared \
		-o ${OUTDIR}libstarsdr_mirics.so starsdr_mirics.c  -I. $(LFLAGS) -L${DEPS} -lmirisdr
	
starsdr_rtlsdr: starsdr_rtlsdr.c starsdr_ext.h
	$(CC) -Wall -O3 -fPIC $(CFLAGS) -shared -o ${OUTDIR}libstarsdr_rtlsdr.so starsdr_rtlsdr.c  -I. $(LFLAGS) -L${DEPS} -lrtlsdr

