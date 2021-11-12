#include "types.h"
#include "user.h"

int main (int argc, char *argv[]){

    setvideomode(0x13);
    int colour = 1;
    for (int x = 0; x < 320; x++)
    {
        
        for (int y = 0; y < 200; y++)
        {
            setpixel(0, x, y,colour);           
        }
        colour++;
        if(colour == 60){
            colour = 1;
        }
    }
    
    /*
    setpixel(0, 100, 100);
    setpixel(0, 100, 102);
    setpixel(0, 102, 100);
    setpixel(0, 102, 102);
    */
    getch();
    setvideomode(0x03);
    exit();
}