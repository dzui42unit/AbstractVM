#include "Lexer.h"

// -----------------------------------------------------------------------------

// constructor that takes an vector of strings

Lexer::Lexer(const std::vector<std::string> &data)
{
    data_to_process = data;

    // assign some rules, will be added soon
    // patterns for checking
}

// copy constructor

Lexer::Lexer(const Lexer &lex) : data_to_process(lex.data_to_process)
{
    // assign some rules, will be added soon
    // patterns for checking
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
            std::cout << elem << std::endl;
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

// --------------------------------------------------------------------------------------------

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
    std::string res;
    size_t      pos;

    res = str;
        pos = 0;
        while (std::isspace(res[pos]))
            pos++;
    return (std::string(res.begin() + pos, res.end()));
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