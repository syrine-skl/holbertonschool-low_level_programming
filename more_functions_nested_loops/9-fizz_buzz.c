#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int index;

	for (index = 1; index <= 100; index++)
	{
		if (index % 3 == 0 && index % 5 == 0)
		{
			printf("FizzBuzz ");
		}
		else if (index % 3 == 0)
		{
			printf("Fizz ");
		}
		else if (index % 5 == 0)
		{
			if (index != 100)
			printf("Buzz ");
			else
				printf("Buzz");
		}
		else
		printf("%d ", index);
	}
	printf("\n");
	return (0);
}
