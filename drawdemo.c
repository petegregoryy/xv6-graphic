#include "types.h"
#include "user.h"

struct rect
{
    int top;
    int left;
    int bottom;
    int right;
};

int main(int argc, char *argv[])
{
    /*int colour = 15;
    if (argc == 2)
    {
        colour = atoi(argv[1]);
    }
*/
    setvideomode(0x13);

    struct rect rectangle;
    rectangle.top = 10;
    rectangle.left = 10;
    rectangle.bottom = 100;
    rectangle.right = 150;

    struct rect *rectPtr;
    rectPtr = &rectangle;
    selectpen(0, 12);
    fillrect(0, rectPtr);
    selectpen(0, 15);
    moveto(0, 10, 10);
    lineto(0, 150, 100);

    getch();
    setvideomode(0x03);
    exit();
}