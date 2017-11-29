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
		std::cout << "I need to process following files:" << std::endl;
		for (int i = 1; i < argc; i++)
		{
			std::cout << argv[i] << std::endl;
			run_vm.emplace_back(std::make_shared<VM>(VM(argv[i])));
		}
		for (int i = 0; i < argc - 1; i++)
		{
			std::vector<std::string> info = (*run_vm[i]).FileContetnt();
			std::cout << std::endl << std::endl << "Files content:" << std::endl;
			for (const auto &j : info)
				std::cout << "|" << j << "|" << std::endl;
			(*run_vm[i]).RemoveComment();
			(*run_vm[i]).WhitesSpaceToSpace();
			(*run_vm[i]).UniqueWhiteSpaces();
		}
		for (int i = 0; i < argc - 1; i++)
		{
			std::cout << std::endl << std::endl << "Files content:" << std::endl;
			std::vector<std::string> info = (*run_vm[i]).FileContetnt();
			for (const auto &j : info)
				std::cout << "|" << j << "|" << std::endl;
		}

	}
	return (0);
}