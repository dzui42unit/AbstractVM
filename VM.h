/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:21:29 by dzui              #+#    #+#             */
/*   Updated: 2017/11/28 19:21:32 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ABSTRACTVM_VM_H
#define ABSTRACTVM_VM_H

#include "Operand.h"
#include "OperandFactory.h"
#include <memory>
#include <utility>
#include <fstream>
#include <regex>
#include <exception>

class 													VM
{
private:
	bool 												valid;
	bool 												exit_instr;
	std::vector<std::string>							errors;
	std::vector<std::string>							input_file;
	std::vector<std::string>							reg_patterns;
	std::shared_ptr<OperandFactory>						factory;
	std::vector<IOperand const *>						val_stack;
	std::vector< std::pair<std::string, bool > >		instr_set;
	std::vector<std::pair<std::string, std::string> >	instr_args;

	void												AssignRegexPatternsSet();
	void												AssignInstructionsSet();
	int 												FindInstruction(const std::string &instr);
	int 												CheckArgument(const std::string &arg);
	int 												CountParenthesis(const std::string &str) const;
public:
														VM();
	explicit											VM(std::vector<std::string> inp_f);
	explicit											VM(std::string f_name);
														~VM();
														VM(VM const &vm);
	VM 													&operator=(VM const &vm);

	void												push(std::string argument);
	void												dump() const;
	void												add();
	void												pop();
	void												mul();
	void												assert(std::string argument);
	void												sub();
	void												div();
	void												mod();
	void												print();

	void												MakeInstructionsSet(void);
	void												RemoveComment(void);
	void												WhitesSpaceToSpace(void);
	void												UniqueWhiteSpaces(void);
	void 												RemoveBlankString(void);
	void												SplitString(std::vector<std::string> &res, std::string const &str, char del);
	void												CheckErrors();
	void												PrintErrors() const;
	void												RunInstructions();
	std::string											TrimString(std::string str);
	int 												WsString(std::string const &str) const;
	eOperandType 										FindType(std::string const &str) const;
	std::string											RemoveSpaces(std::string str);

	class				NoExit : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Exit exception: \"exit\" instruction omitted.");
		}
	};

	class				SyntaxLexicalError : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Lexical / Syntax errors are in the file.");
		}
	};

	class				PopException : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Pop exception: stack is already empty, pop can not be executed.");
		}
	};

	class				AssertException : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Assert exception: instruction is not true.");
		}
	};

	class				StackException : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Stack exception: less elements than it needed to execute instruction.");
		}
	};

	class				PrintException : public std::exception
	{
	public:
		const char 	*what() const throw() override
		{
			return ("Print exception: the value is not a int8 type.");
		}
	};
};


#endif //ABSTRACTVM_VM_H
