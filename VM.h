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
#include <fstream>

class 										VM
{
private:
	std::vector<std::string>				input_file;
	std::shared_ptr<OperandFactory>			factory;
	std::stack< std::shared_ptr<IOperand> >	val_stack;


public:
											VM();
	explicit								VM(std::string f_name);
											~VM();
											VM(VM const &vm);
	VM 										&operator=(VM const &vm);
	std::vector<std::string>				FileContetnt(void) const;
	void									RemoveComment(void);
	void									WhitesSpaceToSpace(void);
	void									UniqueWhiteSpaces(void);
	void 									RemoveBlankString(void);
};


#endif //ABSTRACTVM_VM_H
