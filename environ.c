#include "custom_shell_header.h"

char **_duplicate_environment(void);
void free_custom_environment(void);
char **_find_custom_environment_variable(const char *variable_name);

/**
 * _duplicate_environment - Creates a duplicate of the custom environment.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a double pointer to the duplicated environment.
 */
char **_duplicate_environment(void)
{
	char **new_custom_environment;
	size_t environment_size;
	int index;

	for (environment_size = 0; custom_environment[environment_size]; environment_size++)
		;

	new_custom_environment = malloc(sizeof(char *) * (environment_size + 1));
	if (!new_custom_environment)
		return NULL;

	for (index = 0; custom_environment[index]; index++)
	{
		new_custom_environment[index] = malloc(_strlen(custom_environment[index]) + 1);

		if (!new_custom_environment[index])
		{
			for (index--; index >= 0; index--)
				free(new_custom_environment[index]);
			free(new_custom_environment);
			return NULL;
		}
		_strcpy(new_custom_environment[index], custom_environment[index]);
	}
	new_custom_environment[index] = NULL;

	return new_custom_environment;
}

/**
 * free_custom_environment - Frees the duplicated custom environment.
 */
void free_custom_environment(void)
{
	int index;

	for (index = 0; custom_environment[index]; index++)
		free(custom_environment[index]);
	free(custom_environment);
}

/**
 * _find_custom_environment_variable - Gets an environmental variable from the custom environment.
 * @variable_name: The name of the environmental variable to find.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_find_custom_environment_variable(const char *variable_name)
{
	int index, length;

	length = _strlen(variable_name);
	for (index = 0; custom_environment[index]; index++)
	{
		if (_strncmp(variable_name, custom_environment[index], length) == 0)
			return &custom_environment[index];
	}

	return NULL;
}
