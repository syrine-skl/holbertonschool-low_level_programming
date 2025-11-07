#include "main.h"

/**
 * print_diagonal - Entry point
 * @n : number of times character '\' will appear
 * Return: None
 */
void print_diagonal(int n)
{
	int space;
	int line;

	if (n <= 0)
	{
		_putchar('\n');
		return;
	}
	for (line = 0; line < n; line++)
	{
		for (space = 0; space < line; space++)
		{
			_putchar(32); /* space character */
		}
		_putchar(92); /* '\' character */
		_putchar('\n');
	}
}
