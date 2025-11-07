#include "main.h"

/**
 * print_most_numbers - print the numbers from 0 to 9 except 2 and 4
 * Return: nothing
 */
void print_most_numbers(void)
{
	int index = '0';

	while (index <= '9')
	{
		if (!(index == '2' || index == '4'))
		{
			_putchar(index);
		}
		index++;
	}
	_putchar('\n');
return;
}
