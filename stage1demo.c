#include "types.h"
#include "user.h"
int main(int argc, char* argv[])
{
    setvideomode(0x13);
    int hdc = beginpaint(0);
    moveto(hdc, 100, 50);
    lineto(hdc, 200, 50);
    lineto(hdc, 200, 150);
    lineto(hdc, 100, 150);
    lineto(hdc, 100, 50);
    endpaint(hdc);
    getch();
    setvideomode(0x03);
    exit();
}