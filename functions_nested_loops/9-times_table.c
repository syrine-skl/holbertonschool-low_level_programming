#include "main.h"
#include <stdio.h>

/**
 * times_table - main function
 */
void times_table(void)
{
	int row, col, prod;

	for (row = 0; row <= 9; row++) /* outer loop for rows */
	{
		for (col = 0; col <= 9; col++) /*inner loop for column*/
		{
			prod = row * col;
			if (prod > 9)
			{
				if (col != 0)
				{
					_putchar(44);
					_putchar(32);
				}
					_putchar('0' + prod / 10);
					_putchar('0' + prod % 10);
			}
			else
			{
				if (col != 0)
				{
					_putchar(44);
					_putchar(32);
					_putchar(32);
				}
				_putchar('0' + prod);
			}
		}

	_putchar('\n');
	}
}
