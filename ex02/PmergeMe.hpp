/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:48:14 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/14 15:44:32 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
# define PMERGE_HPP

# include <vector>
# include <deque>
# include <iostream>
# include <sstream>
# include <ctime>
# include <limits>

class PmergeMe
{
	private:
		typedef std::vector<unsigned int> uint_vec;
		typedef std::deque<unsigned int> uint_deq;
		typedef std::pair<unsigned int, unsigned int> t_int_pair;
		typedef uint_vec::iterator t_vec_it;
		typedef uint_deq::iterator t_deq_it;
		typedef std::vector<t_int_pair>::iterator t_pair_vec_it;
		typedef std::deque<t_int_pair>::iterator t_pair_deq_it;

		typedef struct s_jacobs {
			std::size_t jacob_prev;
			std::size_t jacob_cur;
			std::size_t jacob_seq;
			std::size_t next_pos;
		} t_jacobs;

		static t_vec_it binary_search(uint_vec &v, unsigned int needle);
		static t_deq_it binary_search(uint_deq &d, unsigned int needle);

		static void make_pairs(uint_vec &src, std::vector<t_int_pair> &dst);
		static void make_pairs(uint_deq &src, std::deque<t_int_pair> &dst);

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

		static void insert_second(uint_vec &chain, unsigned int n);
		static void insert_second(uint_deq &chain, 	unsigned int n);

		static void transfer_to_chain(std::vector<t_int_pair> &pend,
			uint_vec &chain);
		static void transfer_to_chain(std::deque<t_int_pair> &pend,
			uint_deq &chain);

		static void init_jacobs(t_jacobs &jacobs);
		static std::size_t next_idx(t_jacobs &jacobs, size_t limit);

		PmergeMe(void);
		PmergeMe(const PmergeMe &src);
		~PmergeMe(void);
		PmergeMe &operator=(const PmergeMe &src);

	public:
		static void print_contents(uint_vec &v);
		static void print_contents(uint_deq &d);
		static void parse_input(int argc, char **argv, uint_vec &v);
		static void parse_input(int argc, char **argv, uint_deq &d);
		static double timed_vector_sort(int argc, char **argv, uint_vec &v);
		static double timed_deque_sort(int argc, char **argv, uint_deq &d);
		static void sort(uint_vec &v);
		static void sort(uint_deq &d);
};

#endif
