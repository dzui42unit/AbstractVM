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
        try {
            std::shared_ptr <VM> vm;
            std::vector <std::string> input_data;

            std::string buff;
            while (buff != ";;") {
                std::getline(std::cin, buff);
                input_data.push_back(buff);
            }
            vm = std::make_shared<VM>(VM(input_data));

            vm->LexicalAnalysis();
//			vm->RemoveComment();
//			vm->WhitesSpaceToSpace();
//			vm->UniqueWhiteSpaces();
//			vm->MakeInstructionsSet();
//			vm->CheckErrors();
//			vm->RunInstructions();
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
	}
	else
    {
        try {
            std::vector <std::shared_ptr<VM>> run_vm;

            for (int i = 1; i < argc; i++)
                run_vm.emplace_back(std::make_shared<VM>(VM(argv[i])));
            for (auto &vm : run_vm)
            {
                vm->LexicalAnalysis();
//				vm->RemoveComment();
//				vm->WhitesSpaceToSpace();
//				vm->UniqueWhiteSpaces();
//				vm->MakeInstructionsSet();
//				vm->CheckErrors();
//				vm->RunInstructions();
            }
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
	}
	return (0);
}