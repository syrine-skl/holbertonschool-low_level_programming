#include <stdlib.h>
#include <string.h>
#include "lists.h"

/**
 * add_node_end - adds a new node at the end of a list_t list
 * @head: pointer to pointer of the head of the list
 * @str: string to be duplicated and stored in the node
 *
 * Return: address of the new element, or NULL if it fails
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new_node;
	list_t *temp;
	unsigned int len = 0;

	if (str == NULL)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);

	new_node->str = strdup(str);
	if (new_node->str == NULL)
	{
		free(new_node);
		return (NULL);
	}

	while (str[len])
		len++;

	new_node->len = len;
	new_node->next = NULL;

	/*If list is empty*/
	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}

	/*Traverse to the last node*/
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;

	/*Link new node at the end*/
	temp->next = new_node;

	return (new_node);
}
