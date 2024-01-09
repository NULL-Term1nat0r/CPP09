/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:20:14 by estruckm          #+#    #+#             */
/*   Updated: 2024/01/08 20:20:14 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string exchangeFile, std::string inputFile) {
	_storeExchangeRates(exchangeFile);
	_storeAccountInfo(inputFile);
}

BitcoinExchange::BitcoinExchange(void) {
	_storeExchangeRates("data.csv");
	_storeAccountInfo("input.csv");
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) {
	*this = src;
}

BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const char *BitcoinExchange::InvalidFileException::what() const throw() {
	return "Invalid file";
}

void BitcoinExchange::test() {
	Date a = Date("2024-12-01");
}

bool BitcoinExchange::isValidNumber(std::string number) {
	int length = number.length();
	if (length == 0)
		return false;
	if (length > 1 && (number[0] == '-' || number[0] == '+') && number[1] == '0')
		return false;
	if (length > 1 && number[0] == '0' && number[1] != '.' && number[1] != 'f')
		return false;
	if (length == 1 && (number[0] == '-' || number[0] == '+'))
		return false;
	int dotCounter = 0;
	for (std::size_t i = 0; i < length; ++i) {
		if (!isdigit(number[i])) {
			if (i == 0 && (number[i] == '-' || number[i] == '+'))
				continue;
			if (number[i] == '.' && dotCounter == 0)  {
				++dotCounter;
				continue;
			}
			if (i == length - 1 && number[i] == 'f')
				return true;
			else
				return false;
		}
	}
	return true;  // All characters are digits
}


std::string BitcoinExchange::_nearestDate(std::string date) {
	std::map<std::string, std::string>::iterator it = _exchangeRates.begin();
	std::map<std::string, std::string>::iterator end = _exchangeRates.end();
	std::string nearestDate = it->first;
	while (it != end) {
		if (std::abs(std::stof(it->first) - std::stof(date)) < std::abs(std::stof(nearestDate) - std::stof(date)))
			nearestDate = it->first;
		it++;
	}
	return nearestDate;
}

void BitcoinExchange::_storeExchangeRates(std::string file) {
	_isValidFile(file);
	std::ifstream f(file);
	std::string line = _getLine(f);
	while (f.good()) {
		std::string line = _getLine(f);
		_exchangeRates[_getDate(line)] = _getPrice(line);
	}
}

void BitcoinExchange::_storeAccountInfo(std::string file) {
	_isValidFile(file);
	std::ifstream f(file);
	std::string line = _getLine(f);
	while (f.good()) {
		std::string line = _getLine(f);
		_accountInfo[_getDate(line)] = _getAmount(line);
	}
}

void BitcoinExchange::getAccountBalance() {
	std::map<std::string, std::string>::iterator it = _accountInfo.begin();
	std::map<std::string, std::string>::iterator end = _accountInfo.end();

	while (it != end) {
		std::string date = it->first;
		std::string amount = it->second;
		std::string nearestDate = _nearestDate(date);
		std::string price = _exchangeRates[nearestDate];
		float balance = std::stof(amount) * std::stof(price);
		std::cout << cyan << date << " " << amount << " " << nearestDate << " " << price << " " << balance << resetColor << std::endl;
		it++;
	}
}

void BitcoinExchange::_isValidFile(std::string file){
	std::ifstream f(file);
	if (!f.good())
		throw InvalidFileException();
}

void BitcoinExchange::_isValidInput(std::string input) {
	_isValidFile(input);
	std::ifstream f(input);
	std::string line = _getLine(f);
	while (f.good()) {
		std::string line = _getLine(f);
		_accountInfo[_getDate(line)] = _getAmount(line);
		std::cout << _getDate(line) << " " << _getAmount(line) << std::endl;
	}
	_printMapContainer(_accountInfo);

}

std::string BitcoinExchange::_getLine(std::ifstream &f) {
	std::string line;
	std::getline(f, line);
	return line;
}

std::string BitcoinExchange::_getDate(std::string &line) {
	std::string date;
	std::stringstream ss(line);
	std::getline(ss, date, ',');
	return date;
}

std::string BitcoinExchange::_getAmount(std::string &line) {
	std::string amount;
	int start = line.find(",") + 1;
	while (line[start] == ' ')
		start++;
	int end = line.find("\n", start);
	amount = line.substr(start, end - start);
	return amount;
}

std::string BitcoinExchange::_getPrice(std::string &line) {
	std::string price;
	int start = line.find(",") + 1;
	while (line[start] == ' ')
		start++;
	int end = line.find("\n", start);
	price = line.substr(start, end - start);
	return price;
}

void BitcoinExchange::_printMapContainer(std::map <std::string, std::string> &container) {
	std::map<std::string, std::string>::iterator it = container.begin();
	std::map<std::string, std::string>::iterator end = container.end();
	while (it != end) {
		std::cout << cyan << it->first << " " << it->second << resetColor << std::endl;
		it++;
	}
}
