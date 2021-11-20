#include "types.h"
#include "user.h"
#include "funcs.h"

struct rect
{
    int top;
    int left;
    int bottom;
    int right;
};

int main(int argc, char *argv[])
{
    
    setvideomode(0x13);
    int hdc = beginpaint(0);
    printf(0,"paint1: %d",hdc);
    int colour = 16;
    int rCol = 0;
    int gCol = 0;
    int bCol = 0;
    for (int x = 0; x < 320; x+=4)
    {   
        bCol++;
        for (int y = 0; y < 200; y+=4)
        {
            rCol++;
            setpencolour(colour,rCol,gCol,bCol);
            selectpen(hdc,colour);
            fillrect(hdc, CreateRect(y,x,2+y,2+x));
            colour++;
            if(colour > 255){
                colour = 16;

                rCol = 0;
            }
            if(rCol > 63){

                rCol = 0;
                gCol+=2;
            }
            if(gCol > 63){
                gCol = 0;
            }
            if(bCol > 63){
                bCol = 0;
            }
            sleep(1);
        }        
    }    
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