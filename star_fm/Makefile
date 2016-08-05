
.PHONY: all clean

all: star_fm

star_fm: star_fm.c convenience.c
	rm -f ./libstarsdr.so
	ln -s $(DEPS)libstarsdr_mirics.so ./libstarsdr.so
	$(CC) -Wall -O3 $(CFLAGS) -o star_fm -I../include -I$(DEPS) $^ -Wl,--allow-shlib-undefined $(LFLAGS) -L$(DEPS) -L. -lpthread -lm -lstarsdr
	rm -f ./libstarsdr.so

display: display.c
	$(CROSS_COMPILE)gcc -Wall -O3 -Wno-unused-result -o display $^ -lX11

clean:
	rm -f star_fm display


