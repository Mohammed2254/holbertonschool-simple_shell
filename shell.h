#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* Prototypes */
void tokenize(char *buffer, char **argv);
void execute_command(char **argv);

#endif/*SHELL_H*/
