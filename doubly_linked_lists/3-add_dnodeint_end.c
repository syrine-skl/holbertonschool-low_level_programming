#include "lists.h"

/**
 * add_dnodeint_end- adds a new last node to a linked list
 * @head: a linked list
 * @n: an integer
 * Return: the address of the new element, or NULL on failure
 */

dlistint_t *add_dnodeint_end(dlistint_t **head, const int n)
{
	dlistint_t *new, *current;

	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
		return (NULL);

	new->n = n;
	new->next = NULL;

	if (*head == NULL)
	{
		new->prev = NULL;
		*head = new;
		return (new);
	}

	current = *head;
	while (current->next != NULL)
		current = current->next;

	current->next = new;
	new->prev = current;

	return (new);
}
