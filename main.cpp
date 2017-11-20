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
#include "Int8.h"

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
	std::shared_ptr<Int8> n1(new Int8(35));
	std::shared_ptr<Int8> n2(new Int8(12));
	std::cout << "n1: " << n1->getValue() << std::endl;
	std::cout << "n2: " << n2->getValue() << std::endl;
	*n1 = *(*n1 + *n2);
	std::cout << "n1: " << n1->getValue() << std::endl;
	std::cout << "n2: " << n2->getValue() << std::endl;
	return (0);
}
