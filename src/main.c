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
#include <setjmp.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "built_in.h"

#define BUILTINS_SIZE 4
#define DELIM " \t\n\r"
long ARG_MAX;
static jmp_buf jmpbf;


struct bi {
  char *name;
  int (*func_ptr)(void *arg);
};

struct bi builtins [BUILTINS_SIZE]={
  {"cd", mish_cd},
  {"pwd", mish_pwd},
  {"exit", mish_exit},
  {"echo", mish_echo}
};

/*do at startup*/
void init(){
      putenv("PATH=/bin:/usr/bin:/usr/local/bin");
}

void sigint_handler(int signum) {
  printf("\n");
  siglongjmp(jmpbf, 1); 
}

char **split(char *line, int *counter) {
  int j;
  char **tokens; 
  char *token;
  
  tokens = malloc(ARG_MAX * sizeof(char *));
  if(tokens == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  j = 0;
  token = strtok(line, DELIM);
  while(token != NULL) {
    token[strlen(token)] = '\0'; /*not sure about this*/
    tokens[j] = strdup(token); /*these should be freed*/
    token = strtok(NULL, DELIM);
    j++;
  }
  tokens[j] = NULL;
  *counter = j; /*so we know how many buffers to free*/
  return tokens;
}

int spawn(char **argv) {
  int status;
  /*check if the command is built_in*/
  
  for(int i = 0; i < BUILTINS_SIZE; i++) {
    if(strcmp(argv[0], builtins[i].name) == 0) {
      builtins[i].func_ptr(argv[1]);
      return 0; 
    }
  }
  /*not reachable if the command was builtin*/
  switch(fork()) {
    case -1: perror("fork"); return -1;
    case 0:
        execvp(argv[0], argv);
        perror("execvp");
        _exit(EXIT_FAILURE);
    default:
      wait(&status); /*TODO: set $? to the status*/
  }
  return status;
}

void prompt() {

  char *input;
  char identify;
  char **arguments;
  char cwd[PATH_MAX];
  int counter;
  char prompt[PATH_MAX + 5];
  
  identify = (getuid() == 0)?'#':'$';
  
  if (!(getcwd(cwd, sizeof(cwd)) != NULL)) {
    perror("getcwd() error");
  }

  snprintf(prompt, sizeof(cwd) + sizeof(identify) + 4, "[%s]%c ", cwd, identify);
  input = readline(prompt);
  if(input == 0x0) { /* ctrl-d, when ctrl-d is pressed, EOF(0x0) is returned, so we shouldn't let it go further than here.*/
    printf("\nGoodBye :D\n");
    mish_exit(NULL);
  }
  if(strcmp(input, "") == 0) {
    free(input);
    longjmp(jmpbf, 1);
  }

  add_history(input);
  arguments = split(input, &counter);
  spawn(arguments);
  
  for(int i = 0; i < counter; i++) {
    free(arguments[i]);
  }
  free(arguments);
  free(input);
}
/*
  start of program.
*/
int main(int argc, char *argv[]) {
  ARG_MAX = sysconf(ARG_MAX);
  
  signal(SIGINT, sigint_handler);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGSTOP, SIG_IGN);
  
  sigsetjmp(jmpbf, 1);
  for(;;){
    prompt();
  }

  return 0;
}
