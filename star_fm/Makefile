all: star_fm

star_fm: star_fm.c convenience.c convenience.h
	rm -f ./libstarsdr.so
	ln -s $(DEPS)libstarsdr_mirics.so ./libstarsdr.so
	$(CROSS_COMPILE)gcc -Wall -O3 -o star_fm -I../include -I$(DEPS) star_fm.c convenience.c -L$(DEPS) -L. -lpthread -lm -lstarsdr -lmirisdr -lrtlsdr
	rm -f ./libstarsdr.so

clean:
	rm star_fm

