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

// MoveTo - Takes device context (hdc) x,y coordinates as arguments. The device's current pen location is set to the passed x,y.
void moveto(int hdc, int x, int y){
    checkFull();
    int commandint = commandHolder.cmds;
    commandHolder.commands[commandint].command=1;
    commandHolder.commands[commandint].hdc = hdc;
    commandHolder.commands[commandint].arg1 = x;
    commandHolder.commands[commandint].arg2 = y;
    commandHolder.cmds++;
}

// SetPixel - Takes device context (hdc) and pixel x,y as arguments. The pixel at the specified coordinate is changed to the current hdc pen colour.
void setpixel(int hdc, int x, int y){
    checkFull();
    int index = commandHolder.cmds;
    commandHolder.commands[index].command=2;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].arg1 = x;
    commandHolder.commands[index].arg2 = y;
    commandHolder.cmds++;
    
}

// LineTo - Takes device context (hdc) and target x,y as arguments. A line is drawn from the hdc current location to the target with the current hdc pen colour.
void lineto(int hdc, int x, int y){
    checkFull();
    int index = commandHolder.cmds;
    commandHolder.commands[index].command=3;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].arg1 = x;
    commandHolder.commands[index].arg2 = y;
    commandHolder.cmds++;
    
}

// FillRect - Takes device context (hdc) and a rectangle object. The rectange is drawn with the current hdc pen colour.
void fillrect(int hdc, struct rect* rect){
    checkFull();
    int index = commandHolder.cmds;
    commandHolder.commands[index].command=4;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].rect = rect;
    commandHolder.cmds++;
    
}

// SelectPen - Takes device context (hdc) and a pen index as arguments. The device's pen is then set to the value of the pen index.
int selectpen(int hdc, int penIndex){
    checkFull();
    int index = commandHolder.cmds;
    
    // Saves previous colour of pen, allows for returning of pen colour as specified.
    int prevCol = penCol;
    
    // Push command into the command buffer.
    commandHolder.commands[index].command=5;
    commandHolder.commands[index].hdc= hdc;
    commandHolder.commands[index].arg1 = penIndex;
    commandHolder.cmds++;
    return prevCol;
}

// EndPaint - Takes device contex (hdc) as argument. Releases device context and calls execute on buffered commands.
void endpaint(int hdc){
    execute();
}

// Checks whether the command holder is full, if so it gets executed and flushed to be filled again.
void checkFull(){
    if(commandHolder.cmds >= 100){
        execute();
        commandHolder.cmds = 0;
    }
}

// Allows for execution when command holder is full. If system call was contained in endpaint then execution could only happen when
// endpaint was called, so if the command holder filled up then it would only draw the first 100 instructions.
void execute(){
    executedraw(&commandHolder);
}
