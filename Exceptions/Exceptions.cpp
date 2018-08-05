/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 12:50:03 by dzui              #+#    #+#             */
/*   Updated: 2018/08/05 12:50:05 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.h"

const char 	*Overflow::what() const throw()
{
	return ("Type Overflow occurred.");
}

const char 	*Underflow::what() const throw()
{
	return ("Type Underflow occurred.");
}

const char 	*ZeroDiv::what() const throw()
{
	return ("Zero as a second argument in division operation occurred.");
}

const char 	*ZeroMod::what() const throw()
{
	return ("Zero as a second argument in modulus operation occurred.");
}
