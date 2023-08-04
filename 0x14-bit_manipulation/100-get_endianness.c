#include "main.h"

/**
 * get_endianness - Checks if a machine is little or big endian.
 * Return: 0 if the machine is big endian, 1 if the machine is little endian.
 *
 */

int get_endianness(void)
{
	unsigned int i = 1;
	char *c = (char *) &i;

	return (*c);
}
