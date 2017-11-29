/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:21:17 by dzui              #+#    #+#             */
/*   Updated: 2017/11/28 19:21:18 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "VM.h"

// returns a content of a file

std::vector<std::string>	VM::FileContetnt() const
{
	return (input_file);
}

// replaces each whitespace character to the ' ', if it is not a ' ' character

void 						VM::WhitesSpaceToSpace()
{
	for (auto &elem : input_file)
	{
		std::replace_if(elem.begin(), elem.end(), [](char ch) -> bool {
			return (std::isspace(ch) && (ch != ' '));
		}, ' ');
	}
	RemoveBlankString();
}

// removes a comments from a string
// comment is an occurrence of the ';' character

void						VM::RemoveComment(void)
{
	size_t 	pos;

	for (auto &elem : input_file)
	{
		pos = elem.find_first_of(';');
		if (pos != std::string::npos)
			elem.erase(elem.begin() + pos, elem.end());
	}
	RemoveBlankString();
}

// removes a blank strings from a vector

void						VM::RemoveBlankString(void)
{
	int	i;

	i = 0;
	while (i < input_file.size())
	{
		if (input_file[i].empty())
		{
			input_file.erase(input_file.begin() + i);
			i = 0;
			continue ;
		}
		i++;
	}
}

// removes redundant spaces from a string

void						VM::UniqueWhiteSpaces()
{
	int 					i;
	std::string::iterator 	start;
	std::string::iterator 	end;

	for (auto &elem : input_file)
	{
		end = std::unique(elem.begin(), elem.end(), [](char ch1, char ch2) -> bool
		{
			return (std::isspace(ch1) && isspace(ch2) && (ch1 == ch2));
		});
		elem = std::string(elem.begin(), end);
	}
	i = 0;
	RemoveBlankString();
	while (i < input_file.size())
	{
		if (input_file[i] == " ")
		{
			input_file.erase(input_file.begin() + i);
			i = 0;
			continue ;
		}
		else
		{
			start = input_file[i].begin();
			end = input_file[i].end() - 1;
			if (*start == ' ')
				start++;
			if (*end == ' ')
				end--;
			input_file[i] = std::string(start, end + 1);
		}
		i++;
	}
}

// default constructor

VM::VM()
{
	factory = std::make_shared<OperandFactory>(OperandFactory());
}

VM::VM(std::string f_name)
{
	std::string		buff;
	std::ifstream	inp(f_name);

	if (inp.is_open())
	{
		while (std::getline(inp, buff))
			input_file.push_back(buff);
	}
	else
	{
		std::cout << "I can't open a file." << std::endl;
		exit(0);
	}
	factory = std::make_shared<OperandFactory>(OperandFactory());
}

// copy constructor

VM::VM(VM const &vm)
{
	input_file = vm.input_file;
	val_stack = vm.val_stack;
	factory = std::make_shared<OperandFactory>(*(vm.factory));
}

// assignment operator overloading

VM 	&VM::operator=(VM const &vm)
{
	input_file = vm.input_file;
	val_stack = vm.val_stack;
	factory = std::make_shared<OperandFactory>(*(vm.factory));
	return (*this);
}

// destructor

VM::~VM()
{

}