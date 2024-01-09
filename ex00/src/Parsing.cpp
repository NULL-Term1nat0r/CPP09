/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:12:10 by estruckm          #+#    #+#             */
/*   Updated: 2024/01/09 13:12:10 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parsing.hpp"

int Parsing::stoi(std::string string){
	int result;
	std::istringstream iss(string);

	if (!(iss >> result))
		throw InvalidConversion();
	return result;
}

const char *Parsing::InvalidConversion::what() const throw() {
	return "Invalid conversion";
}
