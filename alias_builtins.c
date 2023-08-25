#include "shell.h"

int custom_shell_alias(char **arguments, char __attribute__((__unused__)) **front);
void set_custom_alias(char *alias_name, char *alias_value);
void display_custom_alias(custom_alias_t *custom_alias);

/**
 * custom_shell_alias - Builtin command that either prints all custom aliases,
 * specific aliases, or sets a custom alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int custom_shell_alias(char **arguments, char __attribute__((__unused__)) **front)
{
	custom_alias_t *temp = custom_aliases;
	int i, ret = 0;
	char *value;

	if (!arguments[0])
	{
		while (temp)
		{
			display_custom_alias(temp);
			temp = temp->next;
		}
		return ret;
	}
	for (i = 0; arguments[i]; i++)
	{
		temp = custom_aliases;
		value = _strchr(arguments[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(arguments[i], temp->alias_name) == 0)
				{
					display_custom_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_custom_error(arguments + i, 1);
		}
		else
			set_custom_alias(arguments[i], value);
	}
	return ret;
}

/**
 * set_custom_alias - Will either set an existing custom alias 'name' with a new value,
 * 'value' or creates a new custom alias with 'name' and 'value'.
 * @alias_name: Name of the alias.
 * @alias_value: Value of the alias. First character is a '='.
 */
void set_custom_alias(char *alias_name, char *alias_value)
{
	custom_alias_t *temp = custom_aliases;
	int len, j, k;
	char *new_value;

	*alias_value = '\0';
	alias_value++;
	len = _strlen(alias_value) - _strspn(alias_value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; alias_value[j]; j++)
	{
		if (alias_value[j] != '\'' && alias_value[j] != '"')
			new_value[k++] = alias_value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(alias_name, temp->alias_name) == 0)
		{
			free(temp->alias_value);
			temp->alias_value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_custom_alias_end(&custom_aliases, alias_name, new_value);
}

/**
 * display_custom_alias - Prints the custom alias in the format alias_name='alias_value'.
 * @custom_alias: Pointer to a custom alias.
 */
void display_custom_alias(custom_alias_t *custom_alias)
{
	char *alias_string;
	int len = _strlen(custom_alias->alias_name) + _strlen(custom_alias->alias_value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, custom_alias->alias_name);
	_strcat(alias_string, "='");
	_strcat(alias_string, custom_alias->alias_value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

/**
 * replace_custom_aliases - Goes through the arguments and replaces any matching custom alias
 * with its value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_custom_aliases(char **args)
{
	custom_alias_t *temp;
	int i;
	char *new_value;

	if (_strcmp(args[0], "custom_alias") == 0)
		return args;

	for (i = 0; args[i]; i++)
	{
		temp = custom_aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->alias_name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->alias_value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return NULL;
				}
				_strcpy(new_value, temp->alias_value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return args;
}
