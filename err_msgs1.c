#include "custom_shell_errors.h"

char *generate_custom_env_error(char **args);
char *generate_custom_alias_error(char **args);
char *generate_custom_exit_error(char **args);
char *generate_custom_cd_error(char **args);
char *generate_custom_syntax_error(char **args);

/**
 * generate_custom_env_error - Creates an error message for custom_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *generate_custom_env_error(char **args)
{
	char *error_message, *hist_str;
	int len;

	hist_str = _itoa(custom_history);
	if (!hist_str)
		return NULL;

	args--;
	len = _strlen(custom_shell_name) + _strlen(hist_str) + _strlen(args[0]) + 45;
	error_message = malloc(sizeof(char) * (len + 1));
	if (!error_message)
	{
		free(hist_str);
		return NULL;
	}

	_strcpy(error_message, custom_shell_name);
	_strcat(error_message, ": ");
	_strcat(error_message, hist_str);
	_strcat(error_message, ": ");
	_strcat(error_message, args[0]);
	_strcat(error_message, ": Unable to add/remove from environment\n");

	free(hist_str);
	return error_message;
}

/**
 * generate_custom_alias_error - Creates an error message for custom_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *generate_custom_alias_error(char **args)
{
	char *error_message;
	int len;

	len = _strlen(custom_shell_name) + _strlen(args[0]) + 13;
	error_message = malloc(sizeof(char) * (len + 1));
	if (!error_message)
		return NULL;

	_strcpy(error_message, "alias: ");
	_strcat(error_message, args[0]);
	_strcat(error_message, " not found\n");

	return error_message;
}

/**
 * generate_custom_exit_error - Creates an error message for custom_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *generate_custom_exit_error(char **args)
{
	char *error_message, *hist_str;
	int len;

	hist_str = _itoa(custom_history);
	if (!hist_str)
		return NULL;

	len = _strlen(custom_shell_name) + _strlen(hist_str) + _strlen(args[0]) + 27;
	error_message = malloc(sizeof(char) * (len + 1));
	if (!error_message)
	{
		free(hist_str);
		return NULL;
	}

	_strcpy(error_message, custom_shell_name);
	_strcat(error_message, ": ");
	_strcat(error_message, hist_str);
	_strcat(error_message, ": exit: Illegal number: ");
	_strcat(error_message, args[0]);
	_strcat(error_message, "\n");

	free(hist_str);
	return error_message;
}

/**
 * generate_custom_cd_error - Creates an error message for custom_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *generate_custom_cd_error(char **args)
{
	char *error_message, *hist_str;
	int len;

	hist_str = _itoa(custom_history);
	if (!hist_str)
		return NULL;

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(custom_shell_name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error_message = malloc(sizeof(char) * (len + 1));
	if (!error_message)
	{
		free(hist_str);
		return NULL;
	}

	_strcpy(error_message, custom_shell_name);
	_strcat(error_message, ": ");
	_strcat(error_message, hist_str);
	if (args[0][0] == '-')
		_strcat(error_message, ": cd: Illegal option ");
	else
		_strcat(error_message, ": cd: can't cd to ");
	_strcat(error_message, args[0]);
	_strcat(error_message, "\n");

	free(hist_str);
	return error_message;
}

/**
 * generate_custom_syntax_error - Creates an error message for custom_syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *generate_custom_syntax_error(char **args)
{
	char *error_message, *hist_str;
	int len;

	hist_str = _itoa(custom_history);
	if (!hist_str)
		return NULL;

	len = _strlen(custom_shell_name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	error_message = malloc(sizeof(char) * (len + 1));
	if (!error_message)
	{
		free(hist_str);
		return NULL;
	}

	_strcpy(error_message, custom_shell_name);
	_strcat(error_message, ": ");
	_strcat(error_message, hist_str);
	_strcat(error_message, ": Syntax error: \"");
	_strcat(error_message, args[0]);
	_strcat(error_message, "\" unexpected\n");

	free(hist_str);
	return error_message;
}
