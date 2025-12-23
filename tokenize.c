#include "shell.h"

/**
 * tokenize - Splits a string into words
 * @buffer: The input string
 * @argv: The array to store the words
 */
void tokenize(char *buffer, char **argv)
{
	char *token;
	int i = 0;
	
	token = strtok(buffer, " \n\t");

	while (token != NULL)
	{
		argv[i] = token;
		token = strtok(NULL, " \n\t");
		i++;
	}
	argv[i] = NULL;
}
