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
#include <exception>

class Date {
public:
	Date(std::string date);
	~Date();
	void parseDate(std::string date);
	bool isValidDate(std::string date);
	Date &operator=(Date const &rhs);
	Date &operator<(Date const &rhs);
	Date &operator>(Date const &rhs);
	Date &operator<=(Date const &rhs);
	Date &operator>=(Date const &rhs);
	Date &operator==(Date const &rhs);
	int _day;
	int _month;
	int year;
	class InvalidDateException : public std::exception {
	public:
		virtual const char *what() const throw();
	};
};