#ifndef __TOOLS_H_
#define __TOOLS_H_

char *alias_check(char *input);
void alias_set(char *name, char *command);
char *get_path(char *command);
void sigint_handel(void);
void sigquit_handel(void);

#endif