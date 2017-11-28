
#ifndef ABSTRACTVM_EXCEPTIONS_H
#define ABSTRACTVM_EXCEPTIONS_H

#include <exception>

class				Overflow : public std::exception
{
public:
	const char 	*what() const throw() override
	{
		return ("Type Overflow occurred.");
	}
};

class				Underflow : public std::exception
{
public:
	const char 	*what() const throw() override
	{
		return ("Type Underflow occurred.");
	}
};

class				ZeroDiv : public std::exception
{
public:
	const char 	*what() const throw() override
	{
		return ("Zero as a second argument in division operation occurred.");
	}
};

class				ZeroMod : public std::exception
{
public:
	const char 	*what() const throw() override
	{
		return ("Zero as a second argument in modulus operation occurred.");
	}
};

#endif //ABSTRACTVM_EXCEPTIONS_H
