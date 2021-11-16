#include "types.h"
#include "user.h"

int main (int argc, char *argv[]){
    int colour = 15;
    if (argc == 2)
    {
        colour = atoi(argv[1]);
    }

    setvideomode(0x13);

    for (int y = 0; y < 200; y++)
    {
        for (int x = 0; x < 320; x++)
        { 
            setpixel(0, x, y,colour);
        }
    }
    getch();
    setvideomode(0x03);
    exit();
}