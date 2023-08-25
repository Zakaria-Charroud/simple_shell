#include "holberton.h"

/**
 * execute_proc - Executes a given command.
 * @cmd: A pointer to the command and arguments.
 *
 * Description: Executes the command either by using its absolute path
 * if it exists, or by searching for the command in the PATH.
 */
void execute_proc(char **cmd)
{
	char *param = (*(cmd + 1));
	char *s, *path_separator = "/";
	char *o;

	char *command = *cmd;
	char *argv[4];

	if ((access(command, F_OK) == 0))
	{
		argv[0] = command;
		argv[1] = param;
		argv[2] = ".";
		argv[3] = NULL;

		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
		}
	}
	else
	{
		o = find_command(vartoprint);

		path_separator = str_concat(o, path_separator);

		s = str_concat(path_separator, command);

		argv[0] = s;
		argv[1] = param;
		argv[2] = ".";
		argv[3] = NULL;

		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
		}
	}
}
