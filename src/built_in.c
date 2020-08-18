#include "built_in.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

int mish_cd(void *arg) {
  char *home = getenv("HOME");
  if(arg == NULL) {
    return chdir(home);
  }else {
    return chdir((char*)arg);
  }
  return 0; /*not reachable*/
}

int mish_exit(void *arg) {
  exit(EXIT_SUCCESS);
}

int mish_pwd(void *arg) {
  char cwd[PATH_MAX];
  if(getcwd(cwd, PATH_MAX) != 0){
    return -1;
  }
  printf("%s\n", cwd);
  return 0;
}

int mish_echo(void *arg) {
  printf("%s", (char *)arg);
  return 0;
}
