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

    moveto(0, 25, 25);

    getch();
    setvideomode(0x03);
    exit();
}