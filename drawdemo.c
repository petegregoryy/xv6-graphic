#include "types.h"
#include "user.h"

int main (int argc, char *argv[]){
    //int colour = 15;
    if (argc == 2)
    {
        ///colour = atoi(argv[1]);
    }

    setvideomode(0x13);

    moveto(0, 100, 50);
    lineto(0, 150, 75);

    /*for (int x = 0; x < 320; x++)
    {
        
        for (int y = 0; y < 200; y++)
        {
            setpixel(0, x, y,colour);
        }
    }*/
    getch();
    setvideomode(0x03);
    exit();
}