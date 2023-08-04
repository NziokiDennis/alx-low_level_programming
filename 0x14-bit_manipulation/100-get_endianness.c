#include "main.h"

/**
 * get_endianness - Checks if a machine is little or big endian.
 *
 * This function determines the endianness of the machine it is executed on.
 * It checks whether the machine stores multi-byte data with the most significant byte first
 * (big endian) or the least significant byte first (little endian).
 *
 * Return: 0 if the machine is big endian, 1 if the machine is little endian.
 *
 * Example usage:
 * int endian_type = get_endianness(); // Get the endianness of the machine.
 * // If the machine is little endian, endian_type will be 1.
 * // If the machine is big endian, endian_type will be 0.
 *
 * Note: This function assumes that the machine uses either little or big endian
 * representation for multi-byte data. It may not work correctly on machines with
 * other types of endianness, such as mixed-endian systems.
 */

int get_endianness(void)
{
	unsigned int i = 1;
	char *c = (char *) &i;

	return (*c);
}
