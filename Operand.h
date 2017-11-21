/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:32:56 by dzui              #+#    #+#             */
/*   Updated: 2017/11/21 15:32:58 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_OPERAND_H
#define ABSTRACTVM_OPERAND_H

#include "IOperand.h"

template < typename T >
class Operand : public IOperand
{
private:
	T 					value;
	int 				precision;
	eOperandType 		type;
	std::string			str_val;
	eOperandType 		SpecifyType();
	T					AssignValue();
	int 				CheckOverUnderFlowAdd(T nb1, T nb2) const;
public:
						Operand();
	explicit			Operand(std::string const &val);
						Operand(Operand const &op);
						~Operand();
	IOperand			&operator=(IOperand const &op);

	eOperandType 		getType(void) const override;
	int					getPrecision(void) const override;
	T 					getValue(void) const;
	std::string const	&toString() const override;

	IOperand const 		*operator+(IOperand const &rhs) const override;
	IOperand const 		*operator-(IOperand const &rhs) const override;
	IOperand const 		*operator*(IOperand const &rhs) const override;
	IOperand const 		*operator/(IOperand const &rhs) const override;
	IOperand const 		*operator%(IOperand const &rhs) const override;

	class				Overflow : public std::exception
	{
	public:
		virtual const char 	*what() const throw()
		{
			return ("Type Overflow occurred.");
		}
	};

	class				Underflow : public std::exception
	{
	public:
		virtual const char 	*what() const throw()
		{
			return ("Type Underflow occurred.");
		}
	};
};

/*******************************************************************/

template 			< typename T >
int 				Operand<T>::CheckOverUnderFlowAdd(T nb1, T nb2) const
{
	if (nb1 >= 0)
	{
		if (std::numeric_limits<T>::max() - nb1 < nb2)
			return (1);
	}
	else
	{
		if (std::numeric_limits<T>::min() - nb1 > nb2)
			return (2);
	}
	return (0);
}

template 			< typename T >
IOperand const 		*Operand<T>::operator+(IOperand const &rhs) const
{
	int 			type;
	int 			exc;
	IOperand		*new_obj;

	type = getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision();
	if (type == _Int8)
	{
		char lhs_val;
		char rhs_val;

		lhs_val = dynamic_cast<Operand<char> const &>(*this).getValue();
		rhs_val = dynamic_cast<Operand<char> const &>(rhs).getValue();
		exc =CheckOverUnderFlowAdd(lhs_val, rhs_val);
		try
		{
			if (exc == 1)
				throw Overflow();
			if (exc == 2)
				throw Underflow();
		}
		catch (Underflow &uf)
		{
			std::cout << uf.what() << std::endl;
			exit(0);
		}
		catch (Overflow &of)
		{
			std::cout << of.what() << std::endl;
			exit(0);
		}
		new_obj = new Operand<char>(std::to_string(lhs_val + rhs_val));
	}
	if (type == _Int16)
	{
		short lhs_val;
		short rhs_val;

		lhs_val = dynamic_cast<Operand<short > const &>(*this).getValue();
		rhs_val = dynamic_cast<Operand<short> const &>(rhs).getValue();
		exc =CheckOverUnderFlowAdd(lhs_val, rhs_val);
		try
		{
			if (exc == 1)
				throw Overflow();
			if (exc == 2)
				throw Underflow();
		}
		catch (Underflow &uf)
		{
			std::cout << uf.what() << std::endl;
			exit(0);
		}
		catch (Overflow &of)
		{
			std::cout << of.what() << std::endl;
			exit(0);
		}
		new_obj = new Operand<short>(std::to_string(lhs_val + rhs_val));
	}
	return (new_obj);
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


/*******************************************************************/

// returns a value of an instance as a string

template 			< typename T >
std::string	const	&Operand<T>::toString() const
{
	return (str_val);
}

// returns the value of the instance

template 			< typename T >
T 					Operand<T>::getValue() const
{
	return (value);
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

/*******************************************************************/

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
IOperand			&Operand<T>::operator=(IOperand const &op)
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
	type = SpecifyType();
	value = AssignValue();
	precision = static_cast<int>(type);
}

/*******************************************************************/

#endif
