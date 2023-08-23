#include "main.h"

void _exit_func(char **environ)
{
	(void)environ;
	
	exit(98);
}

