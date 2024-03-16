/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:35 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/15 21:25:57 by gmachado         ###   ########.fr       */
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

void RPN::check_size(const std::stack<int, std::list<int> > &st)
{
	if (st.size() < 2)
		throw std::domain_error("Invalid format");
}

void RPN::add(std::stack<int, std::list<int> > &st)
{
	check_size(st);

	int right = st.top();
	st.pop();

	int left = st.top();
	st.pop();

	st.push(left + right);
}

void RPN::divide(std::stack<int, std::list<int> > &st)
{
	check_size(st);

	int right = st.top();
	st.pop();

	int left = st.top();
	st.pop();

	if (right == 0)
		throw std::domain_error("Integer divide by zero");

	st.push(left / right);
}

void RPN::multiply(std::stack<int, std::list<int> > &st)
{
	check_size(st);

	int right = st.top();
	st.pop();

	int left = st.top();
	st.pop();

	st.push(left * right);
}

void RPN::subtract(std::stack<int, std::list<int> > &st)
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
	std::stack<int, std::list<int> > st;
	bool should_be_space = false;

	for (size_t i = 0; i < ops.size(); ++i)
	{
		char ch = ops[i];

		if (should_be_space)
		{
			if (ch != ' ')
				throw std::domain_error("Invalid format");
			should_be_space = false;
		}

		if (std::isdigit(ch))
		{
			st.push(static_cast<int>(ch - '0'));
			should_be_space = true;
			continue;
		}

		switch(ch)
		{
			case ' ':
				should_be_space = false;
				continue;

			case '+':
				add(st);
				should_be_space = true;
				continue;

			case '/':
				divide(st);
				should_be_space = true;
				continue;

			case '*':
				multiply(st);
				should_be_space = true;
				continue;

			case '-':
				subtract(st);
				should_be_space = true;
				continue;
		}

		throw std::domain_error("Invalid format");
	}

	if (st.size() != 1)
		throw std::domain_error("Invalid format");

	return st.top();
}
