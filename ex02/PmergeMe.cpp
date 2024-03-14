/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:41 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/14 15:44:01 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) { }

PmergeMe::PmergeMe(const PmergeMe &src) { (void)src; }

PmergeMe::~PmergeMe(void) { }

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
	(void)src;
	return *this;
}

PmergeMe::t_vec_it PmergeMe::binary_search(uint_vec &v, unsigned int needle)
{
	if (v.size() < 1)
		return v.begin();

	t_vec_it start = v.begin();
	t_vec_it end = v.end() - 1;
	t_vec_it result = v.end();

	while (start <= end)
	{
		t_vec_it mid = start + std::distance(start, end) / 2;
		if (*mid <= needle)
			start = mid + 1;
		else
		{
			result = mid;
			end = mid - 1;
		}
	}
	return result;
}

PmergeMe::t_deq_it PmergeMe::binary_search(uint_deq &d, unsigned int needle)
{
	if (d.size() < 1)
		return d.begin();

	t_deq_it start = d.begin();
	t_deq_it end = d.end() - 1;
	t_deq_it result = d.end();

	while (start <= end)
	{
		t_deq_it mid = start + std::distance(start, end) / 2;
		if (*mid <= needle)
			start = mid + 1;
		else
		{
			result = mid;
			end = mid - 1;
		}
	}
	return result;
}

void PmergeMe::make_pairs(uint_vec &src, std::vector<t_int_pair> &dst)
{
	dst.clear();

	for (t_vec_it it = src.begin(); it + 1 < src.end(); it += 2)
	{
		if (*it > *(it + 1))
			dst.push_back(std::make_pair(*it, *(it + 1)));
		else
			dst.push_back(std::make_pair(*(it + 1), *it));
	}
}

void PmergeMe::make_pairs(uint_deq &src, std::deque<t_int_pair> &dst)
{
	dst.clear();

	for (t_deq_it it = src.begin(); it + 1 < src.end(); it += 2)
	{
		if (*it > *(it + 1))
			dst.push_back(std::make_pair(*it, *(it + 1)));
		else
			dst.push_back(std::make_pair(*(it + 1), *it));
	}
}

void PmergeMe::mergesort(std::vector<t_int_pair> &v)
{
	if (v.size() < 2)
		return;

	std::vector<t_int_pair> tmp(v.size());

	mergesort(v.begin(), v.end(), tmp);
}

void PmergeMe::mergesort(std::deque<t_int_pair> &d)
{
	if (d.size() < 2)
		return;

	std::deque<t_int_pair> tmp(d.size());

	mergesort(d.begin(), d.end(), tmp);
}

void PmergeMe::mergesort(t_pair_vec_it start, t_pair_vec_it end,
	std::vector<t_int_pair> &tmp)
{
	std::size_t size = std::distance(start, end);

	if (size <= 1)
		return;

	t_pair_vec_it mid = start + size / 2;

	mergesort(start, mid, tmp);
	mergesort(mid, end, tmp);
	merge(start, mid, end, tmp);
}

void PmergeMe::mergesort(t_pair_deq_it start, t_pair_deq_it end,
	std::deque<t_int_pair> &tmp)
{
	std::size_t size = std::distance(start, end);

	if (size <= 1)
		return;

	t_pair_deq_it mid = start + size / 2;

	mergesort(start, mid, tmp);
	mergesort(mid, end, tmp);
	merge(start, mid, end, tmp);
}

void PmergeMe::merge(t_pair_vec_it start, t_pair_vec_it mid,
	t_pair_vec_it end, std::vector<t_int_pair> &tmp)
{
	t_pair_vec_it left = start;
	t_pair_vec_it right = mid;

	tmp.clear();

	while (left != mid && right != end)
	{
		if (right->first < left->first)
		{
			tmp.push_back(*right);
			++right;
		}
		else
		{
			tmp.push_back(*left);
			++left;
		}
	}

	tmp.insert(tmp.end(), left, mid);
	tmp.insert(tmp.end(), right, end);
	std::copy(tmp.begin(), tmp.end(), start);
}

void PmergeMe::merge(t_pair_deq_it start, t_pair_deq_it mid,
	t_pair_deq_it end, std::deque<t_int_pair> &tmp)
{
	t_pair_deq_it left = start;
	t_pair_deq_it right = mid;

	tmp.clear();

	while (left != mid && right != end)
	{
		if (right->first < left->first)
		{
			tmp.push_back(*right);
			++right;
		}
		else
		{
			tmp.push_back(*left);
			++left;
		}
	}

	tmp.insert(tmp.end(), left, mid);
	tmp.insert(tmp.end(), right, end);
	std::copy(tmp.begin(), tmp.end(), start);
}

void PmergeMe::insert_second(uint_vec &chain, unsigned int n)
{
	t_vec_it pos = binary_search(chain, n);

	chain.insert(pos, n);
}

void PmergeMe::insert_second(uint_deq &chain, unsigned int n)
{
	t_deq_it pos = binary_search(chain, n);

	chain.insert(pos, n);
}


void PmergeMe::init_jacobs(t_jacobs &jacobs)
{
	jacobs.jacob_prev = 1;
	jacobs.jacob_cur = 1;
	jacobs.jacob_seq = 3;
	jacobs.next_pos = 1;
}

std::size_t PmergeMe::next_idx(t_jacobs &jacobs, size_t limit)
{
	if (jacobs.next_pos == jacobs.jacob_prev)
	{
		jacobs.jacob_prev = jacobs.jacob_cur;
		jacobs.jacob_cur *= 2;
		jacobs.jacob_cur += ((++jacobs.jacob_seq) % 2 ? -1 : 1);
		jacobs.next_pos = jacobs.jacob_cur;
	}
	if (--jacobs.next_pos >= limit)
		jacobs.next_pos = limit - 1;
	return jacobs.next_pos;
}

void PmergeMe::transfer_to_chain(std::vector<t_int_pair> &pend,
	uint_vec &chain)
{
	const t_pair_vec_it begin = pend.begin();
	t_jacobs jacobs;
	const std::size_t pend_size = pend.size();

	chain.clear();
	init_jacobs(jacobs);
	chain.push_back(begin->second);
	chain.push_back(begin->first);

	for (t_pair_vec_it it = pend.begin() + 1; it != pend.end(); ++it)
		chain.push_back(it->first);

	for (size_t i = 0; i < pend_size - 1; ++i)
	{
		std::size_t idx = next_idx(jacobs, pend_size);
		insert_second(chain, pend.at(idx).second);
	}
}

void PmergeMe::transfer_to_chain(std::deque<t_int_pair> &pend,
	uint_deq &chain)
{
	const t_pair_deq_it begin = pend.begin();
	t_jacobs jacobs;
	const std::size_t pend_size = pend.size();

	chain.clear();
	init_jacobs(jacobs);
	chain.push_back(begin->second);
	chain.push_back(begin->first);

	for (t_pair_deq_it it = pend.begin() + 1; it != pend.end(); ++it)
		chain.push_back(it->first);

	for (size_t i = 0; i < pend_size - 1; ++i)
	{
		std::size_t idx = next_idx(jacobs, pend_size);
		insert_second(chain, pend.at(idx).second);
	}
}

void PmergeMe::sort(uint_vec &v)
{
	bool has_straggler;
	unsigned int straggler;
	const size_t v_size = v.size();

	if (v_size < 2)
		return;

	if (v_size % 2)
	{
		has_straggler = true;
		straggler = v.back();
	}

	else
		has_straggler = false;

	std::vector<t_int_pair> pend(v_size / 2);

	make_pairs(v, pend);
	mergesort(pend);
	transfer_to_chain(pend, v);

	if (has_straggler)
		insert_second(v, straggler);
}

void PmergeMe::sort(uint_deq &d)
{
	bool has_straggler;
	unsigned int straggler;
	const size_t d_size = d.size();

	if (d_size < 2)
		return;

	if (d_size % 2)
	{
		has_straggler = true;
		straggler = d.back();
	}

	else
		has_straggler = false;

	std::deque<t_int_pair> pend(d_size / 2);

	make_pairs(d, pend);
	mergesort(pend);
	transfer_to_chain(pend, d);

	if (has_straggler)
		insert_second(d, straggler);
}

void PmergeMe::parse_input(int argc, char **argv, uint_vec &v)
{
	std::istringstream ss;
	std::string tmp_str;
	long tmp_num;

	for (int i = 1; i < argc; i++)
	{
		tmp_str = argv[i];
		if (tmp_str.size() == 0)
			throw std::domain_error("Invalid input => Empty string");
		ss.clear();
		ss.str(tmp_str);
		ss >> tmp_num;

		if (ss.fail() || !ss.eof() || tmp_num < 0
			|| tmp_num > std::numeric_limits<unsigned int>::max())
			throw std::domain_error("Invalid input => " + tmp_str);

		v.push_back(tmp_num);
	}
}

void PmergeMe::parse_input(int argc, char **argv, uint_deq &v)
{
	std::istringstream ss;
	std::string tmp_str;
	long tmp_num;

	for (int i = 1; i < argc; i++)
	{
		ss.clear();
		tmp_str = argv[i];
		ss.str(tmp_str);
		ss >> tmp_num;

		if (ss.fail() || !ss.eof() || tmp_num < 0
			|| tmp_num > std::numeric_limits<unsigned int>::max())
			throw std::domain_error("Invalid input => " + tmp_str);

		v.push_back(tmp_num);
	}
}

void PmergeMe::print_contents(uint_vec &v)
{
	uint_vec::iterator it;

	for (it = v.begin(); it != v.end() - 1; ++it)
		std::cout << *it << ' ';

	std::cout << *it << std::endl;
}

void PmergeMe::print_contents(uint_deq &d)
{
	uint_deq::iterator it;

	for (it = d.begin(); it != d.end() - 1; ++it)
		std::cout << *it << ' ';

	std::cout << *it << std::endl;
}

double PmergeMe::timed_vector_sort(int argc, char **argv, uint_vec &v)
{
	struct timespec start_time;
	struct timespec end_time;

	clock_gettime(CLOCK_MONOTONIC, &start_time);
	parse_input(argc, argv, v);
	PmergeMe::sort(v);
	clock_gettime(CLOCK_MONOTONIC, &end_time);

	return (end_time.tv_sec - start_time.tv_sec) * 1000000.0
		+ (end_time.tv_nsec - start_time.tv_nsec) / 1000.0;
}

double PmergeMe::timed_deque_sort(int argc, char **argv, uint_deq &d)
{
	struct timespec start_time;
	struct timespec end_time;

	clock_gettime(CLOCK_MONOTONIC, &start_time);
	parse_input(argc, argv, d);
	PmergeMe::sort(d);
	clock_gettime(CLOCK_MONOTONIC, &end_time);

	return (end_time.tv_sec - start_time.tv_sec) * 1000000.0
		+ (end_time.tv_nsec - start_time.tv_nsec) / 1000.0;
}
