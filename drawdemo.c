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

    moveto(0, 10, 10);
    lineto(0, 10, 100);
    getch();
    setvideomode(0x03);
    exit();
}