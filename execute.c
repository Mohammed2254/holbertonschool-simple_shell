#include "shell.h"

char *trim_spaces(char *s)
{
    char *end;

    while (*s == ' ' || *s == '\t')
        s++;

    if (*s == '\0')
        return (s);

    end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return (s);
}

char *get_path(void)
{
    int i = 0;

    while (environ && environ[i])
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
            return (environ[i] + 5);
        i++;
    }
    return (NULL);
}

char *find_command(char *cmd)
{
    char *path, *copy, *dir, *full;
    size_t len;

    path = get_path();
    if (!path || path[0] == '\0')
        return (NULL);

    copy = strdup(path);
    if (!copy)
        return (NULL);

    dir = strtok(copy, ":");
    while (dir)
    {
        len = strlen(dir) + strlen(cmd) + 2;
        full = malloc(len);
        if (!full)
        {
            free(copy);
            return (NULL);
        }

        sprintf(full, "%s/%s", dir, cmd);

        if (access(full, X_OK) == 0)
        {
            free(copy);
            return (full);
        }

        free(full);
        dir = strtok(NULL, ":");
    }

    free(copy);
    return (NULL);
}

int execute_command(char **argv)
{
    pid_t pid;
    int status;
    char *cmd_path = NULL;
    int from_path = 0;

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
        from_path = 1;
    }

    pid = fork();
    if (pid == -1)
    {
        if (from_path)
            free(cmd_path);
        return (1);
    }

    if (pid == 0)
    {
        execve(cmd_path, argv, environ);
        exit(127);
    }

    wait(&status);

    if (from_path)
        free(cmd_path);

    if (WIFEXITED(status))
        return (WEXITSTATUS(status));

    return (0);
}

