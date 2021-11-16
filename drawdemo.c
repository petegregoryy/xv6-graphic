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

    struct rect *rectangle = CreateStruct(10, 10, 50, 50);

    selectpen(0, 12);
    moveto(0, 10, 10);
    fillrect(0, rectangle);
    selectpen(0, 15);
    lineto(0, 50, 50);

    getch();
    setvideomode(0x03);
    exit();
}

// Made for ease of rectangle creation
struct rect *CreateStruct(int top, int left, int bottom, int right)
{
    struct rect *rectangle = malloc(sizeof(struct rect));
    rectangle->top = top;
    rectangle->left = left;
    rectangle->bottom = bottom;
    rectangle->right = right;
    return rectangle;
}