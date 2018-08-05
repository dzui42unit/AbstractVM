/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VMcanonical.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:10:43 by dzui              #+#    #+#             */
/*   Updated: 2018/08/05 12:55:01 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VM.h"

// push - adds a new object of a specific type to the stack

void 	VM::push(const std::string &argument)
{
    std::pair<std::string, std::string> 	args;

    args = this->lexer->SplitString(argument, ' ');
	stack.push_back((factory->createOperand(FindType(args.first), args.second)));
}

// assert - takes a value and check whether it is equal to the value in the top of the stack

void 	VM::assert(std::string argument)
{
    std::pair<std::string, std::string> 	args;
    const IOperand				*new_one;

    args = this->lexer->SplitString(argument, ' ');
	new_one = factory->createOperand(FindType(args.first), args.second);
    if (stack.empty() || new_one->toString() != stack.back()->toString())
        throw AssertException();
    delete (new_one);
}

// sub - takes two objects from the stack and subtracts them and the result pushes back to the stack

void	VM::sub()
{
    const IOperand *lhs;
    const IOperand *rhs;

    if (stack.size() < 2)
        throw (StackException());
    rhs = stack.back();
    stack.pop_back();
    lhs = stack.back();
    stack.pop_back();
    stack.push_back(*lhs - *rhs);
}

// div - takes two objects from the stack and divides them and the result pushes back to the stack

void	VM::div()
{
	const IOperand *lhs;
	const IOperand *rhs;

	if (stack.size() < 2)
		throw (StackException());
	rhs = stack.back();
	stack.pop_back();
	lhs = stack.back();
	stack.pop_back();
	stack.push_back(*lhs / *rhs);
}

// mod - takes two values from the stack and performs modulus operation andt the result pushes back to the stack

void	VM::mod()
{
    const IOperand *lhs;
    const IOperand *rhs;

    if (stack.size() < 2)
        throw (StackException());
    rhs = stack.back();
    stack.pop_back();
    lhs = stack.back();
    stack.pop_back();
    stack.push_back(*lhs % *rhs);
}

// pop - pops up the last element from the stack

void 	VM::pop()
{
    if (stack.empty())
        throw PopException();
    stack.pop_back();
}

// dump - display the values in the stack, from the last added, to the last added

void	VM::dump() const
{
	for (auto i = stack.rbegin(); i != stack.rend(); i++)
    {
        if ((*i)->toString().find_first_of(".") != std::string::npos)
            std::cout << removeZero((*i)->toString()) << std::endl;
        else
            std::cout << (*i)->toString() << std::endl;
    }
}

// add - takes two objects from a stack and add them and the resulting object pushes back in stack

void 	VM::add()
{
    const IOperand *lhs;
    const IOperand *rhs;

    if (stack.size() < 2)
        throw (StackException());
    rhs = stack.back();
    stack.pop_back();
    lhs = stack.back();
    stack.pop_back();
    stack.push_back(*lhs + *rhs);
}

// mul - takes two objects fro, the stack and multiplies them and the resulting object push back in stack

void 	VM::mul()
{
    const IOperand *lhs;
    const IOperand *rhs;

    if (stack.size() < 2)
        throw (StackException());
    rhs = stack.back();
    stack.pop_back();
    lhs = stack.back();
    stack.pop_back();
    stack.push_back(*lhs * *rhs);
}

// print - takes a last element from the stack and checks if it is a int8 prints it to the standard output
// else errors

void 	VM::print()
{
    char ch;

    if (stack.empty() || stack.back()->getType() != _Int8)
        throw (PrintException());
    ch = static_cast<char>(std::stoi(stack.back()->toString()));
    std::cout << ch << std::endl;
}
