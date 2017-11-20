/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int8.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:59:35 by dzui              #+#    #+#             */
/*   Updated: 2017/11/20 17:59:36 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_INT8_H
#define ABSTRACTVM_INT8_H

#include "IOperand.h"

class 					Int8 : public  IOperand
{
private:
	int 				value;
	int 				prec;
	std::string			str_val;
	eOperandType 		type;
public:
						Int8() = delete;
						~Int8() final;
						Int8(const Int8 &rhs);
	Int8				&operator=(IOperand const &rhs);
	explicit			Int8(int nb);

	int 				getValue() const;
	int 				getPrecision(void) const override ;
	eOperandType 		getType() const override;
	const std::string 	&toString() const override;
	IOperand const 		*operator+(IOperand const &rhs) const override;
	IOperand const 		*operator-(IOperand const &rhs) const override;
	IOperand const 		*operator/(IOperand const &rhs) const override;
	IOperand const 		*operator%(IOperand const &rhs) const override;
	IOperand const 		*operator*(IOperand const &rhs) const override;
};


#endif //ABSTRACTVM_INT8_H
