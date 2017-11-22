/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandCanonical.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:49:06 by dzui              #+#    #+#             */
/*   Updated: 2017/11/22 19:49:09 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.h"

// copy constructor

template 			< typename T >
Operand<T>::Operand(Operand const &op)
{
	value = op.value;
	precision = op.precision;
	type = op.type;
	str_val = op.str_val;
}

// destructor

template 			< typename T >
Operand<T>::~Operand()
{

}

// assignment operator overloading

template 			< typename T >
Operand<T>			&Operand<T>::operator=(IOperand const &op)
{
	eOperandType 	type;

	type = getType() > op.getType() ? getType() : op.getType();
	std::cout << type << std::endl;
	if (type == _Int8)
	{
		this->type = op.getType();
		this->str_val = op.toString();
		this->precision = op.getPrecision();
		this->value = static_cast<char>(std::stoi(op.toString()));
	}
	if (type == _Int16)
	{
		this->type = op.getType();
		this->str_val = op.toString();
		this->precision = op.getPrecision();
		this->value = static_cast<short>(std::stoi(op.toString()));
	}
	if (type == _Int32)
	{
		this->type = op.getType();
		this->str_val = op.toString();
		this->precision = op.getPrecision();
		this->value = std::stoi(op.toString());
	}
	if (type == _Float)
	{
		this->type = op.getType();
		this->str_val = op.toString();
		this->precision = op.getPrecision();
		this->value = static_cast<float>(std::stoi(op.toString()));
	}
	if (type == _Double)
	{
		this->type = op.getType();
		this->str_val = op.toString();
		this->precision = op.getPrecision();
		this->value = static_cast<double>(std::stoi(op.toString()));
	}
	return (*this);
}

// empty constructor

template 			< typename T >
					Operand<T>::Operand()
{
	type = SpecifyType();
	str_val = "";
	value = 0;
	precision = type;
}

// constructor that takes a string that will represent a value of an instance

template 			< typename T >
					Operand<T>::Operand(std::string const &val)
{
	str_val = val;
	type = Operand<T>::SpecifyType();
	value = Operand<T>::AssignValue();
	str_val = std::to_string(value);
	precision = static_cast<int>(type);
}
