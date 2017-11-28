
#ifndef ABSTRACTVM_EXCEPTIONS_H
#define ABSTRACTVM_EXCEPTIONS_H

#include <exception>

class				Overflow : public std::exception
{
public:
	const char 	*what() const throw() override;
};

class				Underflow : public std::exception
{
public:
	const char 	*what() const throw() override;
};

class				ZeroDiv : public std::exception
{
public:
	const char 	*what() const throw() override;
};

class				ZeroMod : public std::exception
{
public:
	const char 	*what() const throw() override;
};

#endif //ABSTRACTVM_EXCEPTIONS_H
