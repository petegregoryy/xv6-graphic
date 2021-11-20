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
    
    setvideomode(0x13);
    
    printf(0,"paint1: %d",0);
    printf(0," paint2: %d\n",1);
    moveto(0,50,50);
    moveto(1,100,50);
    lineto(0,100,100);
    lineto(1,150,100);
    endpaint(0);
    endpaint(1);
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