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
#include <cmath>
#include "../OperandFactory/OperandFactory.h"
#include <memory>
#include <typeinfo>

template < typename T >
class Operand : public IOperand
{
private:
	
	T 								value;
	T								AssignValue();
	std::string						str_val;
	eOperandType 					type;
	eOperandType 					SpecifyType();
	
	int 							precision;
	void 							CheckOverUnderFlowOperation(T nb1, T nb2, eOperationType op) const;
	void							CheckRange() const;
	static OperandFactory 			factory_ptr;
    void                            PrintRanges(void) const;
	
public:
	
	// canonical form of a class
	
						Operand();
	explicit			Operand(std::string const &val);
						Operand(Operand const &op);
						~Operand() override;
	Operand<T>			&operator=(IOperand const &op);
	
	// methods for getting type precision, its string representation, and get type
	
	int					getPrecision(void) const override;
	eOperandType 		getType(void) const override;
	std::string const	&toString() const override;

	// operators overloading for all the mathematical operations
	
	IOperand const 		*operator+(IOperand const &rhs) const override;
	IOperand const 		*operator-(IOperand const &rhs) const override;
	IOperand const 		*operator*(IOperand const &rhs) const override;
	IOperand const 		*operator/(IOperand const &rhs) const override;
	IOperand const 		*operator%(IOperand const &rhs) const override;

	// exceptions classes

	// type overflow exception
	
	class				Overflow : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Type overflow exception");
		}

	};

	// type underflow exception
	
	class				Underflow : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Type underflow exception");
		}
	};

	// zero division exception
	
	class				ZeroDiv : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Zero division exception");
		}
	};

	// zero modulus operation exception
	
	class				ZeroMod : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Zero modulus exception");
		}
	};
	
	// out of range exception
	
	class				OutOfRange : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Out of range exception");
		}
	};
};

#include "Operand.cpp"
#include "OperandCanonical.cpp"
#include "OperandPlusOverload.cpp"
#include "OperandMinusOverload.cpp"
#include "OperandMulOverload.cpp"
#include "OperandDivOverload.cpp"
#include "OperandModulOverload.cpp"

#endif
