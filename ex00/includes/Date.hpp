/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 23:21:52 by estruckm          #+#    #+#             */
/*   Updated: 2024/01/08 23:21:52 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <exception>
#include <ctime>
#include <sstream>
#include "Colors.hpp"

class Date {
public:
	Date(std::string date);
	~Date();
	void parseDate(std::string date);
	bool isValidDate(const std::string &date);

	std::string _getYear(std::string date);
	std::string _getMonth(std::string month);
	std::string _getDay(std::string day);

	int _getCurrentYear();
	int _getCurrentMonth();
	int _getCurrentDay();

	Date &operator=(Date const &rhs);
	Date &operator<(Date const &rhs);
	Date &operator>(Date const &rhs);
	Date &operator<=(Date const &rhs);
	Date &operator>=(Date const &rhs);
	Date &operator==(Date const &rhs);

	int _currentDay;
	int _currentMonth;
	int _currentYear;

	int _day;
	int _month;
	int year;
	class InvalidDateException : public std::exception {
	public:
		virtual const char *what() const throw();
	};
};