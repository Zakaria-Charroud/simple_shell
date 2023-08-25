#include "shell.h"

/**
 * _getenv - Gets the value of the global variable.
 * @name: Name of the global variable.
 * Return: String of the value.
 */
char *_getenv(const char *name)
{
    int i, j;
    char *value;

    if (!name)
        return (NULL);

    for (i = 0; environ[i]; i++)
    {
        j = 0;
        if (name[j] == environ[i][j])
        {
            while (name[j])
            {
                if (name[j] != environ[i][j])
                    break;
                j++;
            }
            if (name[j] == '\0')
            {
                value = (environ[i] + j + 1);
                return (value);
            }
        }
    }
    return (0);
}

/**
 * add_node_end - Adds a new node at the end of a list.
 * @head: Pointer to the pointer to the linked list.
 * @str: String to be added to the new node.
 * Return: Address of the new element/node.
 */
list_path *add_node_end(list_path **head, char *str)
{
    list_path *tmp;
    list_path *new;

    new = malloc(sizeof(list_path));
    if (!new || !str)
    {
        return (NULL);
    }

    new->dir = str;
    new->p = NULL;

    if (!*head)
    {
        *head = new;
    }
    else
    {
        tmp = *head;
        while (tmp->p)
        {
            tmp = tmp->p;
        }
        tmp->p = new;
    }

    return (*head);
}

/**
 * link_path - Creates a linked list for path directories.
 * @path: String of path value.
 * Return: Pointer to the created linked list.
 */
list_path *link_path(char *path)
{
    list_path *head = NULL;
    char *token;
    char *cpath = _strdup(path);

    token = strtok(cpath, ":");
    while (token)
    {
        head = add_node_end(&head, token);
        token = strtok(NULL, ":");
    }

    return (head);
}

/**
 * _which - Finds the pathname of a filename.
 * @filename: Name of the file or command.
 * @head: Head of the linked list of path directories.
 * Return: Pathname of filename or NULL if no match.
 */
char *_which(char *filename, list_path *head)
{
    struct stat st;
    char *string;
    list_path *tmp = head;

    while (tmp)
    {
        string = concat_all(tmp->dir, "/", filename);
        if (stat(string, &st) == 0)
        {
            return (string);
        }
        free(string);
        tmp = tmp->p;
    }

    return (NULL);
}

/**
 * free_list - Frees a linked list.
 * @head: Pointer to the linked list.
 */
void free_list(list_path *head)
{
    list_path *storage;

    while (head)
    {
        storage = head->p;
        free(head->dir);
        free(head);
        head = storage;
    }
}
