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
    std::vector<std::string>    data_to_process;
public:

    // methods for manipulating input data
    // remove comments from the input
    // remove whitespaces
    // remove blank strings
    // trim string

    void 			            RemoveBlankString(void);
    void                        PrintLexerData(void);
    std::string 	            UniqueWhiteSpaces(const std::string &str);
    std::string                 TrimString(const std::string &str);
    std::string		            RemoveSpaces(const std::string &str);
    void			            RemoveComment(void);
    std::vector<std::string>    GetLexerData(void) const;
	void						ProcessWhiteSpaces(void);

    // canonical form of the Lexer class

                                Lexer() = delete;
                                Lexer(const std::vector<std::string> &data);
    Lexer                       &operator=(const Lexer &lex);
                                Lexer(const Lexer &lex);
                                ~Lexer();


};

#endif //ABSTRACTVM_LEXER_H
