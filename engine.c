#include "custom_header.h"

/**
 * check_slash - Checks if the first character is a slash.
 * @command: First string.
 * Return: 1 if yes, 0 if no.
 */
int check_slash(char *command)
{
	int count = 0;

	while (command[count])
	{
		if (command[0] == '/')
		{
			printf("%c\n", command[0]);
			return 1;
		}

		count++;
	}
	return 0;
}

/**
 * compare_exit - Compares strings for exit command.
 * @str1: First string.
 * @str2: Exit string.
 * Return: 1 if yes, 0 if no.
 */
int compare_exit(char *str1, char *str2)
{
	int i = 0;

	for (; (*str2 != '\0' && *str1 != '\0') && *str1 == *str2; str1++)
	{
		if (i == 3)
			break;
		i++;
		str2++;
	}

	return *str1 - *str2;
}

/**
 * compare_environment - Compares strings for environment command.
 * @str1: First string.
 * @str2: Environment string.
 * Return: 1 if yes, 0 if no.
 */
int compare_environment(char *str1, char *str2)
{
	int i = 0;

	for (; (*str2 != '\0' && *str1 != '\0') && *str1 == *str2; str1++)
	{
		if (i == 2)
			break;
		i++;
		str2++;
	}

	return *str1 - *str2;
}

/**
 * parse_input - Identifies keyboard input.
 * @input: Input string from another function (prompt).
 * Return: Buffer containing parsed input.
 **/
char **parse_input(char *input)
{
	char **buffer = malloc(1024 * sizeof(char *));
	char *split;
	int i = 0;
	char *delimiters = " \t\n";

	split = strtok(input, delimiters);

	while (split != NULL)
	{
		buffer[i] = split;
		i++;
		split = strtok(NULL, delimiters);
	}
	execute_process(buffer);
	return buffer;
}

/**
 * handle_control_c - Handles Ctrl+C to avoid shell closure.
 * @signal: Signal to keep the shell running.
 **/
void  handle_control_c(int signal)
{
	(void) signal;
	write(1, "\n$ ", 3);
}
