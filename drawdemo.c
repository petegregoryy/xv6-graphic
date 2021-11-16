#include "types.h"
#include "user.h"

int main (int argc, char *argv[]){
    /*int colour = 15;
    if (argc == 2)
    {
        colour = atoi(argv[1]);
    }
*/
    setvideomode(0x13);

    moveto(0, 0, 0);
    lineto(0, 150, 30);
    lineto(0, 200, 50);
    moveto(0, 300, 190);
    lineto(0, 10, 175);
    getch();
    setvideomode(0x03);
    exit();
}