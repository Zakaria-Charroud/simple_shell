#include "shell.h"

char *custom_error_126(char **cmd_args);
char *custom_error_127(char **cmd_args);

/**
 * custom_error_126 - Creates an error message for permission denied failures.
 * @cmd_args: An array of command arguments.
 *
 * Return: The error string.
 */
char *custom_error_126(char **cmd_args)
{
	char *error_msg, *hist_num_str;
	int error_msg_len;

	hist_num_str = _itoa(history_number);
	if (!hist_num_str)
		return (NULL);

	error_msg_len = _strlen(shell_name) + _strlen(hist_num_str) + _strlen(cmd_args[0]) + 24;
	error_msg = malloc(sizeof(char) * (error_msg_len + 1));
	if (!error_msg)
	{
		free(hist_num_str);
		return (NULL);
	}

	_strcpy(error_msg, shell_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, hist_num_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, cmd_args[0]);
	_strcat(error_msg, ": Permission denied\n");

	free(hist_num_str);
	return (error_msg);
}

/**
 * custom_error_127 - Creates an error message for command not found failures.
 * @cmd_args: An array of command arguments.
 *
 * Return: The error string.
 */
char *custom_error_127(char **cmd_args)
{
	char *error_msg, *hist_num_str;
	int error_msg_len;

	hist_num_str = _itoa(history_number);
	if (!hist_num_str)
		return (NULL);

	error_msg_len = _strlen(shell_name) + _strlen(hist_num_str) + _strlen(cmd_args[0]) + 16;
	error_msg = malloc(sizeof(char) * (error_msg_len + 1));
	if (!error_msg)
	{
		free(hist_num_str);
		return (NULL);
	}

	_strcpy(error_msg, shell_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, hist_num_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, cmd_args[0]);
	_strcat(error_msg, ": not found\n");

	free(hist_num_str);
	return (error_msg);
}
