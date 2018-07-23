//
// Created by Dmytro Zui on 7/16/18.
//

#ifndef ABSTRACTVM_LEXER_H
#define ABSTRACTVM_LEXER_H

#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>
#include <utility>
#include <string>

class Lexer
{
private:
    std::vector<std::string>    			data_to_process;
//	std::vector<std::regex>					regex_patterns;
	std::regex								regex_patterns;
	std::vector<std::vector<std::string>>	tokens;
	std::vector<std::string>				error_log;
public:

    // methods for manipulating input data
    // remove comments from the input
    // remove whitespaces
    // remove blank strings
    // trim string

	void						CreateLexerPatterns(void);
    void 			            RemoveBlankString(void);
    void                        PrintLexerData(void);
    void			            RemoveComment(void);
	void						ProcessWhiteSpaces(void);
	void						CreateTokens(void);
	void						PrintTokens(void);
	bool						ValidateToken(const std::string &check_token);
	void						CheckLexicalErrors(void);
	std::vector<std::string>	SplitString(std::string const &str, char del);
	std::string 	            UniqueWhiteSpaces(const std::string &str);
	std::string                 TrimString(const std::string &str);
	std::string		            RemoveSpaces(const std::string &str);
	std::vector<std::string>    GetLexerData(void) const;
	
	
	// canonical form of the Lexer class

                                Lexer() = delete;
                                Lexer(const std::vector<std::string> &data);
    Lexer                       &operator=(const Lexer &lex);
                                Lexer(const Lexer &lex);
                                ~Lexer();
	
	// custom written exceptions for the lexer
	
	class						LexicalErrorsException : public std::exception
	{
	public:
		const char 				*what() const throw() override
		{
			return ("Lexical errors in file exception");
		}
	};


};

#endif //ABSTRACTVM_LEXER_H
