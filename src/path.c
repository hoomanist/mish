#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "prototype.h"


char *get_path(char *command){
    // get env var 
    char *path_string = getenv("PATH");
    char **path_array = malloc(64*sizeof(char) * sizeof(char));
    int i;
    // convert env var's string to an array
    char *token = strtok(path_string, ":");
    while(token != NULL){
        path_array[i] = token;
        i++;
        char *token = strtok(NULL, ":");

    }

    // check the file existence in each of path entry's
    for(int j; j <= i; j++){
        if( access( strcat(path_array[j], command), F_OK ) != -1 ) {
            // return true binary realpath
            return(strcat(path_array[j], command));
        }else{
            // continue the loop
            continue;
        }
    }
    // if it is not there
    perror("2");
}