#include "main.h"

int main(int ac, char **av, char **env)
{
char *buffer = NULL;
size_t buffer_size = 0;
int n_char, stat, i = 0;
char *token;
char *cmd;
char **arr;
pid_t pid;
(void)ac;
(void)av;

while (1)
{
write(1, "$ ", 2);
n_char = getline(&buffer, &buffer_size, stdin);
if (n_char == -1)
{
    write(1, "\n", 1);
    perror("getline");
    _exit(1);
}
arr = malloc(sizeof(char *) * 1024);
token = strtok(buffer, " \t\n");
while (token)
{
    arr[i] = token;
    token = strtok(NULL, " \t\n");
    i++;
}


if (strcmp(arr[0], "exit") == 0)
{
    printf("exiting shell\n");
    _exit(0);
}
arr[i] = NULL;
pid = fork(); 
if (pid == 0)
{
    cmd = get_command(arr[0]);
    if (cmd)
    {
        execve(cmd, arr,env);
    }
    else
    {
        printf("command not found \n");
    }
    _exit(0);
}
else
    wait(&stat);
i = 0;
free(arr);
}
return (0);
}
