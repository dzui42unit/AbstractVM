/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 12:51:16 by dzui              #+#    #+#             */
/*   Updated: 2018/08/05 12:51:24 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_LEXER_H
#define ABSTRACTVM_LEXER_H

#define YELLOW "\033[33m"

#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>
#include <utility>
#include <string>

class Lexer
{
private:
    std::vector<std::string>    						data_to_process;
	std::regex											regex_patterns;
	std::vector<std::pair<std::string, std::string>>	tokens;
	std::vector<std::string>							error_log;
public:

    // methods for manipulating input data
    // remove comments from the input
    // remove whitespaces
    // remove blank strings
    // trim string

	void												CreateLexerPatterns(void);
    void 			            						RemoveBlankString(void);
    void                        						PrintLexerData(void);
    void			            						RemoveComment(void);
	void												ProcessWhiteSpaces(void);
	void												CreateTokens(void);
	void												PrintTokens(void);
	bool												ValidateToken(const std::string &check_token);
	void												CheckLexicalErrors(void);
	std::pair<std::string, std::string>					SplitString(std::string const &str, char del);
	std::string 	            						UniqueWhiteSpaces(const std::string &str);
	std::string                 						TrimString(const std::string &str);
	std::string		            						RemoveSpaces(const std::string &str);
	std::vector<std::pair<std::string, std::string>>	GetLexerTokens(void) const;
	
	
	// canonical form of the Lexer class

                                						Lexer() = delete;
                                						Lexer(const std::vector<std::string> &data);
    Lexer                      		 					&operator=(const Lexer &lex);
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
