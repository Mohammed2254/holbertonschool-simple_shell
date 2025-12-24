#include "shell.h"

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
    struct stat st;

    path = get_path();
    if (!path)
        return (NULL);

    path_copy = strdup(path);
    dir = strtok(path_copy, ":");

    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        if (!full_path)
            return (NULL);

        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
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
    pid_t child_pid;
    int status;
    char *cmd_path;
    struct stat st;

    if (argv[0] == NULL)
        return (0);

    if (strchr(argv[0], '/'))
    {
        if (stat(argv[0], &st) != 0)
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

    child_pid = fork();
    if (child_pid == -1)
        return (1);

    if (child_pid == 0)
    {
        execve(cmd_path, argv, environ);
        exit(127);
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    }

    return (0);
}

