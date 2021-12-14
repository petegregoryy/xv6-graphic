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
    struct rect* rect;
};

struct commandHolder{
	int cmds;
    struct command commands[100];
};

struct hdctable hdctable = {};



void clear320x200x256()
{
	memset(P2V(0xA0000), 0, (320 * 200));
}

void clear640x400x16(){
	for (int i = 0; i < 4; i++)
	{
		setplane(i);
		memset(getframebufferbase(),0,((640*480)/8));	
	}	
}

void graphicsinit(void){
	initlock(&hdctable.lock,"hdctable");
	for (int i = 0; i < 100; i++)
	{
		hdctable.devices[i].colourIndex = 15;
	}
}

// Global Variables

struct hdc devices[10];

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

int sys_setpencolour(void)
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
	acquire(&hdctable.lock);
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
	release(&hdctable.lock);
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


int sys_executedraw(void){
	struct commandHolder *cmdh;
	
	if (argptr(0, (void *)&cmdh, sizeof(*cmdh)) < 0)
	{
		return -1;
	}
	//cprintf("Number of commands in kernel: %d\n",cmdh->cmds);
	for (int i = 0; i < cmdh->cmds; i++)
	{
		int hdc = cmdh->commands[i].hdc;

		// MoveTo
		if(cmdh->commands[i].command == 1){
			int x = cmdh->commands[i].arg1;
			int y = cmdh->commands[i].arg2;
			

			hdctable.devices[hdc].moveX = x;
			hdctable.devices[hdc].moveY = y;
		}
		// SetPixel
		else if(cmdh->commands[i].command == 2){
			int x = cmdh->commands[i].arg1;
			int y = cmdh->commands[i].arg2;


			if(getcurrentvideomode() == 0x12){
				int index = 640*y+x;
					int planeByteIndex = index / 8;
					int planeBitIndex = index % 8;

					// convert 2d coordinates into 1d index
					// divide by 8 to get real offset
					// modulo by 8 to get the individual bit offset

					int shiftedBit = 1 << planeBitIndex;

					cprintf("X: %d Y: %d\n",x,y);
					for (int i = 0; i < 4; i++)
					{
						setplane(i);
						cprintf("Plane %d\n",i);
						uchar *pixel = getframebufferbase() + planeByteIndex;
						//uchar pixelByte = *pixel;
						cprintf("pixel val: %d ",*pixel);
						printbinary(*pixel);
						*pixel = *pixel | shiftedBit;
						cprintf("shifted: %d ",shiftedBit);
						printbinary(shiftedBit);
						cprintf("OR'd val: %d ",*pixel);
						printbinary(*pixel);
						
					}
					cprintf("\n");
			}
			else if(getcurrentvideomode() == 0x13){
				uchar *pixel = P2V(0xA0000 + 320 * y + x);
				*pixel = hdctable.devices[hdc].colourIndex;
			}
		}
		// LineTo
		else if(cmdh->commands[i].command == 3){
			int x1 = cmdh->commands[i].arg1;
			int y1 = cmdh->commands[i].arg2;

			int dx, dy;
			int sx, sy;
			int err;
			int e2;

			int x0 = hdctable.devices[hdc].moveX;
			int y0 = hdctable.devices[hdc].moveY;

			// Clip values to screen bounds
			if(getcurrentvideomode() == 0x13){
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
			}
			else if(getcurrentvideomode() == 0x12){
				if (x1 > 639)
				{
					x1 = 639;
				}
				else if (x1 < 0)
				{
					x1 = 0;
				}
				if (y1 > 479)
				{
					y1 = 479;
				}
				else if (y1 < 0)
				{
					y1 = 0;
				}
			}

			hdctable.devices[hdc].moveX = x1;
			hdctable.devices[hdc].moveY = y1;

			dx = abs(x1 - x0);
			sx = x0 < x1 ? 1 : -1;
			dy = -abs(y1 - y0);
			sy = y0 < y1 ? 1 : -1;

			err = dx + dy;

			while (x0 != x1 || y0 != y1)
			{
				if(getcurrentvideomode() == 0x12){
					
					
					int index = 640*y0+x0;
					int planeByteIndex = index / 8;
					int planeBitIndex = index % 8;

					// convert 2d coordinates into 1d index
					// divide by 8 to get real offset
					// modulo by 8 to get the individual bit offset

					int shiftedBit = 1 << planeBitIndex;

					cprintf("X: %d Y: %d\n",x0,y0);
					for (int i = 0; i < 4; i++)
					{
						setplane(i);
						cprintf("Plane %d\n",i);
						uchar *pixel = getframebufferbase() + planeByteIndex;
						//uchar pixelByte = *pixel;
						cprintf("pixel val: %d ",*pixel);
						printbinary(*pixel);
						*pixel = *pixel | shiftedBit;
						cprintf("shifted: %d ",shiftedBit);
						printbinary(shiftedBit);
						cprintf("OR'd val: %d ",*pixel);
						printbinary(*pixel);
						
					}
					cprintf("\n");
					
					
					
				}
				else if(getcurrentvideomode() == 0x13){
					uchar *pixel = P2V(0xA0000 + 320 * y0 + x0);
					*pixel = hdctable.devices[hdc].colourIndex;
				}
				e2 = 2 * err;

				if (e2 >= dy)
				{
					err += dy;
					x0 += sx;
				}
				
				if (e2 <= dx)
				{
					err += dx;
					y0 += sy;
				}
			}

		}
		// FillRect
		else if(cmdh->commands[i].command == 4){
			struct rect *rectangle = cmdh->commands[i].rect;

			// checks that rectangle is valid
			if (rectangle->left > rectangle->right || rectangle->top > rectangle->bottom)
			{
				cprintf("Invalid Rect!");
			}
			else{
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
			}
			 
		}
		// SelectPen
		else if(cmdh->commands[i].command == 5){
			int col = cmdh->commands[i].arg1;

			if (col < 0 || col > 255)
			{
				//return -1;
				col = 1;
			}
			else
			{
				hdctable.devices[hdc].colourIndex = col;
			}
		}
	}
	
	
	return 0;
}

void printbinary(int n){
	while (n) {
		if (n & 1)
			cprintf("1");
		else
			cprintf("0");

		n >>= 1;
	}
	cprintf("\n");
}