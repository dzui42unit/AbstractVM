#include "Lexer.h"

// constructor that takes an vector of strings

Lexer::Lexer(const std::vector<std::string> &data)
{
    data_to_process = data;
	CreateLexerPatterns();

    // assign some rules, will be added soon
    // patterns for checking
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

std::vector<std::string>    Lexer::GetLexerData(void) const
{
    return (this->data_to_process);
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

std::vector<std::string> 		Lexer::SplitString(std::string const &str, char del)
{
	std::vector<std::string>	res;
	size_t 						pos;
	
	pos = str.find_first_of(del);
	if (pos == std::string::npos)
	{
		res.emplace_back(str);
		res.emplace_back("");
	}
	else
	{
		res.emplace_back((std::string(str.begin(), str.begin() + pos)));
		res.emplace_back((std::string(str.begin() + pos + 1, str.end())));
	}
	return (res);
}

// Creates a tokens for further processing

void							Lexer::CreateTokens(void)
{
	for (auto elem : this->data_to_process)
		this->tokens.emplace_back(SplitString(elem, ' '));
	for (auto elem : this->tokens)
		for (auto elem2 : elem)
			elem2 = TrimString(elem2);
}

// prints tokens produced by lexer

void							Lexer::PrintTokens(void)
{
	std::cout << "PRODUCED TOKENS" << std::endl;
	for (auto elem : this->tokens)
	{
		for (auto elem2 : elem)
		{
			std::cout << "|" << elem2 << "|";
		}
		std::cout << std::endl;
	}
}

// creates a pattern to check a string for correctness of tokens

void							Lexer::CreateLexerPatterns(void)
{
	// patterns for the instructions
	
	regex_patterns.emplace_back("(\\s+)?push(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?pop(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?dump(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?assert(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?add(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?sub(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?mul(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?div(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?mod(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?print(\\s+)?");
	regex_patterns.emplace_back("(\\s+)?exit(\\s+)?");
	
	// patterns for the input values
	
	regex_patterns.emplace_back("int8[(]+(\\s+)?[-]?[0-9]+(\\s+)?[)]+(\\s+)?");
	regex_patterns.emplace_back("int16[(]+(\\s+)?[-]?[0-9]+(\\s+)?[)]+(\\s+)?");
	regex_patterns.emplace_back("float[(]+(\\s+)?[-]?[0-9]+.[0-9]+(\\s+)?[)]+(\\s+)?");
	regex_patterns.emplace_back("double[(]+(\\s+)?[-]?[0-9]+.[0-9]+(\\s+)?[)]+(\\s+)?");
	
	regex_patterns.emplace_back("int32[(]+(\\s+)?((\\s+)[(]+(\\s+)?){0,}[-]?[0-9]+((\\s+)?[)]+(\\s+)){0,}(\\s+)?[)]+(\\s+)?");
	
}

// check if the tokens are valid, or throw an exception in case of error

bool							Lexer::ValidateToken(const std::string &check_token)
{
	for (auto reg_expr : this->regex_patterns)
	{
		if (std::regex_match(check_token, reg_expr))
			return (true);
	}
	return (false);
}

// method that will find lexical errors, in case of presence -> throws an exception

void							Lexer::CheckLexicalErrors(void)
{
	for (size_t i = 0; i < this->tokens.size(); i++)
	{
		for (auto elem : tokens[i])
		{
			if (!elem.empty() && !ValidateToken(elem))
				error_log.emplace_back("LINE: " + std::to_string(i + 1) + " TOKEN |" + elem + "| IS UNDEFINED");
		}
	}
	
	if (!error_log.empty())
	{
		for (auto elem : error_log)
			std::cout << elem << std::endl;
		exit(0);
	}
	// here will be printing of all the errors, and throwing of the exception
	
}