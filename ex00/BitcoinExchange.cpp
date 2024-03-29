/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:14 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/16 19:40:28 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) : db(NULL) { }

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	db = new std::map<std::string, double>(*(src.db));
}

BitcoinExchange::BitcoinExchange(const std::string &filename) : db(NULL)
{
	load_csv(filename);
}

BitcoinExchange::~BitcoinExchange(void)
{
	delete db;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this == &src)
		return *this;

	delete db;
	db = new std::map<std::string, double>(*src.db);

	return *this;
}

double BitcoinExchange::get_exchange_rate(const std::string &date) const
{
	std::map<std::string, double>::iterator it;

	if (!db || db->empty())
		throw EmptyDBException();

	it = db->lower_bound(date);

	if (it == db->end())
		return (--it)->second;

	if (it->first == date)
		return it->second;

	if (it == db->begin())
		throw NotFoundException(date);

	return (--it)->second;
}

void BitcoinExchange::set_db(std::map<std::string, double> &new_db)
{
	delete db;
	db = new std::map<std::string, double>(new_db);
}

double BitcoinExchange::parse_number(const std::string &num_str)
{
	std::stringstream ss(num_str);
	double d;

	ss >> d;

	if (ss.fail() || !ss.eof())
		throw std::domain_error("bad input => " + num_str);

	if (d < 0)
		throw std::domain_error("not a positive number.");

	return d;
}

bool BitcoinExchange::is_valid_day(const std::tm &tm)
{
	switch(tm.tm_mon)
	{
		case 0:
		case 2:
		case 4:
		case 6:
		case 7:
		case 9:
		case 11:
			return tm.tm_mday > 31 ? false : true;

		case 3:
		case 5:
		case 8:
		case 10:
			return tm.tm_mday > 30 ? false : true;

		case 1:
			if (tm.tm_mday <= 28)
				return true;

			if (tm.tm_mday > 29)
				return false;

			int year = 1900 + tm.tm_year;

			if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
				return true;

			return false;
	}

	return false;
}

std::string BitcoinExchange::parse_date(const std::string &date_str)
{
	std::tm tm;

	if (!strptime(date_str.c_str(), "%Y-%m-%d", &tm))
		throw std::domain_error("bad input => " + date_str);

	if (!is_valid_day(tm))
		throw std::domain_error("bad input => " + date_str);

	return date_str;
}

void BitcoinExchange::load_csv(const std::string &filename)
{
	std::ifstream csv(filename.c_str());

	if (csv.fail())
	{
		delete this->db;
		this->db = NULL;
		throw std::runtime_error("Could not open database file");
	}

	this->db = new std::map<std::string, double>();
	std::string line;

	if (!std::getline(csv, line))
		return;

	while (std::getline(csv, line))
	{
		try
		{
			std::pair<std::string, double> parsed_line = parse_csv_line(line);
			db->insert(parsed_line);
		}
		catch (std::domain_error &e)
		{
			std::cerr << "Error: " << e.what() << " - while parsing database"
				<<std::endl;
		}

	}
}

std::pair<std::string, double>
	BitcoinExchange::parse_csv_line(const std::string &line)
{
	if (line.size() < 12 || line[10] != ',')
		throw std::domain_error("bad input => " + line);

	std::string date = BitcoinExchange::parse_date(line.substr(0, 10));
	double value = BitcoinExchange::parse_number(line.substr(11));
	return std::pair<std::string, double>(date, value);
}

std::pair<std::string, double>
	BitcoinExchange::parse_input_line(const std::string &line)
{
	if (line.size() < 12
		|| line[10] != ' ' || line[11] != '|' || line[12] != ' ')
		throw std::domain_error("bad input => " + line);

	std::string date = BitcoinExchange::parse_date(line.substr(0, 10));
	double value = BitcoinExchange::parse_number(line.substr(13));

	if (value > 1000)
		throw std::domain_error("too large a number.");

	return std::pair<std::string, double>(date, value);
}

void BitcoinExchange::print_result(const std::string & date,
			const double amount, const double rate)
{
	std::cout << date << " => " << amount << " = " << amount * rate <<std::endl;
}

void BitcoinExchange::process_input_file(const char *filename)
{
	std::ifstream infile(filename);

	if (infile.fail())
		throw std::runtime_error("Could not open input file");

	if (!db || db->empty())
		throw EmptyDBException();

	std::string line;

	if (!std::getline(infile, line))
		return;

	while (std::getline(infile, line))
	{
		std::pair<std::string, double> input_pair;

		try
		{
			input_pair = BitcoinExchange::parse_input_line(line);
			double rate = get_exchange_rate(input_pair.first);
			print_result(input_pair.first, input_pair.second, rate);
		}
		catch (NotFoundException &e)
		{
			std:: cerr << "Error: " << e.what() << std::endl;
		}
		catch (std::domain_error &e)
		{
			std:: cerr << "Error: " << e.what() << std::endl;
		}

	}
}

// Nested exception EmptyDBException

BitcoinExchange::EmptyDBException::EmptyDBException(void) { }

BitcoinExchange::EmptyDBException::
	EmptyDBException(const EmptyDBException &src) { (void)src; }

BitcoinExchange::EmptyDBException::~EmptyDBException(void) throw() { }

BitcoinExchange::EmptyDBException &BitcoinExchange::EmptyDBException::
	operator=(const EmptyDBException &src)
{
	(void)src;
	return *this;
}

const char* BitcoinExchange::EmptyDBException::what() const throw()
{
	return "Empty database";
}

// Nested exception class NotFoundException

BitcoinExchange::NotFoundException::NotFoundException(void) :
	m_msg("date not found") { }

BitcoinExchange::NotFoundException::NotFoundException(const
	BitcoinExchange::NotFoundException &src) : m_msg(src.m_msg) { }

BitcoinExchange::NotFoundException::NotFoundException(const std::string &date) :
	m_msg("date not found => " + date) { }

BitcoinExchange::NotFoundException::~NotFoundException(void) throw() { }

BitcoinExchange::NotFoundException &BitcoinExchange::NotFoundException::
	operator=(const NotFoundException &src)
{
	if (this == &src)
		return *this;

	m_msg= src.m_msg;
	return *this;
}

const char* BitcoinExchange::NotFoundException::what() const throw()
{
	return m_msg.c_str();
}
