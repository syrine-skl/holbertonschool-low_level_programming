#include "main.h"

/**
 * print_numbers - print the numbers from 0 to 9
 * Return: 0 (Success)
 */
void print_numbers(void)
{
	int index = '0';

	while (index <= '9')
	{
		_putchar(index);
		index++;
	}
	_putchar('\n');
return;
}
