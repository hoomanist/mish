#include <stdio.h>
#include "prototype.h"

// ctrl-c must not work in a shell 
void  sigint_handel(void){
    printf("press ctrl-d to quit\n");
}
// ctrl-d must be used for exiting
void sigquit_handel(void){
    printf("goodbye mate\n");
    exit(0);
}