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
    int cmds;
    struct command commands[100];
};

struct commandHolder commandHolder = {};

int penCol = 0;

void moveto(int hdc, int x, int y){
    checkFull();
    int commandint = commandHolder.cmds;
    // printf(0,"Empty holder: %d\n",commandint);
    commandHolder.commands[commandint].command=1;
    commandHolder.commands[commandint].hdc = hdc;
    commandHolder.commands[commandint].arg1 = x;
    commandHolder.commands[commandint].arg2 = y;
    // printf(0, "Added moveto Instruction\n");
    commandHolder.cmds++;
}

void setpixel(int hdc, int x, int y){
    checkFull();
    int index = commandHolder.cmds;
    commandHolder.commands[index].command=2;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].arg1 = x;
    commandHolder.commands[index].arg2 = y;
    commandHolder.cmds++;
    // printf(0, "Added Setpixel Instruction\n");
    
}

void lineto(int hdc, int x, int y){
    checkFull();
    int index = commandHolder.cmds;
    commandHolder.commands[index].command=3;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].arg1 = x;
    commandHolder.commands[index].arg2 = y;
    commandHolder.cmds++;
    // printf(0, "Added lineto Instruction\n");
    
}
void fillrect(int hdc, struct rect* rect){
    checkFull();
    int index = commandHolder.cmds;
    commandHolder.commands[index].command=4;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].rect = rect;
    commandHolder.cmds++;
    // printf(0, "Added fillrect Instruction\n");
    
}

int selectpen(int hdc, int penIndex){
    checkFull();
    int index = commandHolder.cmds;
    int prevCol = penCol;
    penCol = prevCol;
    commandHolder.commands[index].command=5;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].arg1 = penIndex;
    commandHolder.cmds++;
    //printf(0, "Added selectpen Instruction\n");
    return penCol;
}

void endpaint(int hdc){
    execute();
}


void checkFull(){
    if(commandHolder.cmds >= 100){
        execute();
        commandHolder.cmds = 0;
    }
}

void execute(){
    //printf(0, "Number of Commands in Execute: %d\n",commandHolder.cmds);
    executedraw(&commandHolder);
}
