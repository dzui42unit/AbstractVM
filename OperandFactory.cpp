/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:38:35 by dzui              #+#    #+#             */
/*   Updated: 2017/11/28 15:38:36 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "OperandFactory.h"

// constructor that initializes the vector of pointers to a member function;

OperandFactory::OperandFactory()
{
	vec.push_back((&OperandFactory::createInt8));
	vec.push_back((&OperandFactory::createInt16));
	vec.push_back((&OperandFactory::createInt32));
	vec.push_back((&OperandFactory::createFloat));
	vec.push_back((&OperandFactory::createDouble));
}

// creates a new operand taking into account its type

IOperand const	*OperandFactory::createOperand(eOperandType type, std::string const &value) const
{
	IOperand const *new_obj;

	new_obj = dynamic_cast<const IOperand *>((this->*vec[type])(value));
	return (new_obj);
}

// destructor

OperandFactory::~OperandFactory()
{

}

// copy constructor

OperandFactory::OperandFactory(OperandFactory const &of)
{
	for (auto i : of.vec)
		vec.push_back(i);
}

// assignment operator overloading

OperandFactory& OperandFactory::operator=(OperandFactory const &of)
{
	vec.clear();
	for (auto i : of.vec)
		vec.push_back(i);
	return (*this);
}

// method that creates Operand<char> object

IOperand	const* OperandFactory::createInt8(std::string const &value) const
{
	IOperand	*res;

	res = new Operand<char>(value);
	return (res);
}

// method that creates Operand<short> object

IOperand	const* OperandFactory::createInt16(std::string const &value) const
{
	IOperand	*res;

	res = new Operand<short>(value);
	return (res);
}

// method that creates Operand<int> object

IOperand	const* OperandFactory::createInt32(std::string const &value) const
{
	IOperand	*res;

	res = new Operand<int>(value);
	return (res);
}

// method that creates Operand<float> object

IOperand	const* OperandFactory::createFloat(std::string const &value) const
{
	IOperand	*res;

	res = new Operand<float>(value);
	return (res);
}

// method that creates Operand<double> object

IOperand	const* OperandFactory::createDouble(std::string const &value) const
{
	IOperand	*res;

	res = new Operand<double>(value);
	return (res);
}