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
    setpencolour(17, 62, 30, 62);
    for (int i = 0; i < 100; i += 3)
    {
        moveto(0, 25 + i, 10 + i);
        selectpen(0, 17);
        lineto(0, 125 + i, 10 + i);
        //selectpen(0, 14);
        lineto(0, 125 + i, 110 + i);
        //selectpen(0, 13);
        lineto(0, 25 + i, 110 + i);
        //selectpen(0, 12);
        lineto(0, 25 + i, 10 + i);
    }

    getch();
    setvideomode(0x03);
    exit();
}