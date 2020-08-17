#include "prototype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    set alias in file
*/
void alias_set(char *name, char *command)
{
    FILE *fp;
    char *inp ;

    // filename for storing aliases
    char *filename = strcat(getenv("HOME"), "/.mish_alias");

    // open file for storing aliases
    fp = fopen(filename, "a+");

    // check if file opens with success
    if(fp != NULL)
    {
        sprintf(inp, "%s \t %s ", name, command);
        fputs(inp, fp);
    }

}

/*
    check if is alias is created
*/
char *alias_check(char *input){
    FILE *fp;
    char c;
    char *text;
    char *name;
    char *command;
    int i=0;
    fp = fopen("~/.mish_alias", "r");
    if(fp == NULL) {
        perror("Error in opening file");
    } do {
        c = fgetc(fp);
        if( feof(fp) ) {
            break ;
        }
        text[i] = c;
        i++;
    } while(1);
    i = 0;
    char line = strtok(text, "\n");
    while (line != NULL)
    {
        char *token = strtok(line, "\t");
        while(token != NULL){
            if(i == 0){
                name = token;
            }else if(i == 1){
                command = token;
            }
            else{
                break;
            }
            token = strtok(NULL, "\t");
        }
        if(! strcmp(input, name))
            return command;
        else {
            continue;
        } 
    }
    return input;

}