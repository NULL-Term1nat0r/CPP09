/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:22:48 by estruckm          #+#    #+#             */
/*   Updated: 2024/01/08 13:22:48 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Colors.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <stack>

class InvalidInputForOperation : public std::exception {
public:
	virtual const char *what() const throw() {
		return "\033[31mInvalid input for operation\033[0m";
	}
};

bool isOperator(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '!' ) {
		std::cout << magenta << "isOperator: " << c  << resetColor <<  std::endl;
		return true;
	}
	return false;
}

bool isOperand(char c) {
	return isdigit(c);
}

double factorial(double n) {
	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}

void calculateOperation(std::stack<int> &operands, char operation) {
	int a = operands.top();
	operands.pop();
	int b = operands.top();
	operands.pop();
	if (operation == '+') {
		std::cout << cyan << "calculating: " << resetColor << boldCyan <<  a << " + " << b << " = " <<  (a + b) << resetColor << std::endl;
		operands.push(a + b);
	}
	else if (operation == '-'){
		std::cout << cyan << "calculating: " << resetColor << boldCyan <<  b << " - " << a << " = " <<  (b - a) << resetColor << std::endl;
		operands.push(b - a);
	}
	else if (operation == '*'){
		std::cout << cyan << "calculating: " << resetColor << boldCyan <<  a << " * " << b << " = " <<  (a * b) << resetColor << std::endl;
		operands.push(a * b);
	}
	else if (operation == '/'){
		if (b == 0)
			throw InvalidInputForOperation();
		std::cout << cyan << "calculating: " << resetColor << boldCyan <<  a << " / " << b << " = " <<  (a / b) << resetColor << std::endl;
		operands.push(a / b);
	}
	else if (operation == '%'){
		if (b == 0)
			throw InvalidInputForOperation();
		std::cout << cyan << "calculating: " << resetColor << boldCyan <<  a << " % " << b << " = " <<  (a % b) << resetColor << std::endl;
		operands.push(a % b);
	}
	else if (operation == '^'){
		std::cout << cyan << "calculating: " << resetColor << boldCyan <<  a << " ^ " << b << " = " <<  (a ^ b) << resetColor << std::endl;
		operands.push(a ^ b);
	}
	else if (operation == '!'){
		std::cout << cyan << "calculating: " << resetColor << boldCyan <<  a << " ! " << b << " = " <<  (a * factorial(b)) << resetColor << std::endl;
		operands.push(a * factorial(b));
	}
	else
		throw InvalidInputForOperation();
}

int main (int argc, char **argv){

	if (argc != 2) {
		std::cout << "Usage: 3 3 4 + + " << std::endl;
		return 1;
	}
	std::stack<int> operands;
	try {
		for (int i = 0; argv[1][i] != '\0'; i++) {
			if (argv[1][i] == ' ')
				continue;
			else if (isOperand(argv[1][i]) && !isOperand(argv[1][i + 1])) {
				std::cout << yellow <<  "pushing: " << argv[1][i] - '0' << " into stack " << resetColor << std::endl; // "3" - "0" = 3
				operands.push(argv[1][i] - '0');
			} else if (isOperator(argv[1][i]) && operands.size() >= 2) {
				calculateOperation(operands, argv[1][i]);
			} else {
				std::cout << red << "Error: invalid character in this constellation: " << argv[1][i] << resetColor << std::endl;
				throw InvalidInputForOperation();
			}
		}
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	try {
		if (operands.size() > 1) {
			std::cout << red << "Error: operator number is too less to do a another operation and finish the calculation" << resetColor << std::endl;
			throw InvalidInputForOperation();
		}
		std::cout << cyan << "result: " << resetColor << boldBackgroundCyan << operands.top() << resetColor << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}