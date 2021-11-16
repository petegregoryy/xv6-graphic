#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    /*int colour = 15;
    if (argc == 2)
    {
        colour = atoi(argv[1]);
    }
*/
    setvideomode(0x13);

    moveto(0, 100, 50);
    for (int i = 0; i < 100; i += 3)
    {
        moveto(0, 25 + i, 10 + i);
        lineto(0, 125 + i, 10 + i, 15);
        lineto(0, 125 + i, 110 + i, 15);
        lineto(0, 25 + i, 110 + i, 15);
        lineto(0, 25 + i, 10 + i, 15);
    }

    getch();
    setvideomode(0x03);
    exit();
}