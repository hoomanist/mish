/*
 * minimalistic shell
 * lisenced under bsd clause 2
 *
 *
 * */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER 64



char **split(char *line) {
  line = strtok(line, "\n");
  int buff = BUFFER;
  char **tokens = malloc(buff * sizeof(char*));
  char *token;
  if (tokens == NULL) {
    printf("mish: allocation error\n");
    exit(1);
  }
  int i = 0;
  token = strtok(line, " "); 
  while (token != NULL) { 
      tokens[i] = token;
      i++;
      token = strtok(NULL, " ");

  } 
  tokens[i] = NULL;
  return tokens;
}

void command(char **arguments){
  if(arguments[1])
  {
    if(! strcmp(arguments[0], "cd")){
      
      if(arguments[1] == NULL ){
        printf("general kenobi");
        chdir("~");
      }else{
        if(chdir(arguments[1])){
          if(errno == 2){
            printf("directory not found \n");
          }
        }
      }
    }
  }
  else if(! strcmp(arguments[0], "exit")){
    exit(0);
  }
  else if(! strcmp(arguments[0], "clear")){
    printf("\033[2J\033[1;1H");
  }
  else if(! strcmp(arguments[0], "help")){
    printf("Minimalistic shell \n");

  }
}
void prompt() {
  char input[CHAR_MAX];
  char identify[4];
  char **arguments;
  char cwd[CHAR_MAX];
  if (!(getcwd(cwd, sizeof(cwd)) != NULL)) {
    perror("getcwd() error");
  }
  uid_t user = getuid();
  if (user == 0) {
    strcpy(identify, "#");
  } else {
    strcpy(identify, "$");
  }
  printf("[%s]%s ", cwd, identify);
  fgets(input, sizeof(input), stdin);
  arguments = split(input);
  command(arguments);
  free(arguments);
}

int main(int argc, char *argv[]) {
  printf("welcome to minimalistic shell ! \n");
  for(;;){
    prompt();
  }
}
