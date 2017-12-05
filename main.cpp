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

#include "VM.h"

int		main(int argc, char **argv)
{
	std::vector<std::shared_ptr<VM>>		run_vm;

	if (argc == 1)
	{
		std::cout << "Please give me a file to work with." << std::endl;
		exit(0);
	}
	else
	{
		for (int i = 1; i < argc; i++)
			run_vm.emplace_back(std::make_shared<VM>(VM(argv[i])));
		for (int i = 0; i < run_vm.size(); i++)
		{
			(*run_vm[i]).RemoveComment();
			(*run_vm[i]).WhitesSpaceToSpace();
			(*run_vm[i]).UniqueWhiteSpaces();
			(*run_vm[i]).MakeInstructionsSet();
			(*run_vm[i]).CheckErrors();
			(*run_vm[i]).push();
		}
	}
	return (0);
}