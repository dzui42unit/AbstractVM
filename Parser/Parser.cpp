#include "Parser.h"

// default constructor

Parser::Parser()
{
	this->AssignInstructionsSet();
}

// copy constructor

Parser::Parser(const Parser &pars)
{
	// something will be copied

	this->tokens = pars.tokens;
	this->instruction_argument = pars.instruction_argument;
}

// copy assignment operator

Parser& 	Parser::operator=(const Parser &pars)
{
	// something will be copied
	
	this->tokens = pars.tokens;
	this->instruction_argument = pars.instruction_argument;
	
	return (*this);
}

// destructor

Parser::~Parser()
{

}

// constructor that takes a set of tokens for further analysis

Parser::Parser(std::vector<std::vector<std::string>> tokens) : tokens(tokens)
{
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

// method that sets the tokens data

void	Parser::SetTokensList(const std::vector<std::vector<std::string>> &tokens)
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
	return (counter);
}