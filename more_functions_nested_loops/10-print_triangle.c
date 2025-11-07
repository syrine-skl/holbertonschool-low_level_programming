#include "main.h"

/**
 * print_triangle - Entry point
 *
 * @size: triangle size
 *
 * Return: none
 */

void print_triangle(int size)
{
	int line;
	int space;
	int row;

	if (size <= 0)
	{
		_putchar('\n');
		return;
	}
	for (line = 1; line <= size; line++)
	{
		for (space = size - line; space > 0; space--)
		{
			_putchar(32); /* space character */
		}
		for (row = 1; row <= line; row++)
		{
			_putchar('#');
		}
		_putchar('\n');
	}
}
