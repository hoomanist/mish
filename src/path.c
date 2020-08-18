#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "prototype.h"


char *get_path(char *command){
    char *path_string = getenv("PATH");
    char **path_array = malloc(64*sizeof(char) * sizeof(char));
    int i;
    char *token = strtok(path_string, ":");
    while(token != NULL){
        path_array[i] = token;
        i++;
        char *token = strtok(NULL, ":");

    }
    for(int j; j <= i; j++){
        if( access( strcat(path_array[j], command), F_OK ) != -1 ) {
            return(strcat(path_array[j], command));
        }else{
            continue;
        }
    }
    printf("command not found");
    
}