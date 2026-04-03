#include "hash_tables.h"
/**
 * hash_table_get- fetches value associated with key
 * @ht: a hash table to search
 * @key: a key to search for
 * Return: the value associated with key or NULL
 */

char *hash_table_get(const hash_table_t *ht, const char *key)
{
	hash_node_t *node;
	unsigned long int index;

	if (!ht || !key || strlen(key) == 0)
	{
		return (NULL);
	}

	index = key_index((const unsigned char *)key, ht->size);

	node = ht->array[index];
	while (node)
	{
		if (strcmp(node->key, key) == 0)
		{
			return (node->value);
		}
		node = node->next;
	}

	return (NULL);
}
