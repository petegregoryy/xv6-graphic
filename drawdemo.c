#include "types.h"
#include "user.h"

int main (int argc, char *argv[]){

    setvideomode(0x13);
    setpixel(0, 100, 100);
    setpixel(0, 100, 102);
    setpixel(0, 102, 100);
    setpixel(0, 102, 102);
    getch();
    setvideomode(0x03);
    exit();
}