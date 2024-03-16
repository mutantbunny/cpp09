/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:47:18 by gmachado          #+#    #+#             */
/*   Updated: 2024/03/16 18:13:51 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <ctime>
# include <exception>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <iomanip>

class BitcoinExchange
{
	private:
		std::map<std::string, double> *db;

		static double parse_number(const std::string &num_str);
		static std::string parse_date(const std::string &date_str);
		static std::pair<std::string, double>
			parse_csv_line(const std::string &line);
		static std::pair<std::string, double>
			parse_input_line(const std::string &line);
		static void print_result(const std::string & date,
			const double amount, const double rate);

		void load_csv(const std::string &filename);

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange(const std::string &filename);

		~BitcoinExchange(void);

		BitcoinExchange &operator=(const BitcoinExchange &src);

		double get_exchange_rate(const std::string &date) const;
		void set_db(std::map<std::string, double> &new_db);
		void process_input_file(const char *filename);

		class EmptyDBException : public std::exception
		{
			public:
				EmptyDBException(void);
				EmptyDBException(const EmptyDBException &src);

				~EmptyDBException(void) throw();

				EmptyDBException &operator=(const EmptyDBException &src);
				virtual const char* what() const throw();
		};

		class NotFoundException : public std::exception
		{
			private:
				std::string m_msg;

			public:
				NotFoundException(void);
				NotFoundException(const NotFoundException &src);
				NotFoundException(const std::string &msg);

				virtual ~NotFoundException(void) throw();

				virtual NotFoundException
					&operator=(const NotFoundException &src);

				virtual const char* what() const throw();
		};
};

#endif
