
#include "Exceptions.h"


const char 	*Overflow::what() const throw()
{
	return ("Type Overflow occurred.");
}

const char 	*Underflow::what() const throw()
{
	return ("Type Underflow occurred.");
}

const char 	*ZeroDiv::what() const throw()
{
	return ("Zero as a second argument in division operation occurred.");
}

const char 	*ZeroMod::what() const throw()
{
	return ("Zero as a second argument in modulus operation occurred.");
}