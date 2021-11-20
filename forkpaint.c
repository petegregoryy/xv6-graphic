#include "types.h"
#include "user.h"
#include "funcs.h"

int main(int argc, char const *argv[])
{
    printf(0,"CHILD\n");
    int paint1 = beginpaint(0);
    int paint2 = beginpaint(0);
        //printf(0,"paint1: %d",paint1);

        //printf(0," paint2: %d\n",paint2);

    selectpen(paint1,7);
    selectpen(paint2,10);
    moveto(paint1,50-10,50);
    moveto(paint2,100-10,50);
    lineto(paint1,100-10,100);
    lineto(paint2,150-10,100);
    endpaint(paint1);
    endpaint(paint2);
    exit();
    
}
