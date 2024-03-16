/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:23 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/16 16:27:11 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " filename" << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange exchange("data.csv");
		exchange.process_input_file(argv[1]);
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: " << e.what()  << std::endl;
	}


	return 0;
}
