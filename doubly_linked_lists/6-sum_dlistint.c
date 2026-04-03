#include "lists.h"

/**
 * sum_dlistint- sums the elements of a doubly linked list
 * @head: a doubly linked list
 * Return: returns the sum of elements of the list
 */

int sum_dlistint(dlistint_t *head)
{
	int sum = 0;

	if (head == NULL)
		return (0);

	while (head != NULL)
	{
		sum += head->n;
		head = head->next;
	}
	return (sum);
}
