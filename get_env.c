#include "main.h"

char *_getenv(const char *name)
{
    extern char **environ;
    int i = 0;
    char *key;

    while (environ[i])
    {
        key = strtok(environ[i], "=");
        if (strcmp(name, key) == 0)
        {
            return (strtok(NULL, "\n"));
        }
        i++;
        
    }
    return (NULL);
}

char *get_command(char *command)
{
    char *path = _getenv("PATH");
    char *token ;
    char *cmd_full;
    struct stat st;

    token = strtok(path, ":");
    while (token)
    {
        cmd_full = malloc(strlen(token) + strlen(command) + 2);
        strcpy(cmd_full, token);
        strcat(cmd_full,"/");
        strcat(cmd_full, command);
        if (stat(cmd_full, &st) == 0)
        {
            return (cmd_full);
        }
        free(cmd_full);
        token = strtok(NULL, ":");
        
    }
    return (NULL);
}

