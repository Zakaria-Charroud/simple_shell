#include "shell.h"
int (*get_builtin_command(char *cmd))(char **args, char **front);
int custom_shell_exit(char **args, char **front);
int custom_shell_change_directory(char **args, char __attribute__((__unused__)) **front);
int custom_shell_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin_command - Matches a command with a corresponding
 *                      custom shell builtin function.
 * @cmd: The command to match.
 *
 * Return: A function pointer to the corresponding builtin function.
 */
int (*get_builtin_command(char *cmd))(char **args, char **front)
{
	builtin_t custom_funcs[] = {
		{ "exit", custom_shell_exit },
		{ "env", custom_shell_env },
		{ "setenv", custom_shell_setenv },
		{ "unsetenv", custom_shell_unsetenv },
		{ "cd", custom_shell_change_directory },
		{ "alias", custom_shell_alias },
		{ "help", custom_shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; custom_funcs[i].name; i++)
	{
		if (_strcmp(custom_funcs[i].name, cmd) == 0)
			break;
	}
	return (custom_funcs[i].f);
}

/**
 * custom_shell_exit - Causes the shell to terminate.
 * @args: An array of arguments containing the exit status.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If no arguments - -3.
 *         If an invalid exit status - 2.
 *         Otherwise - exits with the given status.
 */
int custom_shell_exit(char **args, char **front)
{
	int i, int_len = 10;
	unsigned int status = 0, max_status = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			int_len++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= int_len && args[0][i] >= '0' && args[0][i] <= '9')
				status = (status * 10) + (args[0][i] - '0');
			else
				return (create_custom_error(args - 1, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (status > max_status - 1)
		return (create_custom_error(args - 1, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_custom_alias_list(custom_aliases);
	exit(status);
}

/**
 * custom_shell_change_directory - Changes the current directory.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a valid directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int custom_shell_change_directory(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *newline = "\n";
	char *old_dir = NULL, *current_dir = NULL;
	struct stat directory;

	old_dir = getcwd(old_dir, 0);
	if (!old_dir)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(old_dir);
				return (create_custom_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &directory) == 0 && S_ISDIR(directory.st_mode)
					&& ((directory.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(old_dir);
				return (create_custom_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	current_dir = getcwd(current_dir, 0);
	if (!current_dir)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = old_dir;
	if (custom_shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = current_dir;
	if (custom_shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, current_dir, _strlen(current_dir));
		write(STDOUT_FILENO, newline, 1);
	}
	free(old_dir);
	free(current_dir);
	free(dir_info);
	return (0);
}

/**
 * custom_shell_help - Displays information about custom shell builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int custom_shell_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		custom_help_all();
	else if (_strcmp(args[0], "alias") == 0)
		custom_help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		custom_help_change_directory();
	else if (_strcmp(args[0], "exit") == 0)
		custom_help_exit();
	else if (_strcmp(args[0], "env") == 0)
		custom_help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		custom_help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		custom_help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		custom_help_help();
	else
		write(STDERR_FILENO, shell_name, _strlen(shell_name));

	return (0);
}
