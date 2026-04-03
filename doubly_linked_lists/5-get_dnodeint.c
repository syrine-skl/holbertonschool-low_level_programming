#include "lists.h"

/**
 * get_dnodeint_at_index- returns node at the index input
 * @head: a doubly linked list
 * @index: index to return
 * Return: returns the node at index number
 */

dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
	while (head != NULL && index > 0)
	{
		if (head == NULL)
			return (NULL);
		head = head->next;
		index--;
	}
	return (head);
}
