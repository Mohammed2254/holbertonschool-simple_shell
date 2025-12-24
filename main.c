#include "shell.h"

int print_env(void)
{
    int i = 0;

    while (environ[i])
    {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
    return (0);
}

int main(void)
{
    char *buffer = NULL;
    size_t n = 0;
    ssize_t nread;
    char *argv[100];
    int last_status = 0;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("#cisfun$ ");

        nread = getline(&buffer, &n, stdin);
        if (nread == -1)
        {
            free(buffer);
            exit(last_status);
        }

        tokenize(buffer, argv);

        if (argv[0] == NULL)
            continue;

        if (strcmp(argv[0], "exit") == 0)
        {
            free(buffer);
            exit(last_status);
        }

        if (strcmp(argv[0], "env") == 0)
        {
            print_env();
            continue;
        }

        last_status = execute_command(argv);
    }

    free(buffer);
    return (0);
}

