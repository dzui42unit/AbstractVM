/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:21:17 by dzui              #+#    #+#             */
/*   Updated: 2017/11/28 19:21:18 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "VM.h"

// constructor that takes a vector of strings as an input

VM::VM(std::vector<std::string> inp_f)
{
	this->input_file = inp_f;
	this->factory = std::make_shared<OperandFactory>(OperandFactory());
	this->lexer = std::make_shared<Lexer>(Lexer(this->input_file));
	this->parser = std::make_shared<Parser>(Parser());
}

// constructor that takes file name as a parameter

VM::VM(std::string f_name)
{

	// here will be no such file exception

	std::string		buff;
	std::ifstream	inp(f_name);

	if (inp.is_open())
	{
		while (std::getline(inp, buff))
			input_file.push_back(buff);
	}
	else
        throw (NoSuchFileException());

    this->factory = std::make_shared<OperandFactory>(OperandFactory());
    this->lexer = std::make_shared<Lexer>(Lexer(this->input_file));
	this->parser = std::make_shared<Parser>(Parser());
	
	inp.close();
}

// copy constructor

VM::VM(VM const &vm)
{
	this->factory = std::make_shared<OperandFactory>(*(vm.factory));
    this->lexer = std::make_shared<Lexer>(*(vm.lexer));
	this->parser = std::make_shared<Parser>(*(vm.parser));
}

// copy assignment operator overloading

VM 	&VM::operator=(VM const &vm)
{
	this->input_file = vm.input_file;
    this->factory = std::make_shared<OperandFactory>(*(vm.factory));
    this->lexer = std::make_shared<Lexer>(*(vm.lexer));
	this->parser = std::make_shared<Parser>(*(vm.parser));

    return (*this);
}

// destructor

VM::~VM()
{

}

// ---------------------------------------------------------------------------------------

// runs the VM and executes instructions

void 		VM::RunInstructions()
{
	for (auto const &elem : tokens)
	{
		if (elem.first == "push")
			push(elem.second);
//		if (elem.first == "pop")
//			pop();
//		if (elem.first == "dump")
//			dump();
//		if (elem.first == "assert")
//			assert(elem.second);
//		if (elem.first == "add")
//			add();
//		if (elem.first == "sub")
//			sub();
//		if (elem.first == "mul")
//			mul();
//		if (elem.first == "div")
//			div();
//		if (elem.first == "mod")
//			mod();
//		if (elem.first == "print")
//			print();
//		if (elem.first == "exit")
//			return ;
	}

	// if exit instruction was not fo

//    throw NoExit();
}

// returns a type of object taking a string correspondent value
// also moves to parser


eOperandType 	VM::FindType(std::string const &str) const
{
	eOperandType type;

	if (str == "int8")
		type = _Int8;
	if (str == "int16")
		type = _Int16;
	if (str == "int32")
		type = _Int32;
	if (str == "float")
		type = _Float;
	if (str == "double")
		type = _Double;
	return (type);
}

// runs a lexical analysis of the input data

void	VM::LexicalAnalysis(void)
{
	this->lexer->RemoveComment();
	this->lexer->RemoveBlankString();
	this->lexer->ProcessWhiteSpaces();
	this->lexer->CheckLexicalErrors();
	this->lexer->CreateTokens();
	this->tokens = this->lexer->GetLexerTokens();
}

// performs parsing for the tokens produced by the lexer

void	VM::Parsing(void)
{
	this->parser->SetTokensList(this->tokens);
	this->parser->PerformInstructionArgumentCheck();
	this->parser->PrepareArgumentForProcessing();
	this->tokens = this->parser->GetParserTokens();
}

// method that prints tokens

void	VM::PrintTokens(void) const
{
    std::cout << "TOKENS BEFORE RUNNING INSTRUCTIONS" << std::endl;

	for (auto const &elem : tokens)
		std::cout << "|" << elem.first << "|\t|" << elem.second << "|" << std::endl;
}