/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:48:14 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/12 21:58:27 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
# define PMERGE_HPP

# include <vector>
# include <deque>
//# include <utility>
# include <iostream>

class PmergeMe
{
	private:
		typedef std::pair<int, int> t_int_pair;
		typedef std::vector<int>::iterator t_vec_it;
		typedef std::deque<int>::iterator t_deq_it;
		typedef std::vector<t_int_pair>::iterator t_pair_vec_it;
		typedef std::deque<t_int_pair>::iterator t_pair_deq_it;

		typedef struct s_jacobs {
			std::size_t jacob_prev;
			std::size_t jacob_cur;
			std::size_t jacob_seq;
			std::size_t next_pos;
		} t_jacobs;

		static t_vec_it binary_search(std::vector<int> &v, int needle);
		static t_deq_it binary_search(std::deque<int> &d, int needle);

		static void make_pairs(std::vector<int> &src,
			std::vector<t_int_pair> &dst);
		static void make_pairs(std::deque<int> &src,
			std::deque<t_int_pair> &dst);

		static void mergesort(std::vector<t_int_pair> &v);
		static void mergesort(t_pair_vec_it start, t_pair_vec_it end,
			std::vector<t_int_pair> &tmp);
		static void merge(t_pair_vec_it start, t_pair_vec_it mid,
			t_pair_vec_it end, std::vector<t_int_pair> &tmp);

		static void mergesort(std::deque<t_int_pair> &d);
		static void mergesort(t_pair_deq_it start, t_pair_deq_it end,
			std::deque<t_int_pair> &tmp);
		static void merge(t_pair_deq_it start, t_pair_deq_it mid,
			t_pair_deq_it end, std::deque<t_int_pair> &tmp);

		static void insert_second(std::vector<int> &chain, int n);
		static void insert_second(std::deque<int> &chain, 	int n);

		static void transfer_to_chain(std::vector<t_int_pair> &pend,
			std::vector<int> &chain);
		static void transfer_to_chain(std::deque<t_int_pair> &pend,
			std::deque<int> &chain);

		static void init_jacobs(t_jacobs &jacobs);
		static std::size_t next_idx(t_jacobs &jacobs, size_t limit);

		PmergeMe(void);
		PmergeMe(const PmergeMe &src);
		~PmergeMe(void);
		PmergeMe &operator=(const PmergeMe &src);

	public:
		static void sort(std::vector<int> &v);
		static void sort(std::deque<int> &d);
};

#endif
