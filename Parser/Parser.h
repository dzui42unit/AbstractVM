#ifndef ABSTRACTVM_PARSER_H
#define ABSTRACTVM_PARSER_H

#include <vector>
#include <string>
#include <utility>

class Parser
{
	// some private fields
	
private:
	std::vector<std::vector<std::string>>				tokens;
	std::vector<std::pair<std::string, bool>>	instruction_argument;
public:
	
	// methods for canonical form
	
			Parser();
			~Parser();
			Parser(const Parser &pars);
	Parser	&operator=(const Parser &pars);
			Parser(const std::vector<std::vector<std::string>>	tokens);
	
	// methods for the data processing
	
	void 	AssignInstructionsSet(void);
	int 	CountParenthesis(const std::string &str) const;
	
	//	setters and getters
	
	void	SetTokensList(const std::vector<std::vector<std::string>> &tokens);
};

/* steps of the parsing and analysis

 1. check the token for instruction and its argument
 	- if mismatch | instr | | arg needed| - error instr takes argument
 	- if mismatch | instr | | arg no needed | - error instr does not take argumentgit 
 
*/

#endif //ABSTRACTVM_PARSER_H
