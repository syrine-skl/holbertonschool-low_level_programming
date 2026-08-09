#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * addition - Adds two numbers.
 * @a: First number.
 * @b: Second number.
 * Return: Sum of a and b.
 */
double addition(double a, double b)
{
	return (a + b);
}

/**
 * soustraction - Subtracts b from a.
 * @a: First number.
 * @b: Second number.
 * Return: Difference of a and b.
 */
double soustraction(double a, double b)
{
	return (a - b);
}

/**
 * multiplication - Multiplies two numbers.
 * @a: First number.
 * @b: Second number.
 * Return: Product of a and b.
 */
double multiplication(double a, double b)
{
	return (a * b);
}

/**
 * division - Divides a by b.
 * @a: First number.
 * @b: Second number.
 * Return: Result of the division.
 */
double division(double a, double b)
{
	return (a / b);
}

/**
 * main - Entry point for the simple calculator program.
 * Return: Always 0 (Success).
 */
int main(void)
{
	double nombre1 = 0, nombre2 = 0, resultat = 0;
	int choixOperation = -1;

	while (choixOperation != 0)
	{
		printf("Simple Calculator\n1) Add\n2) Substract\n");
		printf("3) Multiply\n4) Divide\n0) Quit\n");
		if (scanf("%d", &choixOperation) != 1)
			break;
		if (choixOperation == 0)
		{
			printf("Goodbye!\n");
			break;
		}
		if (choixOperation >= 1 && choixOperation <= 4)
		{
			printf("Enter two numbers\nA: ");
			scanf("%lf", &nombre1);
			printf("B: ");
			scanf("%lf", &nombre2);
			if (choixOperation == 1)
				resultat = addition(nombre1, nombre2);
			else if (choixOperation == 2)
				resultat = soustraction(nombre1, nombre2);
			else if (choixOperation == 3)
				resultat = multiplication(nombre1, nombre2);
			else if (choixOperation == 4)
			{
				if (nombre2 != 0)
					resultat = division(nombre1, nombre2);
				else
					printf("Error: Division by zero\n");
			}
			printf("Result: %.2f\n", resultat);
		}
		else if (choixOperation != 0)
			printf("Invalid option, please try again\n");
	}
	return (0);
}
