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


/* split a command into tokens
*/
char **split(char *line) {

  // split input by newline
  line = strtok(line, "\n");
  int buff = BUFFER;

  // tokens will be stored here
  char **tokens = malloc(buff * sizeof(char*));
  char *token;

  if (tokens == NULL) {
    printf("mish: allocation error\n");
    exit(1);
  }

  // token index counter
  int i = 0;

  // split line by whitespace
  token = strtok(line, " "); 
  while (token != NULL) { 
      tokens[i] = token;
      i++;
      token = strtok(NULL, " ");

  } 
  tokens[i] = NULL;

  return tokens;
}

/* execute a command.
command is a string array with each argument in a seperate element.
*/
void command(char **arguments){

  // check if command is not empty
  if(arguments[0])
  {

    // if command was 'cd', working directory should be changed.
    if(! strcmp(arguments[0], "cd")){

      // if command has got no arguments,
      // working directory should be changed to user home.
      if(!arguments[1] || strcmp(arguments[1], "~") == 0){

        // get directory string of user's home
        // and change working directory there.
        chdir(getenv("HOME"));

      // but if it has an argument,
      }else{

        // change working directory.
        if(chdir(arguments[1])){

          // if address were given wrong
          if(errno == 2){
            printf("directory not found \n");
          }
        }
      }
    }

    // if command is 'exit' shell should be terminated.
    else if(! strcmp(arguments[0], "exit")){

      // terminate the shell
      exit(0);
    }

    // if command is 'clear', screen should be cleared.
    else if(! strcmp(arguments[0], "clear")){

      // clear the terminal
      printf("\033[2J\033[1;1H");
    }
  }
  else if(! strcmp(arguments[0], "help")){
    printf("Minimalistic shell \n");

  }
}

/* get a command from stdin and parse/execute it
*/
void prompt() {

  char input[CHAR_MAX];
  char identify[4];
  char **arguments;
  char cwd[CHAR_MAX];

  // get working directory
  // also check for errors
  if (!(getcwd(cwd, sizeof(cwd)) != NULL)) {
    perror("getcwd() error");
  }

  // get user ID
  uid_t user = getuid();

  // if user was logged in as root, show a '#' sign.
  if (user == 0) {
    strcpy(identify, "#");

  // if user was logged in as normal user, show a '$' sign.
  } else {
    strcpy(identify, "$");
  }

  // print out begining of command line
  printf("[%s]%s ", cwd, identify);

  // get user command from stdin
  fgets(input, sizeof(input), stdin);

  // split command arguments
  arguments = split(input);

  // execute the command
  command(arguments);

  free(arguments);
}

/*
  start of program.
*/
int main(int argc, char *argv[]) {

  // hello message of the shell goes here
  printf("welcome to minimalistic shell ! \n");

  // start getting commands
  for(;;){
    prompt();
  }

  return 0;
}
