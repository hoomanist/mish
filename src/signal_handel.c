#include <stdio.h>
#include "prototype.h"

void  sigint_handel(void){
    printf("press ctrl-d to quit\n");
}
void sigquit_handel(void){
    printf("goodbye mate\n");
    exit(0);
}