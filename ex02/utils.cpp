/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:22:14 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/13 00:49:24 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void parse_input(int argc, char **argv, std::vector<int> &v)
{
	std::istringstream ss;
	std::string tmp_str;
	int tmp_num;

	for (int i = 1; i < argc; i++)
	{
		ss.clear();
		tmp_str = argv[i];
		ss.str(tmp_str);
		ss >> tmp_num;

		if (ss.fail() || !ss.eof() || tmp_num < 0)
			throw std::domain_error("Invalid input => " + tmp_str);

		v.push_back(tmp_num);
	}
}

void parse_input(int argc, char **argv, std::deque<int> &v)
{
	std::istringstream ss;
	std::string tmp_str;
	int tmp_num;

	for (int i = 1; i < argc; i++)
	{
		ss.clear();
		tmp_str = argv[i];
		ss.str(tmp_str);
		ss >> tmp_num;

		if (ss.fail() || !ss.eof() || tmp_num < 0)
			throw std::domain_error("Invalid input => " + tmp_str);

		v.push_back(tmp_num);
	}
}

void print_contents(std::vector<int> &v)
{
	std::vector<int>::iterator it;

	for (it = v.begin(); it != v.end() - 1; ++it)
		std::cout << *it << ' ';

	std::cout << *it << std::endl;
}

void print_contents(std::deque<int> &d)
{
	std::deque<int>::iterator it;

	for (it = d.begin(); it != d.end() - 1; ++it)
		std::cout << *it << ' ';

	std::cout << *it << std::endl;
}

void print_vector_sort_time(int argc, char **argv)
{
	struct timespec start_time;
	struct timespec end_time;
	std::vector<int> to_sort;

	parse_input(argc, argv, to_sort);

	const std::size_t num_elems = to_sort.size();

	std::cout << "Before: ";
	print_contents(to_sort);

	clock_gettime(CLOCK_MONOTONIC, &start_time);
	PmergeMe::sort(to_sort);
	clock_gettime(CLOCK_MONOTONIC, &end_time);

	double elapsed_us = (end_time.tv_sec - start_time.tv_sec) * 1000000.0
		+ (end_time.tv_nsec - start_time.tv_nsec) / 1000.0;

	std::cout << "After: ";
	print_contents(to_sort);

	std::cout << "Time to process a range of " << num_elems
		<< " elements with std::vector: " << elapsed_us << " us" << std::endl;
}

void print_deque_sort_time(int argc, char **argv)
{
	struct timespec start_time;
	struct timespec end_time;
	std::deque<int> to_sort;

	parse_input(argc, argv, to_sort);

	const std::size_t num_elems = to_sort.size();

	clock_gettime(CLOCK_MONOTONIC, &start_time);
	PmergeMe::sort(to_sort);
	clock_gettime(CLOCK_MONOTONIC, &end_time);

	double elapsed_us = (end_time.tv_sec - start_time.tv_sec) * 1000000.0
		+ (end_time.tv_nsec - start_time.tv_nsec) / 1000.0;

	std::cout << "Time to process a range of " << num_elems
		<< " elements with std::deque: " << elapsed_us << " us" << std::endl;
}
