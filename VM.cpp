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

// casts an object and assigns is factory_pointer

void	VM::CastObject(IOperand *ptr)
{
	if (dynamic_cast< Operand<char> *>(ptr))
	{
		dynamic_cast<Operand<char> *>(ptr)->setFactoryPtr(factory);
		return ;
	}
	if (dynamic_cast<Operand<short> *>(ptr))
	{
		dynamic_cast<Operand<short> *>(ptr)->setFactoryPtr(factory);
		return ;
	}
	if (dynamic_cast<Operand<int> *>(ptr))
	{
		dynamic_cast<Operand<int> *>(ptr)->setFactoryPtr(factory);
		return ;
	}
	if (dynamic_cast<Operand<float> *>(ptr))
	{
		dynamic_cast<Operand<float> *>(ptr)->setFactoryPtr(factory);
		return ;
	}
	if (dynamic_cast<Operand<double> *>(ptr))
	{
		dynamic_cast<Operand<double> *>(ptr)->setFactoryPtr(factory);
		return ;
	}
}

// push

void 	VM::push()
{
	try
	{
		const IOperand *one;
		const IOperand *two;

		val_stack.push((factory->createOperand(_Int32, "123")));
		CastObject(const_cast<IOperand *>(val_stack.top()));
		val_stack.push((factory->createOperand(_Int32, "12312")));
		CastObject(const_cast<IOperand *>(val_stack.top()));
		one = val_stack.top();
		val_stack.pop();
		two = val_stack.top();
		val_stack.top();

		std::cout << (*one + *two)->toString() << std::endl;
	}
	catch (...)
	{

	}

}

// check the presence of the lexical or syntactical errors

void	VM::CheckErrors()
{
	int 		instruction_number;
	int 		i;
	std::string	error_msg;

	i = 0;
	for (auto &elem : instr_args)
	{
		error_msg = "";
		instruction_number = FindInstruction(elem.first);
		if (instruction_number == -1)
		{
			valid = false;
			error_msg += ("Line " + std::to_string(i + 1) + " Lexical error: ");
			error_msg += (elem.second + ("\"" + elem.first + "\" unknown instruction!"));
		}
		else
		{
			if (elem.first == "exit")
				exit_instr = true;
			if (static_cast<bool>(elem.second.length()) != instr_set[instruction_number].second)
			{
				valid = false;
				error_msg += ("Line " + std::to_string(i + 1) + " Syntactic error: " + "\"" + elem.second + "\"");
				if (instr_set[instruction_number].second)
					error_msg += " argument is passed!";
				else
					error_msg += " argument is not needed!";
			}
			else
			{
				if (!CheckArgument(elem.second) && instr_set[instruction_number].second)
				{
					valid = false;
					error_msg += ("Line " + std::to_string(i + 1) + " Lexical error:");
					error_msg += (" argument \"" + elem.second + "\" can not be passed to instruction!");
				}
				if (CheckArgument(elem.second) && instr_set[instruction_number].second)
				{
					if (CountParenthesis(elem.second))
					{
						valid = false;
						error_msg += ("Line " + std::to_string(i + 1) + " Syntactic error: ");
						error_msg += ("mismatch of opened and closed parenthesis!");
					}
				}
			}
		}
		if (!error_msg.empty())
			errors.push_back(error_msg);
		i++;
	}
	if (!exit_instr)
		errors.emplace_back("Line Syntactical error:" + std::to_string(i + 1) + " \"exit\" instruction is not provided.");
	if (!valid)
		PrintErrors();
}

// check the match of number of parenthesis

int 	VM::CountParenthesis(const std::string &str) const
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '(')
			counter++;
		if (str[i] == ')')
			counter--;
		i++;
	}
	return (counter);
}

// prints all the file with errors description

void	VM::PrintErrors() const
{
	for (int i = 0; i < instr_args.size(); i++)
	{
		std::cout << "Line " << i << " : " << instr_args[i].first << " " << instr_args[i].second << std::endl;
	}
	std::cout << std::endl;
	for (int j = 0; j < errors.size(); j++)
	{
		std::cout << errors[j] << std::endl;
	}
}

// check matches the argument passed to the instruction to one that it can apply

int 	VM::CheckArgument(const std::string &arg)
{
	for (const auto &reg_pattern : reg_patterns)
	{
		std::regex r(reg_pattern);
		if (std::regex_match(arg, r))
			return (1);
	}
	return (0);
}

// finds the instruction from the set and returns its index if is found, -1 if not

int 	VM::FindInstruction(const std::string &instr)
{
	for (int i = 0; i < instr_set.size(); i++)
	{
		if (instr_set[i].first == instr)
			return (i);
	}
	return (-1);
}

// assigns a patterns to check the arguments of instructions

void 	VM::AssignRegexPatternsSet()
{
	reg_patterns.emplace_back("int8()[(]+(\\s+)?[-]?[0-9]+(\\s+)?[)]+");
	reg_patterns.emplace_back("int16()[(]+(\\s+)?[-]?[0-9]+(\\s+)?[)]+");
	reg_patterns.emplace_back("int32()[(]+(\\s+)?[-]?[0-9]+(\\s+)?[)]+");
	reg_patterns.emplace_back("float[(]+(\\s+)?[-]?[0-9]+.[0-9]+(\\s+)?[)]+");
	reg_patterns.emplace_back("double[(]+(\\s+)?[-]?[0-9]+.[0-9]+(\\s+)?[)]+");
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

// fills a vector of the pairs that represents an instruction and its argument

void		VM::MakeInstructionsSet(void)
{
	std::vector<std::string>	temp;

	for (auto &elem : input_file)
	{
		SplitString(temp, elem, ' ');
		instr_args.emplace_back(temp[0], temp[1]);
		temp.clear();
	}
}

// returns a vector of pairs that represent instructions

std::vector<std::pair<std::string, std::string> > VM::getInstrSet() const
{
	return (this->instr_args);
}

// splits a string by a delimiter and writes it in a vector

void 		VM::SplitString(std::vector<std::string> &res, std::string str, char del)
{
	size_t pos;

	pos = str.find_first_of(del);

	if (pos == std::string::npos)
	{
		res.emplace_back(RemoveSpaces(str));
		res.emplace_back("");
	}
	else
	{
		res.emplace_back((std::string(str.begin(), str.begin() + pos)));
		res.emplace_back((std::string(str.begin() + pos + 1, str.end())));
	}
}

// removes all the whitespaces that are present in the string

std::string		VM::RemoveSpaces(std::string str)
{
	str.erase(std::remove_if(str.begin(), str.end(), [](char ch) -> bool{
			return (std::isspace(ch));
		}), str.end());
	return (str);
}

// replaces each whitespace character to the ' ', if it is not a ' ' character

void 						VM::WhitesSpaceToSpace()
{
	for (auto &elem : input_file)
	{
		std::replace_if(elem.begin(), elem.end(), [](char ch) -> bool {
			return (std::isspace(ch) && (ch != ' '));
		}, ' ');
	}
	RemoveBlankString();
}

// removes a comments from a string
// comment is an occurrence of the ';' character

void						VM::RemoveComment(void)
{
	size_t 	pos;

	for (auto &elem : input_file)
	{
		pos = elem.find_first_of(';');
		if (pos != std::string::npos)
			elem.erase(elem.begin() + pos, elem.end());
	}
	RemoveBlankString();
}

// removes a blank strings from a vector

void						VM::RemoveBlankString(void)
{
	int	i;

	i = 0;
	while (i < input_file.size())
	{
		if (input_file[i].empty())
		{
			input_file.erase(input_file.begin() + i);
			i = 0;
			continue ;
		}
		i++;
	}
}

// removes redundant spaces from a string

void						VM::UniqueWhiteSpaces()
{
	int 					i;
	std::string::iterator 	start;
	std::string::iterator 	end;

	for (auto &elem : input_file)
	{
		end = std::unique(elem.begin(), elem.end(), [](char ch1, char ch2) -> bool
		{
			return (std::isspace(ch1) && isspace(ch2) && (ch1 == ch2));
		});
		elem = std::string(elem.begin(), end);
	}
	i = 0;
	RemoveBlankString();
	while (i < input_file.size())
	{
		if (input_file[i] == " ")
		{
			input_file.erase(input_file.begin() + i);
			i = 0;
			continue ;
		}
		else
		{
			start = input_file[i].begin();
			end = input_file[i].end() - 1;
			if (*start == ' ')
				start++;
			if (*end == ' ')
				end--;
			input_file[i] = std::string(start, end + 1);
		}
		i++;
	}
}

// default constructor

VM::VM()
{
	factory = std::make_shared<OperandFactory>(OperandFactory());
	AssignRegexPatternsSet();
	AssignInstructionsSet();
}

// constructor that takes file name as a parameter

VM::VM(std::string f_name)
{
	std::string		buff;
	std::ifstream	inp(f_name);

	if (inp.is_open())
	{
		while (std::getline(inp, buff))
			input_file.push_back(buff);
		AssignRegexPatternsSet();
		AssignInstructionsSet();
		valid = true;
	}
	else
	{
		std::cout << "I can't open a file." << std::endl;
		exit(0);
	}
	factory = std::make_shared<OperandFactory>(OperandFactory());
	inp.close();
}

// copy constructor

VM::VM(VM const &vm)
{
	valid = vm.valid;
	input_file = vm.input_file;
	val_stack = vm.val_stack;
	instr_set = vm.instr_set;
	exit_instr = vm.exit_instr;
	errors = vm.errors;
	instr_args = vm.instr_args;
	reg_patterns = vm.reg_patterns;
	factory = std::make_shared<OperandFactory>(*(vm.factory));
}

// assignment operator overloading

VM 	&VM::operator=(VM const &vm)
{
	valid = vm.valid;
	exit_instr = vm.exit_instr;
	errors = vm.errors;
	input_file = vm.input_file;
	val_stack = vm.val_stack;
	instr_set = vm.instr_set;
	instr_args = vm.instr_args;
	reg_patterns = vm.reg_patterns;
	factory = std::make_shared<OperandFactory>(*(vm.factory));
	return (*this);
}

// destructor

VM::~VM()
{

}