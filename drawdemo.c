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
    setvideomode(0x13);
    int hdc = beginpaint(0);
    selectpen(hdc,12);
    moveto(hdc,10,10);
    fillrect(hdc,CreateRect(50,50,150,150));
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