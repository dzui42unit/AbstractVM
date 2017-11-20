/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:07:26 by dzui              #+#    #+#             */
/*   Updated: 2017/11/20 17:07:27 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_IOPERAND_H
#define ABSTRACTVM_IOPERAND_H

#include <string>
#include <iostream>
#include <exception>


enum eOperandType { _Int8, _Int16, _Int32, _Float, _Double };
enum eOperandPrec { _Int8Pr, _Int16Pr, _Int32Pr, _FloatPr, _DoublePr };

class 							IOperand
{
public:
	virtual int 				getPrecision(void) const = 0;				// precision of the type instance
	virtual eOperandType 		getType(void) const = 0;					// get a type of the instance

	virtual IOperand const *	operator+(IOperand const &rhs) const = 0;	// sum
	virtual IOperand const *	operator-(IOperand const &rhs) const = 0;	// difference
	virtual IOperand const *	operator*(IOperand const &rhs) const = 0;	// product
	virtual IOperand const *	operator/(IOperand const &rhs) const = 0;	// quotient
	virtual IOperand const *	operator%(IOperand const &rhs) const = 0;	// modulo

	virtual std::string const 	&toString(void) const = 0;					// string representation on an instance

	virtual 					~IOperand(void) {}							// destructor


};

#endif //ABSTRACTVM_IOPERAND_H
