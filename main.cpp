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

	if (argc == 1)
	{
		std::shared_ptr<VM>			vm;
		std::vector<std::string>	input_data;

		std::string	buff;
		while (buff != ";;")
		{
			std::getline(std::cin, buff);
			input_data.push_back(buff);
		}
		vm = std::make_shared<VM>(VM(input_data));
		try
		{
			vm->RemoveComment();
			vm->WhitesSpaceToSpace();
			vm->UniqueWhiteSpaces();
			vm->MakeInstructionsSet();
			vm->CheckErrors();
			vm->RunInstructions();
		}
		catch (VM::SyntaxLexicalError &e)
		{
			std::cout << e.what() << std::endl;
			vm->PrintErrors();
		}
		catch (VM::NoExit &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	else
	{
		std::vector<std::shared_ptr<VM>>		run_vm;

		for (int i = 1; i < argc; i++)
			run_vm.emplace_back(std::make_shared<VM>(VM(argv[i])));
		for (auto &i : run_vm)
		{
			try
			{
				i->RemoveComment();
				i->WhitesSpaceToSpace();
				i->UniqueWhiteSpaces();
				i->MakeInstructionsSet();
				i->CheckErrors();
				i->RunInstructions();
			}
			catch (VM::SyntaxLexicalError &e)
			{
				std::cout << e.what() << std::endl;
				i->PrintErrors();
			}
			catch (VM::NoExit &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
	return (0);
}