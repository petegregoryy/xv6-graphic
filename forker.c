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

int
main(int argc, char *argv[])
{
    int pid = fork();

    if(pid == 0){
    // child
        char *argv[2];
        argv[0] = "echo";
        argv[1] = "CHILD";
        exec("echo", argv);
        exit();
        
        
    }
    if(pid > 0) {
        wait();

        printf(0,"parent");
    }   
    else {
        printf(0,"ERROR");

    }   
    exit();
}
