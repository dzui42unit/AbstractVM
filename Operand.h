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
	void 				CheckOverUnderFlowOperation(T nb1, T nb2, eOperationType op) const;
public:
						Operand();
	explicit			Operand(std::string const &val);
						Operand(Operand const &op);
						~Operand() override;
	Operand<T>			&operator=(IOperand const &op);

	eOperandType 		getType(void) const override;
	int					getPrecision(void) const override;
	std::string const	&toString() const override;

	IOperand const 		*operator+(IOperand const &rhs) const override;
	IOperand const 		*operator-(IOperand const &rhs) const override;
	IOperand const 		*operator*(IOperand const &rhs) const override;
	IOperand const 		*operator/(IOperand const &rhs) const override;
	IOperand const 		*operator%(IOperand const &rhs) const override;

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

	class				OutOfRange : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Out of range exception occurred.");
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
