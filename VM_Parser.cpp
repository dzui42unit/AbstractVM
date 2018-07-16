/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VMparser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:12:34 by dzui              #+#    #+#             */
/*   Updated: 2017/12/06 16:12:35 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VM.h"

#define RED "\033[31m"
#define YELLOW "\033[33m"

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
			error_msg += ("\"" + elem.first + "\" unknown instruction!");
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
	if (!valid)
	{
		if (!exit_instr)
			errors.emplace_back("Line Syntactical error: " + std::to_string(i + 1) + " \"exit\" instruction is not provided.");
		throw SyntaxLexicalError();
	}
}

// prints all the file with errors description

void	VM::PrintErrors() const
{
	for (size_t i = 0; i < instr_args.size(); i++)
	{
		std::cout << "Line " << i + 1 << " : " << instr_args[i].first << " " << instr_args[i].second << std::endl;
	}
	std::cout << std::endl;
	for (size_t j = 0; j < errors.size(); j++)
	{
		if (errors[j].find("Lexical") != std::string::npos)
			std::cout << RED;
		else
			std::cout << YELLOW;
		std::cout << errors[j] << std::endl;
	}
}

// finds the instruction from the set and returns its index if is found, -1 if not

int 	VM::FindInstruction(const std::string &instr)
{
	for (size_t i = 0; i < instr_set.size(); i++)
	{
		if (instr_set[i].first == instr)
			return (static_cast<int>(i));
	}
	return (-1);
}

// fills a vector of the pairs that represents an instruction and its argument

void		VM::MakeInstructionsSet(void)
{
	std::vector<std::string>	temp;

	for (auto &elem : input_file)
	{
		SplitString(temp, elem, ' ');
		instr_args.emplace_back(this->lexer->TrimString(temp[0]), this->lexer->TrimString(temp[1]));
		temp.clear();
	}
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

// splits a string by a delimiter and writes it in a vector

void 		VM::SplitString(std::vector<std::string> &res, std::string const &str, char del)
{
	size_t pos;

	pos = str.find_first_of(del);

	if (pos == std::string::npos)
	{
		res.emplace_back(this->lexer->RemoveSpaces(str));
		res.emplace_back("");
	}
	else
	{
		res.emplace_back((std::string(str.begin(), str.begin() + pos)));
		res.emplace_back((std::string(str.begin() + pos + 1, str.end())));
	}
}
