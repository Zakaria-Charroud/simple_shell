#include "shell.h"

void custom_help_environment(void);
void custom_help_initialize_variable(void);
void custom_help_remove_variable(void);
void custom_help_view_history(void);

/**
 * custom_help_environment - Displays information on the custom shell builtin command 'environment'.
 */
void custom_help_environment(void)
{
	char *msg = "environment: environment\n\tDisplay the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * custom_help_initialize_variable - Displays information on the custom shell builtin command 'initialize_variable'.
 */
void custom_help_initialize_variable(void)
{
	char *msg = "initialize_variable: initialize_variable [VARIABLE] [VALUE]\n\tCreate a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable or modify an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tPrints an error message to stderr upon failure.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * custom_help_remove_variable - Displays information on the custom shell builtin command 'remove_variable'.
 */
void custom_help_remove_variable(void)
{
	char *msg = "remove_variable: remove_variable [VARIABLE]\n\tDelete an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tPrints an error ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr upon failure.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
