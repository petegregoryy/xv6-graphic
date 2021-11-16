#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
    int x;
    int y;
    //int sX;
    //int sY;
    //int dx, dy, p, x, y;

    if(argint(0,&hdc) < 0){
        return -1;
    }
    if(argint(1,&x) < 0){
        return -1;
    }
    if(argint(2,&y) < 0){
        return -1;
    }


  /*
    dx = x1 - x0;
    dy = y1 - y0;
    x = x0;
    y = y0;
    p = 2 * dy - dx;
    while(x < x1) {
        if(p >= 0) {
            setPixel(x, y, col);
            y++;
            p = p + 2 * dy - 2 * dx;
        } else {
            setPixel(x, y, col);
            p = p + 2 * dy;
            x++;
        }
    }*/
    
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