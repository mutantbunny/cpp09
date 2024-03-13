/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:23 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/13 01:02:04 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
#include "RPN.hpp"

static void print_error(const char *name, const char* msg)
{
	std::cout << "Error: " << msg << ".\n";
	std::cout << "Usage: " <<  name << " \"expression in reverse polish "
		"notation containing single digits and arithmetic operations "
		"(+, -, / and *) separated by spaces\"" << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		print_error(argv[0], "Wrong number of arguments");
		return 1;
	}

	try
	{
		std::cout << RPN::calculate(argv[1]) << std::endl;
	}
	catch (const std::exception &e)
	{
		print_error(argv[0], e.what());
		return 1;
	}

	return 0;
}
