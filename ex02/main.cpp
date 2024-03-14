/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:23 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/14 15:44:16 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0]
			<< " <list of positive integers>" << std::endl;
		return 1;
	}

	std::vector<unsigned int> unsorted_vector;
	std::vector<unsigned int> sorted_vector;
	std::deque<unsigned int> sorted_deque;
	double vector_sort_time;
	double deque_sort_time;

	try
	{
		PmergeMe::parse_input(argc, argv, unsorted_vector);
		vector_sort_time = PmergeMe::timed_vector_sort(argc, argv,
			sorted_vector);
		deque_sort_time = PmergeMe::timed_deque_sort(argc, argv,
			sorted_deque);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	std::cout << "Before: ";
	PmergeMe::print_contents(unsorted_vector);
	std::cout << std::endl;
	std::cout << "After: ";
	PmergeMe::print_contents(sorted_vector);
	std::cout << std::endl;
	std::cout << "Time to process a range of " << sorted_vector.size()
		<< " elements with std::vector: " << vector_sort_time << " us"
		<< std::endl;
	std::cout << "Time to process a range of " << sorted_deque.size()
		<< " elements with std::deque: " << deque_sort_time << " us"
		<< std::endl;

	return 0;
}
