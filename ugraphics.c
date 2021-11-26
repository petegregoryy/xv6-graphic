#include "types.h"
#include "user.h"

struct command {
    int command;
    int hdc;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int arg7;
    int arg8;
    struct rect* rect;
};
struct commandHolder{
    struct command commands[100];
};

struct commandHolder commandHolder = {};

void moveto(int hdc, int x, int y){
    int commandint = getempty();
    printf(0,"Empty holder: %d\n",commandint);
    commandHolder.commands[commandint].command=1;
    commandHolder.commands[commandint].hdc = hdc;
    commandHolder.commands[commandint].arg1 = x;
    commandHolder.commands[commandint].arg2 = y;

    executedraw(hdc,&commandHolder);
    //movetoSys(hdc,x,y);
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