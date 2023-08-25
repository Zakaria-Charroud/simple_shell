#include "shell.h"

/**
 * split_string - Splits a string into an array of pointers to words.
 * @str: The string to be split.
 * @delim: The delimiter.
 * Return: An array of pointers to words.
 */
char **split_string(char *str, const char *delim)
{
    int word_count = 2;
    char **word_array;
    char *token;
    char *copy;

    copy = malloc(_strlen(str) + 1);
    if (copy == NULL)
    {
        perror(_getenv("_"));
        return (NULL);
    }

    for (int i = 0; str[i]; i++)
        copy[i] = str[i];
    copy[_strlen(str)] = '\0';

    token = strtok(copy, delim);
    word_array = malloc(sizeof(char *) * 2);
    word_array[0] = _strdup(token);

    int index = 1;
    while (token)
    {
        token = strtok(NULL, delim);
        word_array = _realloc(word_array, sizeof(char *) * (index - 1), sizeof(char *) * word_count);
        word_array[index] = _strdup(token);
        index++;
        word_count++;
    }
    free(copy);
    return (word_array);
}

/**
 * execute_command - Executes a command.
 * @args: Array of arguments.
 */
void execute_command(char **args)
{
    int child_pid, status;

    if (!args || !args[0])
        return;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror(_getenv("_"));
    }

    if (child_pid == 0)
    {
        execve(args[0], args, environ);
        perror(args[0]);
        exit(EXIT_FAILURE);
    }

    wait(&status);
}

/**
 * reallocate_memory - Reallocates memory block.
 * @ptr: Pointer to be reallocated.
 * @old_size: Old size of the memory block.
 * @new_size: New size for the memory block.
 * Return: Pointer to the reallocated memory block.
 */

void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;
    char *old_ptr;

    unsigned int i;

    if (ptr == NULL)
        return (malloc(new_size));

    if (new_size == old_size)
        return (ptr);

    if (new_size == 0 && ptr != NULL)
    {
        free(ptr);
        return (NULL);
    }

    new_ptr = malloc(new_size);
    old_ptr = ptr;
    if (new_ptr == NULL)
        return (NULL);

    if (new_size > old_size)
    {
        for (i = 0; i < old_size; i++)
            new_ptr[i] = old_ptr[i];
        free(ptr);
        for (i = old_size; i < new_size; i++)
            new_ptr[i] = '\0';
    }
    if (new_size < old_size)
    {
        for (i = 0; i < new_size; i++)
            new_ptr[i] = old_ptr[i];
        free(ptr);
    }
    return (new_ptr);
}

/**
 * free_array - Frees the array of pointers.
 * @array: Array of pointers to be freed.
 */

void free_array(char **array)
{
    int index;

    for (index = 0; array[index]; index++)
        free(array[index]);
    free(array);
}
