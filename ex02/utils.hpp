/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:22:09 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/13 01:19:30 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <sstream>
# include <ctime>
# include "PmergeMe.hpp"

void print_contents(std::vector<int> &v);
void print_contents(std::deque<int> &d);
void parse_input(int argc, char **argv, std::vector<int> &v);
void print_vector_sort_time(int argc, char **argv);
void print_deque_sort_time(int argc, char **argv);

#endif
