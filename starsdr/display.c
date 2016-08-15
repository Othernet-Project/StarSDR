// parts (C) 2016 Outernet Inc
// derived from code by Brian Hammond, 1996

/*
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
*/

/* include the X library headers */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

/* include some silly stuff */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

/* here are our X variables */
Display *dis;
int screen;
Window win;
GC gc;

/* here are our X routines declared! */
void redraw();

#define MAXPOINTS 25000
//#define WINSIZE  512
int winsize;
int batches;

XPoint *points;


unsigned long black,white;


void plot(int num_samples) {
	XSetForeground(dis,gc,black);
	XDrawPoints(dis, win, gc, points, num_samples, CoordModeOrigin);
};


void read_n_draw(int16_t *d, int n) {
	int m;
	for(m=0;m<n; m++) {
		points[m].x = (d[2*m] >> 5) + (winsize>>1);
		points[m].y = (d[2*m+1] >>  5) + (winsize>>1);
	}
	plot(n);
}


void const_plot (int16_t *data, int num_points) {
	static int count=0;
	count++;

	if (count>batches)
	{
		XClearWindow(dis, win);
		count = 0;
	}
	read_n_draw(data, num_points);

}


void const_init(int b, int ws) {
	winsize = ws;
	batches =b ;
	points = malloc(sizeof(XPoint)*2*MAXPOINTS);
	batches = batches;
	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),
	white=WhitePixel(dis, screen);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,
		winsize, winsize, 5,black, white);
	XSetStandardProperties(dis,win,"Constelation","StarSDR",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask);
        gc=XCreateGC(dis, win, 0,0);
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
};

void const_close() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);
	//exit(1);
};

void redraw() {
	XClearWindow(dis, win);
};

