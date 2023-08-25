#include "holberton.h"

/**
 * _strcmpdir - Compares strings to find a directory.
 *
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: 0 if match, non-zero if otherwise.
 **/
int _strcmpdir(char *s1, char *s2)
{
	int i = 0;

	while (*s2 != '\0' && *s1 != '\0' && *s1 == *s2)
	{
		if (i == 3)
			break;
		i++;
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * charput - Writes the character like putchar.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int charput(char c)
{
	return (write(1, &c, 1));
}

/**
 * place - Prints a string.
 * @str: The string to be printed.
 */
void place(char *str)
{
	while (*str != '\0')
	{
		charput(*str);
		str++;
	}
}

/**
 * _strlen - Computes the length of a string.
 * @str: The string.
 * Return: Length of the string.
 */
int _strlen(char *str)
{
	int length;

	for (length = 0; str[length] != '\0'; length++)
		;

	return (length);
}

/**
 * str_concat - Concatenates two strings.
 * @s1: First string.
 * @s2: Second string.
 * Return: Concatenated string, or NULL on failure.
 */
char *str_concat(char *s1, char *s2)
{
	char *result;
	int len_s1, len_s2, i, j;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	len_s1 = _strlen(s1);
	len_s2 = _strlen(s2);

	result = malloc((len_s1 + len_s2 + 1) * sizeof(char));

	if (result == NULL)
		return (NULL);

	for (i = 0; i < len_s1; i++)
	{
		result[i] = s1[i];
	}

	for (j = len_s1, i = 0; i <= len_s2; j++, i++)
	{
		result[j] = s2[i];
	}

	return (result);
}
