/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int8.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:59:24 by dzui              #+#    #+#             */
/*   Updated: 2017/11/20 17:59:27 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Int8.h"

int 			Int8::getValue() const
{
	return (value);
}

IOperand const	*Int8::operator+(IOperand const &rhs) const
{
	int 		type;
	IOperand	*new_obj;

	type = getType() > rhs.getType() ? getType() : rhs.getType();
	try
	{
		if (type == _Int8)
		{
			std::cout << "_Int8\n";
			new_obj = new Int8((dynamic_cast<Int8 const &>(*this).getValue() + dynamic_cast<Int8 const &>(rhs).getValue()));
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (new_obj);
}

IOperand const	*Int8::operator-(IOperand const &rhs) const
{
	int type;

	type = getType() > rhs.getType() ? getType() : rhs.getType();
	std::cout << "RESULTING TYPE IS: " << type << std::endl;

	try
	{
		dynamic_cast<Int8 const &>(rhs);
	}
	catch (std::exception &e)
	{
		std::cout << "FUCK!\n";
	}
	return (this);

}

IOperand const	*Int8::operator/(IOperand const &rhs) const
{
	int type;

	type = getType() > rhs.getType() ? getType() : rhs.getType();
	std::cout << "RESULTING TYPE IS: " << type << std::endl;

	try
	{
		dynamic_cast<Int8 const &>(rhs);
	}
	catch (std::exception &e)
	{
		std::cout << "FUCK!\n";
	}
	return (this);
}

IOperand const	*Int8::operator*(IOperand const &rhs) const
{
	int type;

	type = getType() > rhs.getType() ? getType() : rhs.getType();
	std::cout << "RESULTING TYPE IS: " << type << std::endl;

	try
	{
		dynamic_cast<Int8 const &>(rhs);
	}
	catch (std::exception &e)
	{
		std::cout << "FUCK!\n";
	}
	return (this);
}

IOperand const	*Int8::operator%(IOperand const &rhs) const
{
	int type;

	type = getType() > rhs.getType() ? getType() : rhs.getType();
	std::cout << "RESULTING TYPE IS: " << type << std::endl;

	try
	{
		if (type == _Int8)
		{
			dynamic_cast<Int8 const &>(rhs);

		}
	}
	catch (std::exception &e)
	{
		std::cout << "FUCK!\n";
	}
	return (this);
}

Int8::Int8(int nb) : value(nb), type(_Int8), prec(_Int8Pr), str_val(std::to_string(value))
{

}

Int8::Int8(const Int8 &rlh)
{
	value = rlh.value;
	type = rlh.type;
	prec = rlh.prec;
	str_val = rlh.str_val;
}

Int8	&Int8::operator=(IOperand const &rhs)
{
	value = dynamic_cast<Int8 const &>(rhs).value;
	type = dynamic_cast<Int8 const &>(rhs).type;
	prec = dynamic_cast<Int8 const &>(rhs).prec;
	str_val = dynamic_cast<Int8 const &>(rhs).str_val;
	return (*this);
}

eOperandType	Int8::getType() const
{
	return (type);
}

std::string const	&Int8::toString() const
{
	return (str_val);
}

Int8::~Int8()
{

}

int 	Int8::getPrecision() const
{
	return (prec);
}