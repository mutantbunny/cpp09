/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:48:14 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/10 03:43:28 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
# define PMERGE_HPP

# include <vector>
# include <list>
# include <string>

class PmergeMe
{
	private:
		bool hasStraggler;
		int straggler;
		std::size_t prevPrevjacobsthal;
		std::size_t prevJacobsthal;
		std::size_t curJacobsthal;
		std::vector<int> chainList;
		std::vector<int> pendList;
		std::list<int> mainList;
		std::vector<int> mainVector;

		void mergeSort(std::list<int>::iterator first,
			std::list<int>::iterator last, size_t size);
		void mergeSort(std::vector<int>::iterator first,
			std::vector<int>::iterator last, size_t size);

		void insertionSort(std::list<int>::iterator first,
			std::list<int>::iterator last, size_t size);
		void insertionSort(std::vector<int>::iterator first,
			std::vector<int>::iterator last, size_t size);



		std::size_t binarySearch(int n);
		void initJacobsthal(void);
		std::size_t nextJacobsthal(void);

	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe &src);
		PmergeMe(const std::string &str);
		~PmergeMe(void);
		PmergeMe &operator=(const PmergeMe &src);

};

#endif
