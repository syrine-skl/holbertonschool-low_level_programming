#include "hash_tables.h"

/**
 * hash_table_set- adds an element to a hash table
 * @ht: a hash table to add to
 * @key: the key, cannot be NULL
 * @value: value associated with key
 * Return: 1 on success, else 0
 */

int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	hash_node_t *node, *new_node;
	char *value_copy;

	if (!ht || !key || strlen(key) == 0)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	node = ht->array[index];
	while (node)
	{
		if (strcmp(node->key, key) == 0)
		{
			value_copy = strdup(value);
			if (!value_copy)
				return (0);

			free(node->value);
			node->value = value_copy;
			return (1);
		}
		node = node->next;
	}
	new_node = malloc(sizeof(hash_node_t));
	if (!new_node)
		return (0);
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (0);
	}
	new_node->next = ht->array[index];
	ht->array[index] = new_node;
	return (1);
}

