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
#include <stack>
#include <utility>
#include <fstream>
#include <regex>

class 													VM
{
private:
	bool 												valid;
	bool 												exit_instr;
	std::vector<std::string>							errors;
	std::vector<std::string>							input_file;
	std::vector<std::string>							reg_patterns;
	std::shared_ptr<OperandFactory>						factory;
	std::stack<IOperand const *>						val_stack;
	std::vector< std::pair<std::string, bool > >		instr_set;
	std::vector<std::pair<std::string, std::string> >	instr_args;

	void												AssignRegexPatternsSet();
	void												AssignInstructionsSet();
	int 												FindInstruction(const std::string &instr);
	int 												CheckArgument(const std::string &arg);
	int 												CountParenthesis(const std::string &str) const;
public:
														VM();
	explicit											VM(std::string f_name);
														~VM();
														VM(VM const &vm);
	VM 													&operator=(VM const &vm);
	void												push();
	void												MakeInstructionsSet(void);
	void												RemoveComment(void);
	void												WhitesSpaceToSpace(void);
	void												UniqueWhiteSpaces(void);
	void 												RemoveBlankString(void);
	void												SplitString(std::vector<std::string> &res, std::string str, char del);
	void												CheckErrors();
	void												PrintErrors() const;
	void												CastObject(IOperand *ptr);
	std::string											RemoveSpaces(std::string str);
	std::vector<std::pair<std::string, std::string> >	getInstrSet() const;

};


#endif //ABSTRACTVM_VM_H
