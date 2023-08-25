#include "holberton.h"

/**
 * find_command - Finds the path to execute a command.
 * @command: The command to search for.
 *
 * Return: The path to the folder containing the command.
 **/
char *find_command(char *command)
{
	DIR *folder;
	struct dirent *entry;
	char *env_path, *path, *cmd_name, *result = NULL;

	while (*environ != NULL)
	{
		if (!(_strcmpdir(*environ, "PATH")))
		{
			env_path = *environ;
			path = strtok(env_path, ":='PATH'");
			folder = opendir(path);
			if (folder == NULL)
			{
				perror("Unable to read directory");
				return ("Error");
			}
			while ((entry = readdir(folder)))
			{
				cmd_name = entry->d_name;
				if (_strcmpdir(cmd_name, command) == 0)
				{
					result = path;
					break;
				}
			}
			closedir(folder);
		}
		environ++;
	}

	if (result == NULL)
		return ("Error: Not Found");
	return (result);
}
