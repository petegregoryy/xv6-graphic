#include "types.h"
#include "defs.h"
#include "memlayout.h"
void clear320x200x256() {
	// You need to put code to clear the video buffer here.  Initially, 
	// you might just set each pixel to black in a nested loop, but think
	// about faster ways to do it. 
	//
	// This function is called from videosetmode.

	memset(P2V(0xA0000), 0, 112200);
}

