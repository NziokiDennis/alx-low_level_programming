#include "main.h"

/**
 * clear_bit - Sets the value of a specific bit to 0.
 * @n: Pointer to the number whose bit needs to be cleared.
 * @index: Index of the bit to clear (0-indexed).
 * Return: 1 if the bit was successfully cleared, -1 if an error occur.
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);

	*n = (~(1UL << index) & *n);
	return (1);
}

