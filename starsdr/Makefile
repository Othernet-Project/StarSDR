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


.PHONY: all starsdr_mirics starsdr_rtlsdr

ifneq (,$(findstring GUI,$(FLAGS)))
    CFLAGS += -DGUI
    LFLAGS += -lX11
endif

ifneq (,$(findstring DCFILTER,$(FLAGS)))
    CFLAGS += -DDCFILTER
endif

#all: starsdr_mirics starsdr_rtlsdr
#all: starsdr_rtlsdr
all: starsdr

#starsdr_mirics: starsdr_mirics.c starsdr_ext.h
#	$(CC) -Wall -O3 -fPIC $(CFLAGS) -shared \
#		-o ${OUTDIR}libstarsdr_mirics.so starsdr_mirics.c  -I. $(LFLAGS) -L${DEPS} -lmirisdr

#starsdr_rtlsdr: starsdr_rtlsdr.c starsdr_ext.h
#	$(CC) -Wall -O3 -fPIC $(CFLAGS) -shared -o ${OUTDIR}libstarsdr_rtlsdr.so starsdr_rtlsdr.c  -I. $(LFLAGS) -L${DEPS} -lrtlsdr

starsdr: starsdr_rtlsdr.c rtlsdr_rpc.c rtlsdr_rpc_msg.c starsdr_ext.h
	$(CC) -Wall -O6 -fPIC $(CFLAGS) -shared -I../include -o ${OUTDIR}libstarsdr.so starsdr_rtlsdr.c librtlsdr.c rtlsdr_rpc.c rtlsdr_rpc_msg.c
