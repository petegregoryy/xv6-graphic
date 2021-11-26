#include "types.h"
#include "defs.h"
#include "memlayout.h"
#include "funcs.h"
#include "x86.h"
#include "graphics.h"
#include "spinlock.h"

struct hdc
{
	int locked;
	int colourIndex;
	int moveX;
	int moveY;
};

struct hdctable{
	struct spinlock lock;
	struct hdc devices[100];
};

struct rect
{
	int top;
	int left;
	int bottom;
	int right;
};

struct command {
    int command;
    int hdc;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int arg7;
    int arg8;
};

struct commandHolder{
    struct command commands[100];
};

struct hdctable hdctable = {};

void clear320x200x256()
{
	// You need to put code to clear the video buffer here.  Initially,
	// you might just set each pixel to black in a nested loop, but think
	// about faster ways to do it.
	//
	// This function is called from videosetmode.

	memset(P2V(0xA0000), 0, (320 * 200));
}

void graphicsinit(void){
	initlock(&hdctable.lock,"hdctable");
}

// Global Variables

struct hdc devices[10];

int colourIndex = 15;

int moveX = 0;
int moveY = 0;

int sys_setpixelSys(void)
{
	int hdc;
	int x;
	int y;

	if (argint(0, &hdc) < 0)
	{
		return -1;
	}
	if (argint(1, &x) < 0)
	{
		return -1;
	}
	if (argint(2, &y) < 0)
	{
		return -1;
	}

	uchar *pixel = P2V(0xA0000 + 320 * y + x);
	*pixel = hdctable.devices[hdc].colourIndex;
	return 0;
}


int sys_movetoSys(void)
{
	int hdc;
	int x;
	int y;

	if (argint(0, &hdc) < 0)
	{
		return -1;
	}
	if (argint(1, &x) < 0)
	{
		return -1;
	}
	if (argint(2, &y) < 0)
	{
		return -1;
	}

	hdctable.devices[hdc].moveX = x;
	hdctable.devices[hdc].moveY = y;
	return 0;
}

int sys_linetoSys(void)
{
	int hdc;

	int x1, y1;
	int dx, dy;
	int sx, sy;
	int err;
	int e2;

	//cprintf("Move X = %d\n", x0);
	//cprintf("Move Y = %d\n", y0);

	if (argint(0, &hdc) < 0)
	{
		return -1;
	}
	if (argint(1, &x1) < 0)
	{
		return -1;
	}
	if (argint(2, &y1) < 0)
	{
		return -1;
	}

	int x0 = hdctable.devices[hdc].moveX;
	int y0 = hdctable.devices[hdc].moveY;

	// Clip values to screen bounds
	if (x1 > 319)
	{
		x1 = 319;
	}
	else if (x1 < 0)
	{
		x1 = 0;
	}
	if (y1 > 199)
	{
		y1 = 199;
	}
	else if (y1 < 0)
	{
		y1 = 0;
	}

	hdctable.devices[hdc].moveX = x1;
	hdctable.devices[hdc].moveY = y1;

	//cprintf("Target X = %d\n", x1);
	//cprintf("Target Y = %d\n", y1);

	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;

	//cprintf("dx: %d\n", dx);
	//cprintf("sx: %d\n", sx);
	//cprintf("dy: %d\n", dy);
	//cprintf("sy: %d\n", sy);

	err = dx + dy;

	while (x0 != x1 || y0 != y1)
	{
		uchar *pixel = P2V(0xA0000 + 320 * y0 + x0);
		*pixel = hdctable.devices[hdc].colourIndex;
		e2 = 2 * err;
		//cprintf("x0: %d x1: %d y0: %d y1 %d\n", x0, x1, y0, y1);
		//cprintf("e2: %d dy %d", e2, dy);
		if (e2 >= dy)
		{
			err += dy;
			//cprintf("x0: %d sx: %d x0+=sx: %d\n", x0, sx, x0 + sx); /// Comments used in debugging!
			x0 += sx;
		}
		//cprintf("e2: %d dx %d", e2, dx);
		if (e2 <= dx)
		{
			err += dx;
			//cprintf("y0: %d sy: %d y0+=sy: %d\n", y0, sy, y0 + sy);
			y0 += sy;
		}
	}
	//cprintf("x0: %d x1: %d y0: %d y1 %d\n", x0, x1, y0, y1);
	//uchar *lastPixel = P2V(0xA0000 + 320 * y0 + x0);
	//*lastPixel = col;

	return 0;
}

int sys_flushscreen(void)
{
	int col;

	if (argint(0, &col) < 0)
	{
		return -1;
	}
	memset(P2V(0xA0000), col, (320 * 200));
	return 0;
}

int sys_selectpenSys(void)
{
	int hdc;
	int col;
	int prevCol;
	if (argint(0, &hdc) < 0)
	{
		return -1;
	}
	if (argint(1, &col) < 0)
	{
		return -1;
	}
	prevCol = hdctable.devices[hdc].colourIndex;
	if (col < 0 || col > 255)
	{
		return -1;
	}
	else
	{
		hdctable.devices[hdc].colourIndex = col;
		return prevCol;
	}
	return 0;
}

int sys_setpencolourSys(void)
{
	int index;
	int r;
	int g;
	int b;

	if (argint(0, &index) < 0)
	{
		return -1;
	}
	if (argint(1, &r) < 0)
	{
		return -1;
	}
	if (argint(2, &g) < 0)
	{
		return -1;
	}
	if (argint(3, &b) < 0)
	{
		return -1;
	}
	// Clip values;
	if (index < 16)
	{
		index = 16;
	}
	else if (index > 255)
	{
		index = 255;
	}
	if (r > 63)
	{
		r = 63;
	}
	if (g > 63)
	{
		g = 63;
	}
	if (b > 63)
	{
		b = 63;
	}

	//Add colour to pallette
	outb(0x3C8, index);
	outb(0x3C9, r);
	outb(0x3C9, g);
	outb(0x3C9, b);
	return 0;
}

int sys_fillrectSys(void)
{
	int hdc;
	struct rect *rectangle;

	if (argint(0, &hdc) < 0)
	{
		return -1;
	}
	if (argptr(1, (void *)&rectangle, sizeof(*rectangle)) < 0)
	{
		return -1;
	}

	// checks that rectangle is valid
	if (rectangle->left > rectangle->right || rectangle->top > rectangle->bottom)
	{
		return -1;
	}
	if(rectangle->left < 0){
		rectangle->left = 0;
	}
	if(rectangle->right > 319){
		rectangle->right = 319;
	}
	if(rectangle->top < 0){
		rectangle->top = 0;
	}
	if(rectangle->bottom > 199){
		rectangle->bottom = 199;
	}

	int memOff = rectangle->right - rectangle->left;
	for (int i = rectangle->top; i < rectangle->bottom; i++)
	{
		memset(P2V(0xA0000 + 320 * i + rectangle->left), hdctable.devices[hdc].colourIndex, memOff);
	}

	return 0;
}

int sys_beginpaint(void){
	int hwnd;
	
	if(argint(0,&hwnd) < 0){
		return -1;
	}

	acquire(&hdctable.lock);
	int returnVal =  -1;
	for (int i = 0; i < 100; i++)
	{
		if(hdctable.devices[i].locked == 0){
			hdctable.devices[i].locked = 1;
			returnVal = i;
			break;
		}
	}
	release(&hdctable.lock);
	return returnVal;
}

int sys_endpaintSys(void){
	int hdc;
	
	if(argint(0,&hdc) < 0){
		return -1;
	}
	acquire(&hdctable.lock);
	devices[hdc].locked = 0;
	release(&hdctable.lock);
	return 0;
}

int sys_executedraw(void){
	return 0;
}