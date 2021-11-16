#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "funcs.h"

int sys_fork(void) {
    return fork();
}

int sys_exit(void) {
    exit();
    return 0;  // not reached
}

int sys_wait(void) {
    return wait();
}

int sys_kill(void) {
    int pid;

    if (argint(0, &pid) < 0) {
        return -1;
    }
    return kill(pid);
}

int sys_getpid(void) {
    return myproc()->pid;
}

int sys_sbrk(void) {
    int addr;
    int n;

    if (argint(0, &n) < 0) {
        return -1;
    }
    addr = myproc()->sz;
    if (growproc(n) < 0) {
        return -1;
    }
    return addr;
}

int sys_sleep(void) {
    int n;
    uint ticks0;

    if (argint(0, &n) < 0) {
        return -1;
    }
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n) {
        if (myproc()->killed) {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

// My Added Commands!

int sys_shutdown(void){
    int n;

    if(argint(0,&n) < 0){
        return -1;
    }

    if(n == 0){
        outw(0x604, 0x2000);
        return 0;
    }
    if(n == 1){
        unsigned char good = 0x02;
        while (good & 0x02) {
        good = inb(0x64);
        }
        outb(0x64, 0xFE);
        return 0;
    }
    return 0;
}

int sys_setpixel(void){
    int hdc;
    int x;
    int y;
    int col;

    if(argint(0,&hdc) < 0){
        return -1;
    }
    if(argint(1,&x) < 0){
        return -1;
    }
    if(argint(2,&y) < 0){
        return -1;
    }
    if(argint(3,&col) < 0){
        return -1;
    }

    uchar *pixel = P2V(0xA0000 + 320 * y + x);
    *pixel = col;
    return 0;
}

int moveX = 0;
int moveY = 0;

int sys_moveto(void){
    int hdc;
    int x;
    int y;

    if (argint(0, &hdc) < 0)
    {
        return -1;
    }
    if(argint(1,&x) < 0){
        return -1;
    }
    if(argint(2,&y) < 0){
        return -1;
    }

    moveX = x;
    moveY = y;
    return 0;
}

int sys_lineto(void){
    int hdc;
    int x0 = moveX;
    int y0 = moveY;
    int x1, y1;
    int dx, dy;
    int sx, sy;
    int err;
    int e2;

    cprintf("Move X = %d\n", x0);
    cprintf("Move Y = %d\n", y0);

    if(argint(0,&hdc) < 0){
        return -1;
    }
    if(argint(1,&x1) < 0){
        return -1;
    }
    if(argint(2,&y1) < 0){
        return -1;
    }
    moveX = x1;
    moveY = y1;

    cprintf("Target X = %d\n", x1);
    cprintf("Target Y = %d\n", y1);

    dx = abs(x1 - x0);
    sx = x0 < x1 ? 1 : -1;
    dy = -abs(y1 - y0);
    sy = y0 < y1 ? 1 : -1;

    cprintf("dx: %d\n", dx);
    cprintf("sx: %d\n", sx);
    cprintf("dy: %d\n", dy);
    cprintf("sy: %d\n", sy);
    
    err = dx + dy;
    
    

    while(x0 != x1 && y0 != y1){
        uchar *pixel = P2V(0xA0000 + 320 * y0 + x0);
        *pixel = 15;
        e2 = 2 * err;
        if(e2 >= dy){
            err += dy;
            //cprintf("x0: %d sx: %d x0+=sx: %d\n", x0, sx,x0+sx); /// Comments used in debugging!
            x0 += sx;
        }
        if(e2 <= dx){
            err += dx;
            //cprintf("y0: %d sy: %d y0+=sy: %d\n", y0, sy,y0+sy);
            y0 += sy;
        }
    }
    uchar *lastPixel = P2V(0xA0000 + 320 * y0 + x0);
    *lastPixel = 15;

    return 0;
}

int sys_flushscreen(void){
    int col;

    if(argint(0,&col) < 0){
        return -1;
    }
    memset(P2V(0xA0000), col, (320*200));
    return 0;
}