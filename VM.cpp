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

// ---------------------------------------------------------------------------------------

// constructor that takes a vector of strings as an input

VM::VM(std::vector<std::string> inp_f)
{
	this->input_file = inp_f;
	this->factory = std::make_shared<OperandFactory>(OperandFactory());
	this->lexer = std::make_shared<Lexer>(Lexer(this->input_file));

//	AssignRegexPatternsSet();
//	AssignInstructionsSet();
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
//		AssignRegexPatternsSet();
//		AssignInstructionsSet();
		valid = true;
	}
	else
	{
        throw (NoSuchFileException());
	}

    this->factory = std::make_shared<OperandFactory>(OperandFactory());
    this->lexer = std::make_shared<Lexer>(Lexer(this->input_file));

    inp.close();
}

// copy constructor

VM::VM(VM const &vm)
{

//	valid = vm.valid;
//	input_file = vm.input_file;
//	val_stack = vm.val_stack;
//	instr_set = vm.instr_set;
//	exit_instr = vm.exit_instr;
//	errors = vm.errors;
//	instr_args = vm.instr_args;
//	reg_patterns = vm.reg_patterns;

	this->factory = std::make_shared<OperandFactory>(*(vm.factory));
    this->lexer = std::make_shared<Lexer>(*(vm.lexer));
}

// assignment operator overloading

VM 	&VM::operator=(VM const &vm)
{
	this->input_file = vm.input_file;

    this->factory = std::make_shared<OperandFactory>(*(vm.factory));
    this->lexer = std::make_shared<Lexer>(*(vm.lexer));

//	valid = vm.valid;
//	exit_instr = vm.exit_instr;
//	errors = vm.errors;
//	input_file = vm.input_file;
//	val_stack = vm.val_stack;
//	instr_set = vm.instr_set;
//	instr_args = vm.instr_args;
//	reg_patterns = vm.reg_patterns;
//	factory = std::make_shared<OperandFactory>(*(vm.factory));
//	this->lexer = std::make_shared<Lexer>(this->input);

    return (*this);
}

// destructor

VM::~VM()
{

}

// ---------------------------------------------------------------------------------------

// runs a lexical analysis of the input data

void	VM::LexicalAnalysis(void)
{
	this->lexer->PrintLexerData();
}

// runs the VM and executes instructions

void 		VM::RunInstructions()
{
	for (auto const &elem : instr_args)
	{
		if (elem.first == "push")
			push(elem.second);
		if (elem.first == "pop")
			pop();
		if (elem.first == "dump")
			dump();
		if (elem.first == "assert")
			assert(elem.second);
		if (elem.first == "add")
			add();
		if (elem.first == "sub")
			sub();
		if (elem.first == "mul")
			mul();
		if (elem.first == "div")
			div();
		if (elem.first == "mod")
			mod();
		if (elem.first == "print")
			print();
		if (elem.first == "exit")
			return ;
	}
	if (!exit_instr)
		throw NoExit();
}

// returns a type of object taking a string correspondent value

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

// assigns a patterns to check the arguments of instructions

void 	VM::AssignRegexPatternsSet()
{
	reg_patterns.emplace_back(R"(int8(\s+)?[(]+(\s+)?[-]?[0-9]+(\s+)?[)]+(\s+)?)");
	reg_patterns.emplace_back(R"(int16(\s+)?[(]+(\s+)?[-]?[0-9]+(\s+)?[)]+(\s+)?)");
	reg_patterns.emplace_back(R"(int32(\s+)?[(]+(\s+)?[-]?[0-9]+(\s+)?[)]+(\s+)?)");
	reg_patterns.emplace_back(R"(float(\s+)?[(]+(\s+)?[-]?[0-9]+.[0-9]+(\s+)?[)]+(\s+)?)");
	reg_patterns.emplace_back(R"(double(\s)?[(]+(\s+)?[-]?[0-9]+.[0-9]+(\s+)?[)]+(\s+)?)");
}

// assigns the set of instructions ints name and whether it takes argument or not

void 	VM::AssignInstructionsSet()
{
	instr_set.emplace_back("push", true);
	instr_set.emplace_back("pop", false);
	instr_set.emplace_back("dump", false);
	instr_set.emplace_back("assert", true);
	instr_set.emplace_back("add", false);
	instr_set.emplace_back("sub", false);
	instr_set.emplace_back("mul", false);
	instr_set.emplace_back("div", false);
	instr_set.emplace_back("mod", false);
	instr_set.emplace_back("print", false);
	instr_set.emplace_back("exit", false);
}
