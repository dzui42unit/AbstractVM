#include "Parser.h"

// default constructor

const int Parser::NOT_PASSED_NEED_ARG = 1;
const int Parser::PASSED_NOT_NEED_ARG = 2;
const int Parser::INVALID_ARGUMENT = 3;

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
	return (counter);
}

// method that goes through all tokens and checks for the correspondace between instruction
// and the argument it recieved

void	Parser::PerformInstructionArgumentCheck(void)
{
	int error_code;
	
	for (size_t i = 0; i < tokens.size(); i++)
	{
		// check if the instruction needs argument or not
		
		error_code = CheckInstructionMatchParameter(tokens[i]);
		if (!error_code)
		{
			std::cout << tokens[i].first << " MATCHED " << std::endl;
			
			// check if passed argument matches allowed one
			
			if (!tokens[i].second.empty())
			{
				error_code = CheckPassedArgument(tokens[i].second);
				if (!error_code)
				{
					// here will be the continuation of the checks
				}
				if (error_code == Parser::INVALID_ARGUMENT)
					error_log.emplace_back("LINE: " + std::to_string(i + 1) + " |" + tokens[i].first + "| HAS TAKEN INVALID ARGUMENT " + tokens[i].second);
			}
		}
		if (error_code == Parser::PASSED_NOT_NEED_ARG)
			error_log.emplace_back("LINE: " + std::to_string(i + 1) + " |" + tokens[i].first + "| DOES NOT TAKE AN ARGUMENT");
		if (error_code == Parser::NOT_PASSED_NEED_ARG)
			error_log.emplace_back("LINE: " + std::to_string(i + 1) + " |" + tokens[i].first + "| NEEDS AN ARGUMENT PASSED");
	}
	
	if (!error_log.empty())
	{
		for (auto error : error_log)
		{
			std::cout << error << std::endl;
		}
		throw (ParserErrorException());
	}
}

// method that checks correspondance of instruction
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