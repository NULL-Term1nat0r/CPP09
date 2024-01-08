/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:20:22 by estruckm          #+#    #+#             */
/*   Updated: 2024/01/08 20:20:22 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <iomanip>
# include <sstream>
# include <fstream>
# include <vector>
# include <map>
# include <algorithm>
# include <iterator>
# include <exception>
# include <stdexcept>
# include <ctime>
# include <cmath>

#include "Colors.hpp"
#include "Date.hpp"

class BitcoinExchange {
	public:
		BitcoinExchange(std::string exchangeFile, std::string inputFile);
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const &src);
		~BitcoinExchange(void);
		BitcoinExchange &operator=(BitcoinExchange const &rhs);
		void _isValidInput(std::string input);
		void getAccountBalance();
		void test();

	private:
		std::map<std::string, std::string> _exchangeRates;
		std::map<std::string, std::string> _accountInfo;

		void _storeExchangeRates(std::string file);
		void _storeAccountInfo(std::string file);

		void _printMapContainer(std::map<std::string, std::string> &container);

		void _isValidFile(std::string file);
		std::string _getLine(std::ifstream &f);
		std::string _getDate(std::string &line);
		std::string _getAmount(std::string &line);
		std::string _getPrice(std::string &line);
		void _isValidDate(std::string date);
		void _isValidAmount(std::string amount);

		bool isValidNumber(std::string s);
		std::string _nearestDate(std::string date);
		class InvalidFileException : public std::exception {
		public:
			virtual const char *what() const throw();
		};
};

#endif
