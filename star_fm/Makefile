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


.PHONY: all clean

all: star_fm

star_fm: star_fm.c convenience.c
	#rm -f ./libstarsdr.so
	#ln -s $(DEPS)libstarsdr_rtlsdr.so ./libstarsdr.so
	$(CC) -Wall -O3 $(CFLAGS) -o star_fm -I../include -I$(DEPS) $^ -Wl,--allow-shlib-undefined $(LFLAGS) -L$(DEPS) -L. -lpthread -lm -lstarsdr
	#rm -f ./libstarsdr.so

display: display.c
	$(CROSS_COMPILE)gcc -Wall -O3 -Wno-unused-result -o display $^ -lX11

clean:
	rm -f star_fm display
