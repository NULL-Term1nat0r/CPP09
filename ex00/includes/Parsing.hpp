/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:05:55 by estruckm          #+#    #+#             */
/*   Updated: 2024/01/09 13:05:55 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include <string>
#include <sstream>

class Parsing {
	public:
		static int stoi(std::string);
		class InvalidConversion : std::exception {
			virtual const char *what() const throw();
		};
};

#endif