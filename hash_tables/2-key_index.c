#include "hash_tables.h"

/**
 * key_index- gives you the index of a key
 * @key: a key
 * @size: size of the array in the hash table
 * Return: returns the index of the key/value pair stored in the hash table
 */

unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}
