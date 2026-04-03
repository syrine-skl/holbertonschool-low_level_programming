#include <stdlib.h>
#include "lists.h"

/**
 * free_dlistint - free a memory list
 * @head: pointer of start list
 */

void free_dlistint(dlistint_t *head)
{
	dlistint_t *temp;

	while (head != NULL)
	{
		temp = head->next;

		free(head);

		head = temp;
	}
}
