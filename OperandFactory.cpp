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

OperandFactory::OperandFactory() : ptrs_nb(5)
{

	create_ptrs = new create_func[ptrs_nb];

	create_ptrs[0] = &OperandFactory::createInt8;
	create_ptrs[1] = &OperandFactory::createInt16;
	create_ptrs[2] = &OperandFactory::createInt32;
	create_ptrs[3] = &OperandFactory::createFloat;
	create_ptrs[4] = &OperandFactory::createDouble;
}

// creates a new operand taking into account its type

IOperand const	*OperandFactory::createOperand(eOperandType type, std::string const &value) const
{
	IOperand const *new_obj;

	new_obj = dynamic_cast<const IOperand *>((this->*create_ptrs[type])(value));
	return (new_obj);
}

// destructor

OperandFactory::~OperandFactory()
{
	delete  create_ptrs;
}

// copy constructor

OperandFactory::OperandFactory(OperandFactory const &of)
{
	ptrs_nb = of.ptrs_nb;
	create_ptrs = new create_func[ptrs_nb];
	for (int i = 0; i < ptrs_nb; i++)
		create_ptrs[i] = of.create_ptrs[i];
}

// assignment operator overloading

OperandFactory& OperandFactory::operator=(OperandFactory const &of)
{
	delete create_ptrs;
	ptrs_nb = of.ptrs_nb;
	create_ptrs = new create_func[ptrs_nb];
	for (int i = 0; i < ptrs_nb; i++)
		create_ptrs[i] = of.create_ptrs[i];
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