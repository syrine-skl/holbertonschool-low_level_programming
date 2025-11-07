#include "main.h"

/**
 * print_two_digits - print a number from 0 to 14 using _putchar
 * @n: number to print
 *
 * Note: uses _putchar exactly twice in this function body
 */
void print_two_digits(int n)
{
	if (n >= 10)
		_putchar('1');
	_putchar((n % 10) + '0');
}

/**
 * more_numbers - prints 10 times the numbers from 0 to 14
 *
 * Allowed: exactly three _putchar occurrences in source:
 *  - two in print_two_digits (tens and units)
 *  - one here for the newline at the end of each line
 */
void more_numbers(void)
{
	int line, n;

	for (line = 0; line < 10; line++)
	{
		for (n = 0; n <= 14; n++)
			print_two_digits(n);
		_putchar('\n');
	}
}
