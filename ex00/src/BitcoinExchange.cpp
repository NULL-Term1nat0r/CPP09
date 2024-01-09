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

const char *BitcoinExchange::InvalidFileContent::what() const throw() {
	return "Invalid file content";
}


void BitcoinExchange::test() {
	Date a = Date("20g8-02-29");
}


Date BitcoinExchange::_nearestDate(Date searchDate) {
	std::map<Date, double>::iterator it = _exchangeRates.begin();
	std::map<Date, double>::iterator end = _exchangeRates.end();
	if (it == end)
		throw InvalidFileContent();
	Date nearestDate = it->first;
	while (it != end) {
		if (it->first <= searchDate && (nearestDate <= it->first)) {
			nearestDate = it->first;
		}
		it++;
	}
	return nearestDate;
}

void BitcoinExchange::_storeExchangeRates(std::string file) {
	try {
		_isValidFile(file);
	}
	catch (std::exception &e){
		std::cout << red << e.what() << resetColor << std::endl;
	}
	std::ifstream f(file);
	_getLine(f);
	int lineCounter = 2;
	while (f.good()) {
		std::string line = _getLine(f);
		std::string dateString = _getDate(line);
		std::string priceString = _getPrice(line);
		try {
			Date date(dateString);
			double price = stod(priceString);
			_exchangeRates[date] = price;
		}
		catch (std::exception &e) {
			std::cout << red <<  "Error in line " << lineCounter << " in " << file << " file" << resetColor << std::endl;
			std::cout << e.what() << std::endl;
		}
		lineCounter++;
	}
	std::cout << boldBackgroundCyan  << "all Exchange/Rate data has been read!" << resetColor << std::endl;
}

void BitcoinExchange::_storeAccountInfo(std::string file) {
	try {
		_isValidFile(file);
	}
	catch (std::exception &e){
		std::cout << red << e.what() << resetColor << std::endl;
	}
	std::ifstream f(file);
	_getLine(f); // skip first line of headers in file
	int lineCounter = 2;
	while (f.good()) {
		std::string line = _getLine(f);
		std::string dateString = _getDate(line);
		std::string amountString = _getAmount(line);
		try {
			Date date(dateString);
			double amount = stod(amountString);
			_accountInfo[date] = amount;
		}
		catch (std::exception &e) {
			std::cout << red <<  "Error in line " << lineCounter << " in " << file << " file" << resetColor << std::endl;
			std::cout << e.what() << std::endl;
		}
		lineCounter++;
	}
	std::cout << boldBackgroundMagenta << "all Account data has been read!" << resetColor << std::endl;
}

void BitcoinExchange::getAccountBalance() {
	std::map<Date, double>::iterator it = _accountInfo.begin();
	std::map<Date, double>::iterator end = _accountInfo.end();

	while (it != end) {
		Date date = it->first;
		double amount = it->second;
		Date nearestDate = _nearestDate(date);
		double price = _exchangeRates[nearestDate];
		double balance = amount * price;
		std::cout << "["<< cyan << date << " " << amount << "] ----> ["<< nearestDate << " " << price << "] " << resetColor;
		std::cout << boldBackgroundMagenta << "----> " << balance << resetColor << std::endl;
		it++;
	}
}

void BitcoinExchange::_isValidFile(std::string file){
	std::ifstream f(file);
	if (!f.good())
		throw InvalidFileException();
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
