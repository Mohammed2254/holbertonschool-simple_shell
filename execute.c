#include "shell.h"

/**
* execute_command - Forks and executes a command
* @argv: The array of command and arguments
*/
int execute_command(char **argv)
{
	pid_t child_pid;
	int status;

	if (argv[0] == NULL)
		return;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
	}
	else if (child_pid == 0)
	{
		/* Child Process */
		if (execve(argv[0], argv, environ) == -1)
		{
			fprintf(stderr, "No such file or directory\n");
			exit(127);
		}
	}
	else
	{
		/* Parent Process */
		wait(&status);
		
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
return (0);
}
