/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:02:54 by dzui              #+#    #+#             */
/*   Updated: 2017/11/20 17:02:55 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.h"
#include "Operand.h"

void	add_ints(int lhs, int rhs)
{
	std::cout << lhs + rhs << std::endl;
	if (lhs >= 0)
	{
		if (std::numeric_limits<int>::max() - lhs < rhs)
		{
			std::cout << "Overflow\n";
		}
	}
	else
	{
		if (std::numeric_limits<int>::min() - lhs > rhs)
		{
			std::cout << "Underflow\n";
		}
	}
}

int		main(void)
{
	Operand<char>	i("-41");
	Operand<double> d("45.2");
	Operand<short>	c("-423");

//	std::cout << "CHAR object = " << i.toString() << std::endl;
//	std::cout << "DOUBLE object = " << d.toString() << std::endl;
//	std::cout << "CHAR object = " << c.toString() << std::endl;

	Operand<int> kek;
	kek = *(i + c);
	std::cout << "int that stores result of addition of two chars: " << kek.toString() << std::endl;
	return (0);
}
