#ifndef ABSTRACTVM_PARSER_H
#define ABSTRACTVM_PARSER_H

#include <vector>
#include <string>
#include <regex>
#include <utility>
#include <iostream>

#define RED "\033[31m"

class Parser
{
	// some private fields
	
private:
	std::vector<std::pair<std::string, std::string>> 	tokens;
	std::vector<std::pair<std::string, bool>>			instruction_argument;
	std::regex											arguments_patterns;
	std::vector<std::string>							error_log;
	
	// error codes
	
	static const int									PASSED_NOT_NEED_ARG;
	static const int									NOT_PASSED_NEED_ARG;
	static const int									INVALID_ARGUMENT;
	static const int									PARENTHESIS_ERROR;
	
public:
	
	// methods for canonical form
	
			Parser();
			~Parser();
			Parser(const Parser &pars);
	Parser	&operator=(const Parser &pars);
			Parser(const std::vector<std::pair<std::string, std::string>> &tokens);
	
	// methods for the data processing
	
	void 	AssignInstructionsSet(void);
	void	AssignArgumentsPatterns(void);
	int 	CountParenthesis(const std::string &str) const;
	void	PerformInstructionArgumentCheck(void);
	int		CheckInstructionMatchParameter(const std::pair<std::string, std::string> &instr_arg);
	int		CheckPassedArgument(const std::string &argument);
	void	PrepareArgumentForProcessing(void);
	
	
	//	setters and getters
	
	void												SetTokensList(const std::vector<std::pair<std::string, std::string>> &tokens);
	std::vector<std::pair<std::string, std::string>>	GetParserTokens(void) const;
	// some exceptions
	
	class	ParserErrorException : public std::exception
	{
	public:
		const char *what() const throw() override
		{
			return ("Syntax error exception");
		}
	};
};

/* steps of the parsing and analysis

 1. check the token for instruction and its argument										+
 	- if mismatch | instr | | arg needed| - error instr takes argument						+
 	- if mismatch | instr | | arg no needed | - error instr does not take argument			+
 	
 2. check the argument																		+
 	- if it does not match any of the patters - error, passed invalid argument				+
 3. check the correspondance between '(' and ')', number of opened == number of closed		+
 
*/

#endif //ABSTRACTVM_PARSER_H
