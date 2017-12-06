/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandModulOverload.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 18:59:37 by dzui              #+#    #+#             */
/*   Updated: 2017/11/28 18:59:38 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Operand.h"

template 			< typename T>
IOperand const 		*Operand<T>::operator%(IOperand const &rhs) const
{
	int 			type;
	const IOperand	*new_obj;

	new_obj = nullptr;
	type = getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision();
	if (type == _Int8)
	{
		char lhs_val;
		char rhs_val;

		try
		{
			lhs_val = static_cast<char>(std::stoi(this->toString()));
			rhs_val = static_cast<char>(std::stoi(rhs.toString()));
			if (rhs_val == 0)
				throw (ZeroMod());
			Operand<T>::CheckOverUnderFlowOperation(lhs_val, rhs_val, Mod);
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
		catch (ZeroMod &zd)
		{
			std::cout << zd.what() << std::endl;
			exit(0);
		}
		new_obj = factory_ptr.createOperand(_Int8, std::to_string(lhs_val % rhs_val));
	}
	if (type == _Int16)
	{
		short lhs_val;
		short rhs_val;

		try
		{
			lhs_val = static_cast<short>(std::stoi(this->toString()));
			rhs_val = static_cast<short>(std::stoi(rhs.toString()));
			Operand<T>::CheckOverUnderFlowOperation(lhs_val, rhs_val, Mod);
			if (rhs_val == 0)
				throw (ZeroMod());
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
		catch (ZeroMod &zd)
		{
			std::cout << zd.what() << std::endl;
			exit(0);
		}
		new_obj = factory_ptr.createOperand(_Int16, std::to_string(lhs_val % rhs_val));
	}
	if (type == _Int32)
	{
		int lhs_val;
		int rhs_val;

		try
		{
			lhs_val = std::stoi(this->toString());
			rhs_val = std::stoi(rhs.toString());
			Operand<T>::CheckOverUnderFlowOperation(lhs_val, rhs_val, Mod);
			if (rhs_val == 0)
				throw (ZeroMod());
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
		catch (ZeroMod &zd)
		{
			std::cout << zd.what() << std::endl;
			exit(0);
		}
		new_obj = factory_ptr.createOperand(_Int32, std::to_string(lhs_val % rhs_val));
	}
	if (type == _Float)
	{
		float lhs_val;
		float rhs_val;

		try
		{
			lhs_val = std::stof(this->toString());
			rhs_val = std::stof(rhs.toString());
			Operand<T>::CheckOverUnderFlowOperation(lhs_val, rhs_val, Mod);
			if (rhs_val == 0)
				throw (ZeroMod());
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
		catch (ZeroMod &zd)
		{
			std::cout << zd.what() << std::endl;
			exit(0);
		}
		new_obj = factory_ptr.createOperand(_Float, std::to_string(fmodf(lhs_val, rhs_val)));
	}
	if (type == _Double)
	{
		double lhs_val;
		double rhs_val;

		try
		{
			lhs_val = std::stod(this->toString());
			rhs_val = std::stod(rhs.toString());
			Operand<T>::CheckOverUnderFlowOperation(lhs_val, rhs_val, Mod);
			if (rhs_val == 0)
				throw (ZeroMod());
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
		catch (ZeroMod &zd)
		{
			std::cout << zd.what() << std::endl;
			exit(0);
		}
		new_obj = factory_ptr.createOperand(_Double, std::to_string(fmod(lhs_val, rhs_val)));
	}
	return (new_obj);
}
