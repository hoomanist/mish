#include "prototype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*
    set alias in file
*/
void alias_set(char *name, char *command)
{
    FILE *fp;
    char inp[CHAR_MAX] ;
    // filename for storing aliases
    char *filename = strcat(getenv("HOME"), "/.mish_alias");
    // open file for storing aliases
    fp = fopen(filename, "a+");

    // check if file opens with success
    if(fp != NULL)
    {
        sprintf(inp, "%s=%s\n ", name, command);
        fputs(inp, fp);
        fclose(fp);
    }

}


/*
    check if is alias is created
*/
char *alias_check(char *input){
    
    FILE *fp;
    char c;
    char *name;
    char *command;

    // filename for storing aliases
    char *filename = strcat(getenv("HOME"), "/.mish_alias");

    // open the file storig aliases
    fp = fopen(filename, "r");
    
    if(fp == NULL) {
        perror("Error in opening file");
        return input;
    }


    // get file size
    fseek(fp, 0, SEEK_END);
    long int textSize = ftell(fp);

    // close the file and reopen it to start from begining
    fclose(fp);
    fp = fopen(filename, "r");

    // file text will be stored in this string.
    // so allocate enough bytes for it.
    char* text = malloc(textSize*sizeof(char));

    int i=0;
    do {
        c = fgetc(fp);
        if( feof(fp) ) {
            break ;
        }
        text[i] = c;
        i++;
    } while(1);

    fclose(fp);


    i = 0;

    // seprate it by \n
    char* line = strtok(text, "\n");

    char* rest = text;

    while (line != NULL)
    {

    line = strtok_r(rest, "\n", &rest);

        // seprate by tabs
        char *token = strtok(line, "=");
        while(token != NULL){
            if(i == 0){
                // assigning name
                name = token;
            }else if(i == 1){
                // command ti run
                command = token;
            }
            else{
                break;
            }
            token = strtok(NULL, "=");
        }
        // check if it is alias
        if(! strcmp(input, name))
            return command;
        else {
            continue;
        } 
    }
    // if it is not alias
    return input;

}