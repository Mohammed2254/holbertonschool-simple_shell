#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void tokenize(char *buffer, char **argv);
int execute_command(char **argv);

char *get_path(void);
char *find_command(char *cmd);

#endif /* SHELL_H */

