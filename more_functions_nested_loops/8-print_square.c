#include "main.h"

/**
 * print_square - prints a square using the '#' character
 *
 * @size: the length and width of the square
 *
 * Return: nothing
 */
void print_square(int size)
{
	int line;
	int row;

	if (size <= 0)
	{
		_putchar('\n');
		return;
	}
	for (line = 0; line < size; line++)
	{
		for (row = 0; row < size; row++)
		{
			_putchar('#');
		}
		_putchar('\n');
	}
}
