#include "shell.h"

/**
* main - Simple Shell main loop
* Return: 0 on success
*/
int main(void)
{
	char *buffer = NULL;
	size_t n = 0;
	ssize_t nread;
	char *argv[100];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		nread = getline(&buffer, &n, stdin);

		if (nread == -1)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		tokenize(buffer, argv);

		if (argv[0] == NULL)
			continue;
		if (strcmp(argv[0], "exit") == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		execute_command(argv);

	}

free(buffer);
return (0);
}
