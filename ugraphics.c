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

    //pushToArray(commandint,&commandHolder);
    //movetoSys(hdc,x,y);
}

void setpixel(int hdc, int x, int y){
    int index = getempty();
    commandHolder.commands[index].command=2;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].arg1 = x;
    commandHolder.commands[index].arg2 = y;

    //pushToArray(index,&commandHolder);
    //setpixelSys(hdc,x,y);
}

void lineto(int hdc, int x, int y){
    int index = getempty();
    commandHolder.commands[index].command=3;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].arg1 = x;
    commandHolder.commands[index].arg2 = y;

    //pushToArray(index,&commandHolder);
    //linetoSys(hdc,x,y);
}
void fillrect(int hdc, struct rect* rect){
    int index = getempty();
    commandHolder.commands[index].command=4;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].rect = rect;

    //pushToArray(index,&commandHolder);
    //fillrectSys(hdc,rect);
}

void selectpen(int hdc, int penIndex){
    int index = getempty();
    commandHolder.commands[index].command=5;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].arg1 = penIndex;

    //pushToArray(index,&commandHolder);
    //selectpenSys(hdc,index);
}

void endpaint(int hdc){
    execute();
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

// int pushToArray(int index, struct command* cmd){
//     commandHolder.commands[index] = *cmd;
//     return 0;
// }

void execute(){
    executedraw(&commandHolder);
}
