/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:38:48 by dzui              #+#    #+#             */
/*   Updated: 2017/11/28 15:38:52 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_OPERANDFACTORY_H
#define ABSTRACTVM_OPERANDFACTORY_H

#include "IOperand.h"

class								OperandFactory
{
public:

	typedef IOperand const 			*(OperandFactory::*create_func)(std::string const &val) const;			// typedef for a member function of a class

									OperandFactory();														// constructor
									~OperandFactory();														// destructor
									OperandFactory(OperandFactory const &of);								// copy constructor
	OperandFactory					&operator=(OperandFactory const &of);									// assignment operator overloading
	IOperand	const				*createOperand(eOperandType type, std::string const & value) const;		// returns an object of a specified type

private:

	create_func 					*create_ptrs;															// stores pointers to a functions
	int 							ptrs_nb;																// number of pointers to a function

	IOperand	const				*createInt8(std::string const & value) const;							// creates a Operand<char> object
	IOperand	const 				*createInt16(std::string const & value) const;							// creates a Operand<short> object
	IOperand	const				*createInt32(std::string const & value) const;							// creates a Operand<int> object
	IOperand	const				*createFloat(std::string const & value) const;							// creates a Operand<float> object
	IOperand	const				*createDouble(std::string const & value) const;							// creates a Operand<double> object
};

#endif
