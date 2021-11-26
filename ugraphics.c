#include "types.h"
#include "user.h"


struct commandHolder commandHolder = {};

void moveto(int hdc, int x, int y){
    movetoSys(hdc,x,y);
}

void setpixel(int hdc, int x, int y){
    setpixelSys(hdc,x,y);
}

void lineto(int hdc, int x, int y){
    linetoSys(hdc,x,y);
}
void fillrect(int hdc, struct rect* rect){
    fillrectSys(hdc,rect);
}

void selectpen(int hdc, int index){
    selectpenSys(hdc,index);
}

void endpaint(int hdc){
    endpaintSys(hdc);
}

void setpencolour(int index,int r,int b, int g){
    setpencolourSys(index,r,g,b);
}

int getempty(){
    for (int i = 0; i < 100; i++)
    {
        if(commandHolder.commands[i].command == 0){
            return i;
        }
    }
    return -1;
}