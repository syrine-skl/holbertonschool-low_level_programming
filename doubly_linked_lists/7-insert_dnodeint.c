#include "lists.h"

/**
 * insert_dnodeint_at_index- inserts a node at an index number
 * @h: a doubly linked list
 * @idx: index to insert the node at
 * @n: integer value for the new node
 * Return: returns the address of the new node or NULL on failure
 */

dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *new = malloc(sizeof(dlistint_t)), *current;
	unsigned int i = 0;

	if (new == NULL)
		return (NULL);

	if (idx == 0)
		return (add_dnodeint(h, n));

	current = *h;
	while (current != NULL && i < idx - 1)
	{
		current = current->next;
		i++;
	}

	if (current == NULL)
		return (NULL);

	new->n = n;
	new->next = current->next;
	new->prev = current;
	if (current->next != NULL)
		current->next->prev = new;
	current->next = new;
	return (new);
}
