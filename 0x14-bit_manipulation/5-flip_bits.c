#include "main.h"

/**
 * flip_bits - Counts the number of bits to change to get from one number to another.
 *
 * This function takes two integers, @n and @m, and calculates the number of bits
 * that need to be changed in @n to transform it into @m. It returns the count of
 * differing bits between the two numbers.
 *
 * @n: The first number.
 * @m: The second number.
 *
 * Return: The number of bits to change between @n and @m.
 *
 * Example usage:
 * unsigned int num1 = 10; // 1010
 * unsigned int num2 = 15; // 1111
 * int result = flip_bits(num1, num2); // 2 bits need to be changed.
 * // After the call, result will be 2.
 *
 * Note: This function assumes that the numbers @n and @m are non-negative integers.
 * To avoid unexpected behavior, ensure that both numbers have the same data type
 * and that they have the same number of bits on the target platform.
 */

unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	int i, count = 0;
	unsigned long int current;
	unsigned long int exclusive = n ^ m;

	for (i = 63; i >= 0; i--)
	{
		current = exclusive >> i;
		if (current & 1)
			count++;
	}

	return (count);
}
