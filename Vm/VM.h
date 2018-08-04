/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:21:29 by dzui              #+#    #+#             */
/*   Updated: 2017/11/28 19:21:32 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ABSTRACTVM_VM_H
#define ABSTRACTVM_VM_H

#include <memory>
#include <utility>
#include <fstream>
#include <regex>
#include <exception>

#include "../Operand/Operand.h"
#include "../OperandFactory/OperandFactory.h"
#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"

class 													VM
{
private:

	// stores all the errors

	std::vector<std::string>							errors;

	// stores input data and a stack of values, tokens produced by lexer

	std::vector<std::string>							input_file;
	std::vector<IOperand const *>						stack;
	std::vector<std::pair<std::string, std::string>>	tokens;

	// pointers to other classes such as Factory class - produces Operands
	// Lexer - performs lexical analysis and returns set of tokens
	// Parser - performs check of the language rules and and pushes values to the stack
	
	std::shared_ptr<Lexer>								lexer;
	std::shared_ptr<Parser>								parser;
	std::shared_ptr<OperandFactory>						factory;

    std::string                                         removeZero(const std::string &str) const;

public:

	// constructors (default, copy, copy assignment operator)

														VM() = delete;
	explicit											VM(std::vector<std::string> inp_f);
	explicit											VM(std::string f_name);
														~VM();
														VM(VM const &vm);
	VM 													&operator=(VM const &vm);

	// functions for lexical analysis and a parser

	void												LexicalAnalysis(void);
	void												Parsing(void);
    void                                                PrintTokens(void) const;

	// instruction set

	void												push(const std::string &argument);
	void												dump() const;
	void												add();
	void												pop();
	void												mul();
	void												assert(std::string argument);
	void												sub();
	void												div();
	void												mod();
	void												print();

	// some stuff for the parser, it will be removed from here

	void												RunInstructions();
	eOperandType 										FindType(std::string const &str) const;

	// some exceptions, that will be moved to Exception.h/Exception.cpp files

	class				NoExit : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Exit exception: \"exit\" instruction omitted.");
		}
	};

	class				SyntaxLexicalError : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Lexical / Syntax errors are in the file.");
		}
	};

	class				PopException : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Pop exception: stack is already empty, pop can not be executed.");
		}
	};

	class				AssertException : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Assert exception: instruction is not true.");
		}
	};

	class				StackException : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Stack exception: less elements than it needed to execute instruction.");
		}
	};

	class				PrintException : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Print exception: the value is not a int8 type.");
		}
	};

	class				NoSuchFileException : public std::exception
	{
	public:
		const char *what() const throw() override
		{
			return ("Input file doesn't exist, no such file.");
		}
	};
};

#endif //ABSTRACTVM_VM_H
