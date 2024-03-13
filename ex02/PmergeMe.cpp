/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:41 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/12 23:04:04 by gmachado         ###   ########.fr       */
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

PmergeMe::t_vec_it PmergeMe::binary_search(std::vector<int> &v, int needle)
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

PmergeMe::t_deq_it PmergeMe::binary_search(std::deque<int> &d, int needle)
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

void PmergeMe::insert_second(std::vector<int> &chain, int n)
{
	t_vec_it pos = binary_search(chain, n);

	chain.insert(pos, n);
}

void PmergeMe::insert_second(std::deque<int> &chain, int n)
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
	std::vector<int> &chain)
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
	std::deque<int> &chain)
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

void PmergeMe::sort(std::vector<int> &v)
{
	bool has_straggler;
	int straggler;
	const int v_size = v.size();

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

void PmergeMe::sort(std::deque<int> &d)
{
	bool has_straggler;
	int straggler;
	const int d_size = d.size();

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
