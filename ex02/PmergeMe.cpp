/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coelho <coelho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:41 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/11 05:10:12 by coelho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstddef>
#include <iterator>

PmergeMe::PmergeMe(void) { }

PmergeMe::PmergeMe(const PmergeMe &src) { (void)src; }

PmergeMe::~PmergeMe(void) { }

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
	(void)src;
	return *this;
}

PmergeMe::t_deq_it PmergeMe::binary_search(t_deq_it start, t_deq_it end,
	int needle)
{
	if (start >= end)
		return start;

	t_deq_it mid = start + (std::distance(start, end) / 2);

	if (*mid == needle)
		return mid;

	if (*mid > needle)
		return binary_search(start, mid, needle);

	return binary_search(mid, end, needle);
}

PmergeMe::t_vec_it PmergeMe::binary_search(t_vec_it start,t_vec_it end,
	int needle)
{
	if (start >= end)
		return start;

	t_vec_it mid = start + (std::distance(start, end) / 2);

	if (*mid == needle)
		return mid;

	if (*mid > needle)
		return binary_search(start, mid, needle);

	return binary_search(mid, end, needle);
}

void PmergeMe::make_pairs(std::vector<int> &src, std::vector<t_int_pair> &dst)
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

void PmergeMe::make_pairs(std::deque<int> &src, std::deque<t_int_pair> &dst)
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

void PmergeMe::mergesort(t_pair_vec_it start, t_pair_vec_it end,
	std::vector<t_int_pair> tmp)
{
	std::size_t dist = std::distance(start, end);

	if (dist <= 1)
		return;

	t_pair_vec_it mid = start + (std::distance(start, end) / 2);

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
		if (*right < *left)
			tmp.push_back(*right);
		else
			tmp.push_back(*left);
	}

	tmp.insert(tmp.end(), left, mid);
	tmp.insert(tmp.end(), right, end);
	std::copy(tmp.begin(), tmp.end(), start);
}

void PmergeMe::mergesort(std::deque<t_int_pair> &d)
{
	if (d.size() < 2)
		return;

	std::deque<t_int_pair> tmp(d.size());

	mergesort(d.begin(), d.end(), tmp);
}

void PmergeMe::mergesort(t_pair_deq_it start, t_pair_deq_it end,
	std::deque<t_int_pair> tmp)
{
	std::size_t dist = std::distance(start, end);

	if (dist <= 1)
		return;

	t_pair_deq_it mid = start + (std::distance(start, end) / 2);

	mergesort(start, mid, tmp);
	mergesort(mid, end, tmp);
	merge(start, mid, end, tmp);
}

void PmergeMe::merge(t_pair_deq_it start, t_pair_deq_it mid,
	t_pair_deq_it end, std::deque<t_int_pair> &tmp)
{
	t_pair_deq_it left = start;
	t_pair_deq_it right = mid;

	tmp.clear();

	while (left != mid && right != end)
	{
		if (*right < *left)
			tmp.push_back(*right);
		else
			tmp.push_back(*left);
	}

	tmp.insert(tmp.end(), left, mid);
	tmp.insert(tmp.end(), right, end);
	std::copy(tmp.begin(), tmp.end(), start);
}

void PmergeMe::insert_second(std::vector<int> &chain, int n)
{

}

void PmergeMe::insert_second(std::deque<int> &chain, int n)
{

}

void PmergeMe::transfer_to_chain(std::vector<t_int_pair> &pend,
	std::vector<int> &chain)
{
	t_pair_vec_it begin = pend.begin();
	std::size_t jacobsthal = 3;
	std::size_t seq_pos = 4;

	chain.clear();
	chain.push_back(begin->second);
	chain.push_back(begin->first);

	for (t_pair_vec_it it = pend.begin(); it != pend.end(); ++it)
		chain.push_back(it->first);


}

void PmergeMe::transfer_to_chain(std::deque<t_int_pair> &pend,
	std::deque<int> &chain)
{

}

void PmergeMe::sort(std::vector<int> &v)
{
	bool has_straggler;
	int straggler;

	if (v.size() % 2)
	{
		has_straggler = true;
		straggler = v.back();
		v.pop_back();
	}
	else
		has_straggler = false;

	std::vector<t_int_pair> pend(v.size() / 2);

	make_pairs(v, pend);
	mergesort(pend);


}

void PmergeMe::sort(std::deque<int> &d)
