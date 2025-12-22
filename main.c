#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
	int Res = isatty(0);
	char *buffer = NULL;
	char *command = NULL;
	char *freeCommand = NULL;
	int fork0;
	char *argm[2];
	int len;
	int ifwrong;
	size_t n = 0;
ssize_t nread;

	while (1)
	{
		if (Res == 1)
			printf("#cisfun$");

		nread = getline(&buffer, &n, stdin);
		if (nread == -1)
		{
			free(buffer);
			exit(0);
		}
		freeCommand = command;
		command = strtok(buffer, " \n\t");
		if (command == NULL)
			continue;

		fork0 = fork();


		argm[0] = command;
		argm[1] = NULL;

		if (fork0 == 0)
		{
		ifwrong = execve (command,argm,environ);
			if (ifwrong == -1)
				exit(1);
		}
		if (fork0 > 0)
			wait(NULL);
		else
		fprintf(stderr, "No such file or directory\n");

		free(freeCommand);


	}
    return (0);
}
