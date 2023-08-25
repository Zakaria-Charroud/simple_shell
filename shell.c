#include "shell.h"

void handle_sigint(int sig_num)
{
	if (sig_num == SIGINT)
	{
		_puts("\n#shell$ ");
	}
}

void handle_eof(int len, char *buff)
{
	(void)buff;
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buff);
		}
		exit(0);
	}
}

void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		_puts("#shell$ ");
}

int main(void)
{
	ssize_t len = 0;
	char *buff = NULL, *path_value, *pathname, **args;
	size_t size = 0;
	list_path *path_list = NULL;
	void (*builtin_func)(char **);

	signal(SIGINT, handle_sigint);

	while (len != EOF)
	{
		display_prompt();
		len = getline(&buff, &size, stdin);
		handle_eof(len, buff);

		args = splitstring(buff, " \n");
		if (!args || !args[0])
			execute(args);
		else
		{
			path_value = _getenv("PATH");
			path_list = linkpath(path_value);
			pathname = _which(args[0], path_list);
			builtin_func = checkbuild(args);

			if (builtin_func)
			{
				free(buff);
				builtin_func(args);
			}
			else if (!pathname)
				execute(args);
			else if (pathname)
			{
				free(args[0]);
				args[0] = pathname;
				execute(args);
			}
		}
	}

	free_list(path_list);
	freearv(args);
	free(buff);
	return (0);
}
