/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:38 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/02 22:02:12 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <exception>

class RPN
{
	public:
		RPN(void);
		RPN(const RPN &src);

		~RPN(void);

		RPN &operator=(const RPN &src);

		static int calculate(const std::string &ops);
		static void add(std::stack<int> &st);
		static void divide(std::stack<int> &st);
		static void multiply(std::stack<int> &st);
		static void subtract(std::stack<int> &st);
		static void check_size(const std::stack<int> &st);

};

#endif
