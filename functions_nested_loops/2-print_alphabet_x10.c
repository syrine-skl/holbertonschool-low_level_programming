#include "main.h"

/**
* print_alphabet_x10 - prints the alphabet 10 times in lowercase
*/

void print_alphabet_x10(void)
{

int n;
char letter;

for (n = 1; n <= 10; n++)
{
for (letter = 'a'; letter <= 'z'; letter++)
{
_putchar(letter);
}
_putchar('\n');
}

}
