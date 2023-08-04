#include "main.h"

/**
 * clear_bit - Sets the value of a specific bit to 0.
 *
 * This function takes a pointer to a number @n and an @index representing the bit
 * position that needs to be cleared (set to 0) in the number. The index is 0-based,
 * counting from the rightmost bit as 0, moving leftward with each bit position.
 *
 * @n: Pointer to the number whose bit needs to be cleared.
 * @index: Index of the bit to clear (0-indexed).
 *
 * Return: 1 if the bit was successfully cleared, -1 if an error occur.
 *
 * Note: This function assumes that the number @n is represented using at least the
 * number of bits required to store an unsigned long on the target platform.
 * To avoid undefined behavior, ensure that the @index is within valid bounds
 * (0 to (sizeof(unsigned long) * 8) - 1) before calling this function.
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);

	*n = (~(1UL << index) & *n);
	return (1);
}

