/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 23:22:03 by estruckm          #+#    #+#             */
/*   Updated: 2024/01/08 23:22:03 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Date.hpp"
#include <iostream>

Date::Date(std::string date) {
	_currentDay = _getCurrentDay();
	_currentMonth = _getCurrentMonth();
	_currentYear = _getCurrentYear();
	std::cout << cyan << "year: " << _currentYear << resetColor << std::endl;
	std::cout << cyan << "month: " << _currentMonth << resetColor << std::endl;
	std::cout << cyan << "day: " << _currentDay << resetColor << std::endl;

	if (!isValidDate(date))
		throw InvalidDateException();


	std::cout << "year: " << _getYear(date) << std::endl;
	std::cout << "month: " << _getMonth(date) << std::endl;
	std::cout << "day: " << _getDay(date) << std::endl;

}

Date::~Date() {}

void Date::parseDate(std::string date) {

}
bool Date::isValidDate(const std::string& date) {
	if (date.length() != 10)
		return false;
	// Use an std::istringstream to extract components
	std::istringstream ss(date);
	char dash1, dash2;
	int year, month, day;

	if (!(ss >> year >> dash1 >> month >> dash2 >> day))
		return false;
	if (ss.fail())
		return false;
	if (dash1 != '-' || dash2 != '-')
		return false;
	if (year < 0 || year > _currentYear){
		std::cout << "fail passier in if year statement" << std::endl;
		return false;
	}
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
//			year < 0 || year > _currentYear || month < 1 || month > 12 || (year == _currentYear && month > _currentMonth) || day < 1 || day > 31 || (year == _currentYear  && month == _currentMonth && day > _currentDay)) {

	std::cout << "date is valid\n";
	return true;
}
std::string Date::_getYear(std::string date){
	int end = date.find('-');
	return date.substr(0, end);
}

std::string Date::_getMonth(std::string date){
	int start = date.find('-');
	int end = date.find_last_of('-');
	return date.substr(start + 1, end - start - 1);
}

std::string Date::_getDay(std::string date){
	int start = date.find_last_of('-');
	int end = date.length();
	return date.substr(start + 1, end);
}

int Date::_getCurrentDay() {
	std::time_t t = std::time(NULL);
	std::tm* now = std::localtime(&t);
	return now->tm_mday;
}

int Date::_getCurrentMonth() {
	std::time_t t = std::time(NULL);
	std::tm* now = std::localtime(&t);
	return now->tm_mon + 1;
}

int Date::_getCurrentYear() {
	std::time_t t = std::time(NULL);
	std::tm* now = std::localtime(&t);
	return now->tm_year + 1900;
}


Date &Date::operator=(Date const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const char *Date::InvalidDateException::what() const throw() {
	return "Invalid date";
}