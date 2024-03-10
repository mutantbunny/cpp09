/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:35 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/02 22:30:36 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) { }

RPN::RPN(const RPN &src) { (void)src; }

RPN::~RPN(void) { }

RPN &RPN::operator=(const RPN &src)
{
	(void)src;
	return *this;
}

void RPN::check_size(const std::stack<int> &st)
{
	if (st.size() < 2)
		throw std::domain_error("Invalid format");
}

void RPN::add(std::stack<int> &st)
{
	check_size(st);

	int right = st.top();
	st.pop();

	int left = st.top();
	st.pop();

	st.push(left + right);
}

void RPN::divide(std::stack<int> &st)
{
	check_size(st);

	int right = st.top();
	st.pop();

	int left = st.top();
	st.pop();

	st.push(left / right);
}

void RPN::multiply(std::stack<int> &st)
{
	check_size(st);

	int right = st.top();
	st.pop();

	int left = st.top();
	st.pop();

	st.push(left * right);
}

void RPN::subtract(std::stack<int> &st)
{
	check_size(st);

	int right = st.top();
	st.pop();

	int left = st.top();
	st.pop();

	st.push(left - right);
}

int RPN::calculate(const std::string &ops)
{
	std::stack<int> st;

	for (size_t i = 0; i < ops.size(); ++i)
	{
		char ch = ops[i];

		if (std::isdigit(ch))
		{
			st.push(static_cast<int>(ch - '0'));
			continue;
		}

		switch(ch)
		{
			case ' ':
				continue;

			case '+':
				add(st);
				continue;

			case '/':
				divide(st);
				continue;

			case '*':
				multiply(st);
				continue;

			case '-':
				subtract(st);
				continue;
		}

		throw std::domain_error("Invalid format");
	}

	if (st.size() != 1)
		throw std::domain_error("Invalid format");

	return st.top();
}
