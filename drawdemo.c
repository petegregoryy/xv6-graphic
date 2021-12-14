#include "types.h"
#include "user.h"
#include "funcs.h"

struct rect
{
    int top;
    int left;
    int bottom;
    int right;
};

int main(int argc, char *argv[])
{
    //int ppid = getpid();
    setvideomode(0x12);
    int hdc = beginpaint(0);
    setpixel(hdc, 200,100);
    moveto(hdc,200,100);
    lineto(hdc,400,400);
    setpixel(hdc, 248,250);
    setpixel(hdc, 250,250);
    setpixel(hdc, 252,250);
    setpixel(hdc, 254,250);

    setpixel(hdc, 256,250);
    setpixel(hdc, 258,250);
    setpixel(hdc, 260,250);
    endpaint(hdc);
    getch();
    setvideomode(0x13);
    hdc = beginpaint(0);
    setpixel(hdc, 200,100);
    moveto(hdc,200,100);
    lineto(hdc,400,400);
    endpaint(hdc);
    getch();
    setvideomode(0x03);
    
    exit();
    
}

// Made for ease of rectangle creation
struct rect *CreateRect(int top, int left, int bottom, int right)
{
    struct rect *rectangle = malloc(sizeof(struct rect));
    rectangle->top = top;
    rectangle->left = left;
    rectangle->bottom = bottom;
    rectangle->right = right;
    return rectangle;
}