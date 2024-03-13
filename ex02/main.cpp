/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:23 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/13 00:48:05 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	std::vector<int> v;
	std::deque<int> d;

	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0]
			<< " <list of positive integers>" << std::endl;
		return 1;
	}

	try
	{
		print_vector_sort_time(argc, argv);
		print_deque_sort_time(argc, argv);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error processing input: " << e.what() << std::endl;
	}

	return 0;
}
