#include "types.h"
#include "user.h"
#include "funcs.h"
#include "memlayout.h"

struct rect
{
    int top;
    int left;
    int bottom;
    int right;
};

int main(int argc, char const *argv[])
{
    setvideomode(0x13);
    int hdc = beginpaint(0);
    int colourVal = 0;
    for (int i = 0; i < 240; i++)
    {
        if(colourVal>=63){
            colourVal = 0;
        }
        if(i<=63){
            setpencolour(i+16,colourVal,0,0);
            
        }
        else if(i<126){
            setpencolour(i+16,0,colourVal,0);
        }
        else if(i<189){
            setpencolour(i+16,0,0,colourVal);
        }
        else{
            setpencolour(i+16,colourVal,colourVal,colourVal);   
        }
        colourVal++;
        
        
    }
    for (int i = 0; i < 200; i++)
    {
        selectpen(hdc,i+16);
        fillrect(hdc,CreateRect(i,0,i+1,320));
    }
    selectpen(hdc,14);
    fillrect(hdc,CreateRect(50,100,150,200));
    endpaint(hdc);
    getch();
    setvideomode(0x03);
    exit();
}

// Made for ease of rectangle creation
struct rect *CreateRect(int top, int left, int bottom, int right)
{
    struct rect *rectangle = malloc(sizeof(struct rect));
    rectangle->top = top;
    rectangle->left = left;
    rectangle->bottom = bottom;
    rectangle->right = right;
    return rectangle;
}
