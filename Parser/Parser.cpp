/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 12:54:10 by dzui              #+#    #+#             */
/*   Updated: 2018/08/05 12:54:12 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"

// error codes for the parser

const int Parser::NOT_PASSED_NEED_ARG = 1;
const int Parser::PASSED_NOT_NEED_ARG = 2;
const int Parser::INVALID_ARGUMENT = 3;
const int Parser::PARENTHESIS_ERROR = 4;

// default constructor

Parser::Parser()
{
	this->AssignInstructionsSet();
	this->AssignArgumentsPatterns();
}

// copy constructor

Parser::Parser(const Parser &pars)
{
	// something will be copied

	this->tokens = pars.tokens;
	this->instruction_argument = pars.instruction_argument;
	this->arguments_patterns = pars.arguments_patterns;
	this->error_log = pars.error_log;
}

// copy assignment operator

Parser& 	Parser::operator=(const Parser &pars)
{
	// something will be copied
	
	this->tokens = pars.tokens;
	this->instruction_argument = pars.instruction_argument;
	this->arguments_patterns = pars.arguments_patterns;
	this->error_log = pars.error_log;
	
	return (*this);
}

// destructor

Parser::~Parser()
{

}

// constructor that takes a set of tokens for further analysis

Parser::Parser(const std::vector<std::pair<std::string, std::string>> &tokens) : tokens(tokens)
{
	this->AssignInstructionsSet();
	this->AssignInstructionsSet();
}

// creates a set of instructions and arguments for them
// whether an instruction takes some data of not

void 	Parser::AssignInstructionsSet(void)
{
	instruction_argument.emplace_back("push", true);
	instruction_argument.emplace_back("pop", false);
	instruction_argument.emplace_back("dump", false);
	instruction_argument.emplace_back("assert", true);
	instruction_argument.emplace_back("add", false);
	instruction_argument.emplace_back("sub", false);
	instruction_argument.emplace_back("mul", false);
	instruction_argument.emplace_back("div", false);
	instruction_argument.emplace_back("mod", false);
	instruction_argument.emplace_back("print", false);
	instruction_argument.emplace_back("exit", false);
}

// sets the patterns for the arguments, that can be passed to the instructions

void	Parser::AssignArgumentsPatterns(void)
{
	std::string pattern_1 = std::string("((int8[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+)|");
	std::string pattern_2 = std::string("(int16[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+)|");
	std::string pattern_3 = std::string("(int32[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+)|");
	std::string pattern_4 = std::string("(float[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+[.][0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+)|");
	std::string pattern_5 = std::string("(double[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+[.][0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+))");

	arguments_patterns = std::regex(pattern_1 + pattern_2 + pattern_3 + pattern_4 + pattern_5);
}

// method that sets the tokens data

void	Parser::SetTokensList(const std::vector<std::pair<std::string, std::string>> &tokens)
{
	this->tokens = tokens;
}

// check the match of number of parenthesis to match '(' and ')'

int 	Parser::CountParenthesis(const std::string &str) const
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
	if (counter != 0)
		return (Parser::PARENTHESIS_ERROR);
	return (0);
}

// method that goes through all tokens and checks for the correspondence between instruction
// and the argument it received

void	Parser::PerformInstructionArgumentCheck(void)
{
	int error_code;
	
	for (size_t i = 0; i < tokens.size(); i++)
	{
		// check if the instruction needs argument or not
		
		error_code = CheckInstructionMatchParameter(tokens[i]);
		if (!error_code)
		{
			// check if passed argument matches allowed one
			
			if (!tokens[i].second.empty())
			{
				error_code = CheckPassedArgument(tokens[i].second);
				if (!error_code)
				{
					// check the second argument for the number of closed and opened parenthesis
					// it means that the argument is valid, it is one of the listed one
					
					error_code = CountParenthesis(tokens[i].second);
					
					// it means that the number of parenthesis is invalid '(' != ')'
					
					if (error_code == Parser::PARENTHESIS_ERROR)
						error_log.emplace_back("Line: " + std::to_string(i + 1) + " " + tokens[i].second + " number of '(' does not match ')'");
					
				}
				if (error_code == Parser::INVALID_ARGUMENT)
					error_log.emplace_back("Line: " + std::to_string(i + 1) + " instruction \"" + tokens[i].first + "\" has received invalid argument \"" + tokens[i].second + "\"");
			}
		}
		if (error_code == Parser::PASSED_NOT_NEED_ARG)
			error_log.emplace_back("Line: " + std::to_string(i + 1) + " instruction \"" + tokens[i].first + "\" received redundant argument");
		if (error_code == Parser::NOT_PASSED_NEED_ARG)
			error_log.emplace_back("Line: " + std::to_string(i + 1) + " instruction \"" + tokens[i].first + "\" requires argument to pe passed");
	}
	
	// print errors and pass and throw an exception
	
	if (!error_log.empty())
	{
		for (auto error : error_log)
			std::cout << error << std::endl;
		throw (ParserErrorException());
	}
}

// method that checks correspondence of instruction
// and whether it needs argument or not

int 	Parser::CheckInstructionMatchParameter(const std::pair<std::string, std::string> &instr_arg)
{
	
	for (auto elem : instruction_argument)
	{
		// the instruction was found
		
		if (instr_arg.first == elem.first)
		{
			// if the argument is needed, but is was not passed
			// we write an error in the log vector
			
			if ((elem.second == true) && ((instr_arg.second).empty()))
				return (Parser::NOT_PASSED_NEED_ARG);
			
			// if the argument is not needed, but passed
			// we write an error in the log vector
			
			if ((elem.second == false) && (!(instr_arg.second).empty()))
				return (Parser::PASSED_NOT_NEED_ARG);
			
			// we stop the search, the instruction and its argument march the rules
			// we stop check and leave
			
			break ;
		}
	}
	
	return (0);
}

// a method that will check passed argument to the instruction

int		Parser::CheckPassedArgument(const std::string &argument)
{
	if (std::regex_match(argument, arguments_patterns))
		return (0);
	return (Parser::INVALID_ARGUMENT);
}

// a method that will prepare arguments for further processing
// will reduce the number of '(' and')'

void	Parser::PrepareArgumentForProcessing(void)
{
	for (auto &elem : tokens)
	{
		std::replace_if(elem.second.begin(), elem.second.end(), [](char ch) -> bool {
			return ((ch == '(') || (ch == ')'));
		}, ' ');
		auto end = std::unique(elem.second.begin(), elem.second.end(), [](char l, char r){
			return std::isspace(l) && std::isspace(r) && l == r;
		});
		elem.second.erase(end, elem.second.end());
        elem.second.pop_back();
	}
}

// method that returns the data after the parser finished its work

std::vector<std::pair<std::string, std::string>>	Parser::GetParserTokens(void) const
{
	return (this->tokens);
}
