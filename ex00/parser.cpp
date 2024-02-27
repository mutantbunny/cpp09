/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 03:14:54 by gmachado          #+#    #+#             */
/*   Updated: 2024/02/26 22:53:22 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <exception>


static double parse_number(std::string num_str)
{
	if ((!std::isdigit(num_str[0]) && num_str[0] != '-' && num_str[0] != '+')
		|| !std::isdigit(num_str[num_str.size() - 1]))
		throw std::domain_error("Value format error");

	bool found_dot = false;

	for (size_t i = 0; i < num_str.size() - 1; ++i)
	{
		if (num_str[i] == '.')
		{
			if (found_dot)
				throw std::domain_error("Value format error");
			found_dot = true;
		}
		else if (!std::isdigit(num_str[i]))
			throw std::domain_error("Value format error");
	}

	double value = std::atof(num_str.substr(11).c_str());

	if (value > 2147483648)
		throw std::domain_error("Too large a number");

	if (value < 0)
		throw std::domain_error("Not a positive number");

	return value;
}

static std::string parse_date(std::string date_str)
{
	if (!std::isdigit(date_str[0]) || !std::isdigit(date_str[1])
		|| !std::isdigit(date_str[2]) || !std::isdigit(date_str[3])
		|| date_str[4] != '-'|| !std::isdigit(date_str[5])
		|| !std::isdigit(date_str[6]) || date_str[7] != '-'
		|| !std::isdigit(date_str[8]) || !std::isdigit(date_str[9]))
		throw std::domain_error("Date format error");

	int year = std::atoi(date_str.substr(0,4).c_str());
	if (year < 0)
		throw std::domain_error("Year format error");

	int month = std::atoi(date_str.substr(5,2).c_str());
	if (month < 1 || month > 12)
		throw std::domain_error("Month format error");

	int day = std::atoi(date_str.substr(8,2).c_str());

	if (day < 1)
		throw std::domain_error("Day format error");

	switch(month)
	{
		case 4:
		case 6:
		case 9:
		case 11:
			if (day > 30)
				throw std::domain_error("Day format error");
		case 2:
			if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
			{
				if (day > 29)
					throw std::domain_error("Day format error");
				else if (day > 28)
					throw std::domain_error("Day format error");
			}
		default:
			if (day > 31)
				throw std::domain_error("Day format error");
	}

	return date_str;
}

static std::pair<std::string, double> parse_csv_line(std::string line)
{
	if (line.size() < 12 || line[10] != ',')
		throw std::domain_error("Line format error");

	std::string parse_date(line.substr(0, 10));
	double value = parse_number(line.substr(11));
	return std::pair<std::string, double>(line.substr(0,10), value);
}

std::map<std::string, double> *load_csv(const std::string &filename)
{
	std::map<std::string, double> *m = new std::map<std::string, double>();
	std::ifstream csv;
	std::string date;
	double value;

	csv.exceptions(std::ios::failbit);
	csv.open(filename.c_str());

	while (!csv.eof())
	{
		std::string line;
		try
		{
			std::getline(csv, line);
		}
		catch (std::ios_base::failure &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
			delete m;
			return NULL;
		}
		try
		{
			std::pair<std::string, double> parsed_line = parse_csv_line(line);
			m->insert(parsed_line);
		}
		catch (std::exception &e) {
			std::cerr << "Error parsing line: " << e.what() << std::endl;
		}
	}

	return m;
}

static std::pair<std::string, double> parse_txt_line(std::string line)
{
	if (line.size() < 12
		|| line[10] != ' ' || line[11] != '|' || line[12] != ' ')
		throw std::domain_error("Line format error");

	std::string parse_date(line.substr(0, 10));
	double value = parse_number(line.substr(13));
	return std::pair<std::string, double>(line.substr(0,10), value);
}
