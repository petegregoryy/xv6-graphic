#include "types.h"
#include "user.h"

int main (int argc, char *argv[]){
    if(argc == 1){
        printf(1, "Shutting down...\n");
        shutdown(0);
    }
    if(argc == 2){
        printf(1, "Rebooting...\n");
        shutdown(1);
    }

    exit();
}