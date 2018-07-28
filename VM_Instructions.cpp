/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VMcanonical.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:10:43 by dzui              #+#    #+#             */
/*   Updated: 2017/12/06 16:10:45 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vm/VM.h"

// push - adds a new object of a specific type to the stack

void 	VM::push(std::string argument)
{
	std::cout << argument << std::endl;
	
//	std::vector<std::string> 	args;
//
//	std::replace_if(argument.begin(), argument.end(), [](char ch) -> bool {
//			return (ch == '(' || ch == ')');
//	}, ' ');
//	SplitString(args, argument, ' ');
//	for (auto &elem : args)
//		elem = this->lexer->RemoveSpaces(elem);
//	val_stack.push_back((factory->createOperand(FindType(args[0]), args[1])));
}

// assert - takes a value and check whether it is equal to the value in the top of the stack

void 	VM::assert(std::string argument)
{
	std::cout << argument << std::endl;
//	const IOperand				*new_one;
//	std::vector<std::string> 	args;
//
//	std::replace_if(argument.begin(), argument.end(), [](char ch) -> bool {
//		return (ch == '(' || ch == ')');
//	}, ' ');
//	SplitString(args, argument, ' ');
//	for (auto &elem : args)
//		elem = this->lexer->RemoveSpaces(elem);
//	new_one = factory->createOperand(FindType(args[0]), args[1]);
//	try
//	{
//		if (val_stack.empty()
//			|| new_one->toString() != val_stack.back()->toString())
//			throw AssertException();
//		delete (new_one);
//	}
//	catch (AssertException &e)
//	{
//		std::cout << e.what() << std::endl;
//	}
}

// sub - takes two objects from the stack and subtracts them and the result pushes back to the stack

void	VM::sub()
{
//	try
//	{
//		const IOperand *lhs;
//		const IOperand *rhs;
//
//		if (val_stack.size() < 2)
//			throw (StackException());
//		lhs = val_stack.back();
//		val_stack.pop_back();
//		rhs = val_stack.back();
//		val_stack.pop_back();
//		val_stack.push_back(*lhs - *rhs);
//	}
//	catch (StackException &e)
//	{
//		std::cout << e.what() << std::endl;
//		exit(0);
//	}
}

// div - takes two objects from the stack and devides them and the result pushes back to the stack

void	VM::div()
{
//	try
//	{
//		const IOperand *lhs;
//		const IOperand *rhs;
//
//		if (val_stack.size() < 2)
//			throw (StackException());
//		lhs = val_stack.back();
//		val_stack.pop_back();
//		rhs = val_stack.back();
//		val_stack.pop_back();
//		val_stack.push_back(*lhs / *rhs);
//	}
//	catch (StackException &e)
//	{
//		std::cout << e.what() << std::endl;
//		exit(0);
//	}
}

// mod - takes two values from the stack and performs modulus operation andt the result pushes back to the stack

void	VM::mod()
{
//	try
//	{
//		const IOperand *lhs;
//		const IOperand *rhs;
//
//		if (val_stack.size() < 2)
//			throw (StackException());
//		lhs = val_stack.back();
//		val_stack.pop_back();
//		rhs = val_stack.back();
//		val_stack.pop_back();
//		val_stack.push_back(*lhs % *rhs);
//	}
//	catch (StackException &e)
//	{
//		std::cout << e.what() << std::endl;
//		exit(0);
//	}
}

// pop - pops up the last element from the stack

void 	VM::pop()
{
//	try
//	{
//		if (val_stack.empty())
//			throw PopException();
//		val_stack.pop_back();
//	}
//	catch (PopException &e)
//	{
//		std::cout << e.what() << std::endl;
//		exit(0);
//	}
}

// dump - display the values in the stack, from the last added, to the last added

void	VM::dump() const
{
//	for (auto i = val_stack.rbegin(); i != val_stack.rend(); i++)
//		std::cout << (*i)->toString() << std::endl;
}

// add - takes two objects from a stack and add them and the resulting object pushes back in stack

void 	VM::add()
{
//	try
//	{
//		const IOperand *lhs;
//		const IOperand *rhs;
//
//		if (val_stack.size() < 2)
//			throw (StackException());
//		lhs = val_stack.back();
//		val_stack.pop_back();
//		rhs = val_stack.back();
//		val_stack.pop_back();
//		val_stack.push_back(*lhs + *rhs);
//	}
//	catch (StackException &e)
//	{
//		std::cout << e.what() << std::endl;
//		exit(0);
//	}
}

// mul - takes two objects fro, the stack and multiplies them and the resulting object push back in stack

void 	VM::mul()
{
//	try
//	{
//		const IOperand *lhs;
//		const IOperand *rhs;
//
//		if (val_stack.size() < 2)
//			throw (StackException());
//		lhs = val_stack.back();
//		val_stack.pop_back();
//		rhs = val_stack.back();
//		val_stack.pop_back();
//		val_stack.push_back(*lhs * *rhs);
//	}
//	catch (StackException &e)
//	{
//		std::cout << e.what() << std::endl;
//		exit(0);
//	}
}

// print - takes a last element from the stack and checks if it is a int8 prints it to the standard output
// else errors

void 	VM::print()
{
//	try
//	{
//		char ch;
//
//		if (val_stack.empty()
//				|| val_stack.back()->getType() != _Int8)
//			throw (PrintException());
//		ch = static_cast<char>(std::stoi(val_stack.back()->toString()));
//		std::cout << ch << std::endl;
//	}
//	catch (PrintException &e)
//	{
//		std::cout << e.what() << std::endl;
//		exit(0);
//	}
}
