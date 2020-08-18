#ifndef __TOOLS_H_
#define __TOOLS_H_

char *alias_check(char *input); // check if the command is and alias
void alias_set(char *name, char *command); // set an alias in ~/.mish_aliases
char *get_path(char *command); // get realpath of a binary by it's name
void sigint_handel(void); // handeling CTRL-C signals
void sigquit_handel(void); // handeling CTRL-D signals

#endif