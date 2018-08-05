/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 12:50:23 by dzui              #+#    #+#             */
/*   Updated: 2018/08/05 12:50:27 by dzui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_EXCEPTIONS_H
#define ABSTRACTVM_EXCEPTIONS_H

#include <exception>

class				Overflow : public std::exception
{
public:
	const char 	*what() const throw() override;
};

class				Underflow : public std::exception
{
public:
	const char 	*what() const throw() override;
};

class				ZeroDiv : public std::exception
{
public:
	const char 	*what() const throw() override;
};

class				ZeroMod : public std::exception
{
public:
	const char 	*what() const throw() override;
};

#endif
