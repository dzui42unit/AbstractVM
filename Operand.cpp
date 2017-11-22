/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:02:39 by dzui              #+#    #+#             */
/*   Updated: 2017/11/22 19:02:42 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.h"

template 			< typename T >
int 				Operand<T>::CheckOverUnderFlowOperation(T nb1, T nb2, char op) const
{
	if (op == '+')
	{
		if (nb1 > 0)
		{
			if (std::numeric_limits<T>::max() - nb1 < nb2)
				return (1);
		}
		else
		{
			if (std::numeric_limits<T>::min() - nb1 > nb2)
				return (2);
		}
	}
	if (op == '-')
	{
		if (nb1 < 0)
		{
			if (std::numeric_limits<T>::max() + nb1 < nb2)
				return (1);
		}
		else
		{
			if (std::numeric_limits<T>::min() + nb1 > nb2)
				return (2);
		}
	}
	if (op == '*')
	{
		if (nb1 > std::numeric_limits<T>::max() / nb2)
			return (1);
		if (nb1 < std::numeric_limits<T>::min() / nb2)
			return (2);
		if (nb1 == -1 && (nb2 == std::numeric_limits<T>::min()))
			return (1);
		if (nb2 == -1 && (nb1 == std::numeric_limits<T>::min()))
			return (1);
	}
	if (op == '/')
	{
		if (nb1 == -1 && nb2 == std::numeric_limits<T>::min())
			return (1);
		if (nb2 == -1 && nb1 == std::numeric_limits<T>::min())
			return (1);
	}
	return (0);
}

template 			< typename T>
IOperand const 		*Operand<T>::operator-(IOperand const &rhs) const
{
	eOperandType 	type;
	IOperand		*new_obj;

	return (new_obj);
}

template 			< typename T>
IOperand const 		*Operand<T>::operator/(IOperand const &rhs) const
{
	eOperandType 	type;
	IOperand		*new_obj;

	return (new_obj);
}

template 			< typename T>
IOperand const 		*Operand<T>::operator*(IOperand const &rhs) const
{
	eOperandType 	type;
	IOperand		*new_obj;

	return (new_obj);
}

template 			< typename T>
IOperand const 		*Operand<T>::operator%(IOperand const &rhs) const
{
	eOperandType 	type;
	IOperand		*new_obj;

	return (new_obj);
}

// returns a value of an instance as a string

template 			< typename T >
std::string	const	&Operand<T>::toString() const
{
	return (str_val);
}

// returns the precision of the instance

template 			< typename T >
int 				Operand<T>::getPrecision() const
{
	return (precision);
}

// specifies one of the types of an instance (listed in the eOpetandType)

template 			< typename T >
eOperandType 		Operand<T>::SpecifyType()
{
	eOperandType res;

	if (typeid(T).name() == typeid(char).name())
		res = _Int8;
	if (typeid(T).name() == typeid(short).name())
		res = _Int16;
	if (typeid(T).name() == typeid(int).name())
		res = _Int32;
	if (typeid(T).name() == typeid(float).name())
		res = _Float;
	if (typeid(T).name() == typeid(double).name())
		res = _Double;
	return (res);
}

// returns one of the types (listed in the eOpetandType)

template 			< typename T >
eOperandType 		Operand<T>::getType() const
{
	return (type);
}

// assigns a value taking inro account its type

template 			< typename T >
T 					Operand<T>::AssignValue()
{
	T res;

	if (type == _Int8)
		res = static_cast<char>(std::stoi(str_val));
	if (type == _Int16)
		res = static_cast<short>(std::stoi(str_val));
	if (type == _Int32)
		res = std::stoi(str_val);
	if (type == _Float)
		res = std::stof(str_val);
	if (type == _Double)
		res = std::stod(str_val);
	return (res);
}
