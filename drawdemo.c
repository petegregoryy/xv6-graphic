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
    int startx = 0;
    int starty = 0;
    int endOffx = 20;
    int endOffy = 200;
    int colour = 1;

    moveto(0, 0, 0);
    while (!getch())
    {
        for (int i = 0; i < 16; i++)
        {
            moveto(0, startx, starty);
            lineto(0, endOffx, endOffy, colour);
            endOffx += 20;
            colour++;
            sleep(2);
            flushscreen(0);
        }
        for (int i = 16; i > 0; i--)
        {
            moveto(0, startx, starty);
            lineto(0, endOffx, endOffy, colour);
            endOffx -= 20;
            colour--;
            sleep(2);
            flushscreen(0);
        }
    }
    //getch();
    setvideomode(0x03);
    exit();
}