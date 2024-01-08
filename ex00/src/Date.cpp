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

Date::Date(std::string date) {

}

Date::~Date() {}

void Date::parseDate(std::string date) {

}
bool Date::isValidDate(std::string date) {

}


Date &Date::operator=(Date const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const char *Date::InvalidDateException::what() const throw() {
	return "Invalid date";
}