/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 12:51:07 by dzui              #+#    #+#             */
/*   Updated: 2018/08/05 12:51:09 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.h"

// constructor that takes an vector of strings

Lexer::Lexer(const std::vector<std::string> &data)
{
    data_to_process = data;
	CreateLexerPatterns();
}

// copy constructor

Lexer::Lexer(const Lexer &lex) : data_to_process(lex.data_to_process), regex_patterns(lex.regex_patterns), tokens(lex.tokens), error_log(lex.error_log)
{

}

// copy assignment operator

Lexer			&Lexer::operator=(const Lexer &lex)
{
	this->regex_patterns = lex.regex_patterns;
	this->data_to_process = lex.data_to_process;
	
	return (*this);
}

// destructor

Lexer::~Lexer()
{

}

// removes a comments from a string
// comment is an occurrence of the ';' character

void			Lexer::RemoveComment(void)
{
    size_t			pos;

    for (auto &elem : data_to_process)
    {
        pos = elem.find(';');
        if (pos != std::string::npos) {
            elem.erase(elem.begin() + pos, elem.end());
        }
    }
}

// removes a blank strings from a input data

void			Lexer::RemoveBlankString(void)
{
    size_t 			i;
    std::string 	str;

    auto lambda = [&str]() -> bool {
        for (size_t i = 0; i < str.length(); i++)
        {
            if (!std::isspace(str[i]))
                return (false);
        }
        return (true);
    };

    i = 0;
    while (i < data_to_process.size())
    {

        str = data_to_process[i];
        if (data_to_process[i].empty() || lambda())
        {
            data_to_process.erase(data_to_process.begin() + i);
            i = 0;
            continue ;
        }
        i++;
    }
}

// replaces all whitespaces with space and makes in unique

std::string     Lexer::UniqueWhiteSpaces(const std::string &str)
{
    std::string res;

    res = str;
    std::replace_if(res.begin(), res.end(), [](char ch) { return isspace(ch); }, ' ');
    auto end = std::unique(res.begin(), res.end(), [](char l, char r){
        return std::isspace(l) && std::isspace(r) && l == r;
    });
    res.erase(end, res.end());
    return (res);
}

// trims a string, removes whitespaces from the beginning and the end

std::string	    Lexer::TrimString(const std::string &str)
{
	std::string s;
	
	s = str;
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isspace(*it))
		it++;
	
	std::string::const_reverse_iterator rit = s.rbegin();
	while (rit.base() != it && isspace(*rit))
		rit++;
	
	return std::string(it, rit.base());
}

// removes all spaces from a string

std::string		Lexer::RemoveSpaces(const std::string &str)
{
    std::string res;

    res = str;
    res.erase(std::remove_if(res.begin(), res.end(), [](char ch) -> bool{
        return (std::isspace(ch));
    }), res.end());
    return (res);
}

// prints the data in the lexer

void	Lexer::PrintLexerData(void)
{
    std::cout << "DATA IN THE LEXER" << std::endl;
    for (auto &v : this->data_to_process)
    {
        std::cout << "|" << v << "|" << std::endl;
    }
}

// method that returns lexer data after it was processed
// trimmed strings, removed comments, removed blank strings, reduced spaces;

std::vector<std::pair<std::string, std::string>>    Lexer::GetLexerTokens(void) const
{
    return (this->tokens);
}

// method that will process each string and will remove all whitespaces
// replace all of them by space, makes unique

void                        Lexer::ProcessWhiteSpaces(void)
{
    for (auto &item : this->data_to_process)
    {
		TrimString(item);
		item = TrimString(item);
        item = UniqueWhiteSpaces(item);
    }
}

// splits a string by a delimiter and writes it in a vector

std::pair<std::string, std::string>	Lexer::SplitString(std::string const &str, char del)
{
	std::pair<std::string, std::string>	res;
	size_t 								pos;
	
	pos = str.find_first_of(del);
	if (pos == std::string::npos)
	{
		res.first = str;
		res.second = "";
	}
	else
	{
		res.first = std::string(str.begin(), str.begin() + pos);
		res.second = std::string(str.begin() + pos + 1, str.end());
	}
	return (res);
}

// Creates a tokens for further processing

void							Lexer::CreateTokens(void)
{
	for (auto elem : this->data_to_process)
		this->tokens.emplace_back(SplitString(elem, ' '));
	for (auto elem : this->tokens)
	{
		elem.first = TrimString(elem.first);
		elem.second = TrimString(elem.second);
	}
}

// prints tokens produced by lexer

void							Lexer::PrintTokens(void)
{
	std::cout << "PRODUCED TOKENS" << std::endl;
	for (auto elem : this->tokens)
	{
			std::cout << "|" << elem.first << "|" << " |" << elem.second << std::endl;
	}
}

// creates a pattern to check a string for correctness of tokens

void							Lexer::CreateLexerPatterns(void)
{
	// patterns for lexical analysis
	
	std::string pattern_1 = std::string("(((\\s+)?(push|pop|dump|assert|add|sub|mul|div|mod|print|exit)(\\s+)?)*)");
	std::string pattern_2 = std::string("(((\\s+)?(int8[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+(\\s+)?)|");
	std::string pattern_3 = std::string("(int16[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+(\\s+)?)|");
	std::string pattern_4 = std::string("(int32[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+(\\s+)?)|");
	std::string pattern_5 = std::string("(float[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+[.][0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+(\\s+)?)|");
	std::string pattern_6 = std::string("(double[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+[.][0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+(\\s+)?)(\\s+)?)*)");

	this->regex_patterns = std::regex(pattern_1 + pattern_2 + pattern_3 + pattern_4 + pattern_5 + pattern_6);
}

// check if the tokens are valid, or throw an exception in case of error

bool							Lexer::ValidateToken(const std::string &check_token)
{
	if (std::regex_match(check_token, regex_patterns)) {
		return (true);
	}
	return (false);
}

// method that will find lexical errors, in case of presence -> throws an exception

void							Lexer::CheckLexicalErrors(void)
{
	for (size_t i = 0; i < data_to_process.size(); i++)
	{
		if (!data_to_process[i].empty() && !ValidateToken(data_to_process[i]))
			error_log.emplace_back("Line: " + std::to_string(i + 1) + " " + data_to_process[i] + " - undefined token");
	}
	
	// printing of all the errors, and throwing of the exception
	
	if (!error_log.empty())
	{
		for (auto elem : error_log)
			std::cout << elem << std::endl;
		throw LexicalErrorsException();
	}
	
}
