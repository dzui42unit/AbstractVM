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
#include <iomanip>
#include <limits.h>
#include <algorithm>

template < typename  T>
OperandFactory Operand<T>::factory_ptr;

// check if the overflow can take place

template 			< typename T >
void 				Operand<T>::CheckOverUnderFlowOperation(T nb1, T nb2, eOperationType op) const
{
	if (op == Add)
	{
		if (nb1 > 0)
		{
			if (std::numeric_limits<T>::max() - nb1 < nb2)
				throw (Overflow());
		}
		else
		{
			if (std::numeric_limits<T>::min() - nb1 >= nb2)
				throw (Underflow());
		}
	}
	if (op == Sub)
	{
		if (nb2 < 0)
		{
			if (std::numeric_limits<T>::max() + nb2 < nb1)
				throw (Overflow());
		}
		else
		{
			if (std::numeric_limits<T>::min() + nb2 > nb1)
				throw (Underflow());
		}
	}
	if (op == Mul)
	{
		if (nb1 == -1 && (nb2 == std::numeric_limits<T>::min()))
			throw (Underflow());
		if (nb2 == -1 && (nb1 == std::numeric_limits<T>::min()))
			throw (Underflow());
		if (nb1 > std::numeric_limits<T>::max() / nb2)
			throw (Overflow());
		if (nb1 < std::numeric_limits<T>::min() / nb2)
			throw (Underflow());
	}
	if (op == Div)
	{
		if (nb1 == -1 && nb2 == std::numeric_limits<T>::min())
			throw (Underflow());
		if (nb2 == -1 && nb1 == std::numeric_limits<T>::min())
			throw (Underflow());
	}
	if (op == Mod)
	{
		if (nb1 == -1 && nb2 == std::numeric_limits<T>::min())
			throw (Underflow());
		if (nb2 == -1 && nb1 == std::numeric_limits<T>::min())
			throw (Underflow());
	}
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

// check whether the number fits in range of its type

template < typename T >
void				Operand<T>::CheckRange() const
{
	if (type == _Int8)
	{
		if (std::numeric_limits<char>::lowest() > std::stoll(str_val))
			throw Underflow();
		if (std::numeric_limits<char>::max() < std::stoll(str_val))
			throw Overflow();
	}
	if (type == _Int16)
	{
		if (std::numeric_limits<short>::lowest() > std::stoll(str_val))
			throw Underflow();
		if (std::numeric_limits<short>::max() < std::stoll(str_val))
			throw Overflow();
	}
	if (type == _Int32)
	{
		if (std::numeric_limits<int>::lowest() > std::stoll(str_val))
			throw Underflow();
		if (std::numeric_limits<int>::max() < std::stoll(str_val))
			throw Overflow();
	}
	if (type == _Float)
	{
		if (std::numeric_limits<float>::lowest() > std::stold(str_val))
			throw Underflow();
		if (std::numeric_limits<float>::max() < std::stold(str_val))
			throw Overflow();
	}
	if (type == _Double)
	{
		if (std::numeric_limits<double>::lowest() > std::stold(str_val))
			throw Underflow();
		if (std::numeric_limits<double>::max() < std::stold(str_val))
			throw Overflow();
	}
}

template 		    < typename T >
void                Operand<T>::PrintRanges(void) const
{
    std::cout.setf(std::ios::fixed);
    std::cout << "CHAR_MIN: " << static_cast<int>(std::numeric_limits<char>::lowest()) << std::endl;
    std::cout << "CHAR_MAX: " << static_cast<int>(std::numeric_limits<char>::max()) << std::endl << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout << "SHORT_MIN: " << std::numeric_limits<short>::lowest() << std::endl;
    std::cout << "SHORT_MAX: " << std::numeric_limits<short>::max() << std::endl << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout << "INT_MIN: " << std::numeric_limits<int>::lowest() << std::endl;
    std::cout << "INT_MAX: " << std::numeric_limits<int>::max() << std::endl << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout << "FLOAT_MIN: " << std::numeric_limits<float>::lowest() << std::endl;
    std::cout << "FLOAT_MAX: " << std::numeric_limits<float>::max() << std::endl << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout << "DOUBLE_MIN: " << std::numeric_limits<double>::lowest() << std::endl;
    std::cout << "DOUBLE_MAX: " << std::numeric_limits<double>::max() << std::endl << std::endl;
}

// assigns a value taking into account its type

template 			< typename T >
T 					Operand<T>::AssignValue()
{
	T result = 0.0;
    char    under_over_flow = 2;

    if (this->str_val[0] == '-')
        under_over_flow = 0;
    if (this->str_val[0] != '-')
        under_over_flow = 1;
    try
    {
        if (this->type == _Int8 || this->type == _Int16
            || this->type == _Int32)
            std::stoi(this->str_val);
        if (this->type == _Float)
            std::stof(this->str_val);
        if (this->type == _Double)
            std::stod(this->str_val);
    }
    catch (std::exception &e)
    {
        if (under_over_flow == 0)
                throw (Underflow());
        if (under_over_flow == 1)
                throw (Overflow());
    }
    CheckRange();

//	length = str_val.length();
//	if (str_val[0] == '-')
//		length--;
//	if (length > 19)
//		throw (OutOfRange());
//	if (type == _Int8)
//		res = static_cast<char>(std::stoll(str_val));
//	if (type == _Int16)
//		res = static_cast<short>(std::stoll(str_val));
//	if (type == _Int32)
//		res = static_cast<int>(std::stoll(str_val));
//	if (type == _Float)
//		res = static_cast<float>(std::stold(str_val));
//	if (type == _Double)
//		res = static_cast<double>(std::stold(str_val));
	return (result);
}
