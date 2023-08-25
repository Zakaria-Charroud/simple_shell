/*
 * File: custom_env_builtins.c
 * Auth: Alex & Sasha
 */
#include "shell.h"

int custom_shell_environment(char **args, char __attribute__((__unused__)) **front);
int custom_shell_initialize_variable(char **args, char __attribute__((__unused__)) **front);
int custom_shell_remove_variable(char **args, char __attribute__((__unused__)) **front);

/**
 * custom_shell_environment - Display the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an issue occurs - -1.
 *         Otherwise - 0.
 *
 * Description: Prints each variable in the format 'variable'='value'.
 */
int custom_shell_environment(char **args, char __attribute__((__unused__)) **front)
{
	int var_idx;
	char newline = '\n';

	if (!custom_environ)
		return (-1);

	for (var_idx = 0; custom_environ[var_idx]; var_idx++)
	{
		write(STDOUT_FILENO, custom_environ[var_idx], _strlen(custom_environ[var_idx]));
		write(STDOUT_FILENO, &newline, 1);
	}

	(void)args;
	return (0);
}

/**
 * custom_shell_initialize_variable - Modify or add an environment variable.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Description: args[1] holds the name of the variable.
 *              args[2] holds the value to set.
 *
 * Return: If an issue occurs - -1.
 *         Otherwise - 0.
 */
int custom_shell_initialize_variable(char **args, char __attribute__((__unused__)) **front)
{
	char **var_entry = NULL, **new_custom_environ, *new_var;
	size_t env_size;
	int var_idx;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_var = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_var)
		return (create_error(args, -1));
	_strcpy(new_var, args[0]);
	_strcat(new_var, "=");
	_strcat(new_var, args[1]);

	var_entry = _get_custom_environment_entry(args[0]);
	if (var_entry)
	{
		free(*var_entry);
		*var_entry = new_var;
		return (0);
	}

	for (env_size = 0; custom_environ[env_size]; env_size++)
		;

	new_custom_environ = malloc(sizeof(char *) * (env_size + 2));
	if (!new_custom_environ)
	{
		free(new_var);
		return (create_error(args, -1));
	}

	for (var_idx = 0; custom_environ[var_idx]; var_idx++)
		new_custom_environ[var_idx] = custom_environ[var_idx];

	free(custom_environ);
	custom_environ = new_custom_environ;
	custom_environ[var_idx] = new_var;
	custom_environ[var_idx + 1] = NULL;

	return (0);
}

/**
 * custom_shell_remove_variable - Delete an environment variable.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Description: args[1] holds the name of the variable to remove.
 *
 * Return: If an issue occurs - -1.
 *         Otherwise - 0.
 */
int custom_shell_remove_variable(char **args, char __attribute__((__unused__)) **front)
{
	char **var_entry, **new_custom_environ;
	size_t env_size;
	int var_idx, new_idx;

	if (!args[0])
		return (create_error(args, -1));

	var_entry = _get_custom_environment_entry(args[0]);
	if (!var_entry)
		return (0);

	for (env_size = 0; custom_environ[env_size]; env_size++)
		;

	new_custom_environ = malloc(sizeof(char *) * env_size);
	if (!new_custom_environ)
		return (create_error(args, -1));

	for (var_idx = 0, new_idx = 0; custom_environ[var_idx]; var_idx++)
	{
		if (*var_entry == custom_environ[var_idx])
		{
			free(*var_entry);
			continue;
		}
		new_custom_environ[new_idx] = custom_environ[var_idx];
		new_idx++;
	}
	free(custom_environ);
	custom_environ = new_custom_environ;
	custom_environ[env_size - 1] = NULL;

	return (0);
}
