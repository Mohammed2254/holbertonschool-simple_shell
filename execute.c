#include "shell.h"

char *trim_spaces(char *str)
{
    char *end;

    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == '\0')
        return (str);

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return (str);
}

char *get_path(void)
{
    int i = 0;

    while (environ[i])
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
            return (environ[i] + 5);
        i++;
    }
    return (NULL);
}

char *find_command(char *cmd)
{
    char *path, *path_copy, *dir, *full_path;

    path = get_path();
    if (!path || path[0] == '\0')
        return (NULL);

    path_copy = strdup(path);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        if (!full_path)
            return (NULL);

        sprintf(full_path, "%s/%s", dir, cmd);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

int execute_command(char **argv)
{
    pid_t pid;
    int status;
    char *cmd_path;

    if (!argv || !argv[0])
        return (0);

    argv[0] = trim_spaces(argv[0]);
    if (argv[0][0] == '\0')
        return (0);

    if (strchr(argv[0], '/'))
    {
        if (access(argv[0], X_OK) != 0)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
            return (127);
        }
        cmd_path = argv[0];
    }
    else
    {
        cmd_path = find_command(argv[0]);
        if (!cmd_path)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
            return (127);
        }
    }

    pid = fork();
    if (pid == -1)
        return (1);

    if (pid == 0)
    {
        execve(cmd_path, argv, environ);
        exit(127);
    }

    wait(&status);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));

    return (0);
}

