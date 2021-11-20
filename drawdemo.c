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
    int pid = fork();
    
    
    
    if(pid == 0){
        char *argv2[1];
        exec("forkpaint",argv2);
        exit();
    }
    if(pid > 0)
{
        printf(0,"Parent\n");
        int paint1 = beginpaint(0);
        int paint2 = beginpaint(0);
        //printf(0,"paint1: %d",paint1);

        //printf(0," paint2: %d\n",paint2);

        selectpen(paint1,14);
        selectpen(paint2,15);
        moveto(paint1,50,50);
        moveto(paint2,100,50);
        lineto(paint1,100,100);
        lineto(paint2,150,100);
        endpaint(paint1);
        endpaint(paint2);
    }
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