#include <stdexcept>
#include <regex>
#include <Constants.hpp>
#include <Vector.hpp>
#include <Scalar.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <Utility.hpp>

#include "Utility.hpp"

bool Utility::isOperator(const std::string &s) {
	return isOperator(s[0]);
}

bool Utility::isOperator(const char &c) {
	return getOperatorPrecedence(c) != -1;
}

int Utility::getOperatorPrecedence(const std::string &s) {
	return getOperatorPrecedence(s[0]);
}

int Utility::getOperatorPrecedence(const char &c) {
	if (c == '+' || c == '-') {
		return 1;
	} else if (c == '*' || c == '/' || c == '.') {
		return 2;
	} else {
		return -1;
	}
}

bool Utility::isBracket(const char &c) {
	return c == '(' || c == ')';
}


std::string Utility::extractNumber(const std::string &source) {
	std::string number;

	for (char currentChar : source) {
		if (isdigit(currentChar) || currentChar == '.') {
			number += currentChar;
		} else {
			break;
		}
	}

	return number;
}

std::string Utility::extractName(const std::string &source) {
	std::smatch nameMatch;
	std::regex_search(source, nameMatch, Constants::VARIABLE_NAME_REGEX);
	return nameMatch[0];
}

bool Utility::isWhiteSpace(const char &c) {
	return c == ' ' || c == '\t';
}

std::vector<std::string> Utility::splitExpression(const std::string &expression) {
	std::vector<std::string> splitExpression;

	for (unsigned i = 0; i < expression.length(); i++) {
		char currentChar = expression[i];

		if (isOperator(currentChar) || isBracket(currentChar)) {
			splitExpression.emplace_back(std::string(1, currentChar));
		} else if (isdigit(currentChar)) {
			std::string number = extractNumber(expression.substr(i));
			i += number.length() - 1;
			splitExpression.push_back(number);
		} else if (isalpha(currentChar)) {
			std::string name = extractName(expression.substr(i));
			i += name.length() - 1;
			splitExpression.push_back(name);
		} else if (isWhiteSpace(currentChar)) {
			continue;
		} else {
			throw std::invalid_argument("Invalid expression.");
		}
	}

	return splitExpression;
}

linalg::Matrix<double>
Utility::applyOperator(linalg::Matrix<double> &leftOperand,
                       linalg::Matrix<double> &rightOperand,
                       const std::string &op) {
	if (op == "+") {
		return leftOperand + rightOperand;
	} else if (op == "-") {
		return leftOperand + rightOperand;
	} else if (op == "*") {
		return leftOperand * rightOperand;
	} else if (op == "/") {
		return leftOperand / rightOperand;
	} else if (op == ".") {
		linalg::Vector<double> leftVector = linalg::Vector(leftOperand);
		linalg::Vector<double> rightVector = linalg::Vector(rightOperand);
		return linalg::Scalar(leftVector.dot(rightVector));
	} else {
		throw std::invalid_argument("Invalid operator " + op);
	}
}

long Utility::findExpressionSplitIndex(const std::vector<std::string> &expression,
                                       std::vector<unsigned long> &bracketsMatches,
                                       long startIndex, long endIndex) {
	long splitIndex = 0;
	int minSplitPrecedence = 3;
	for (long i = endIndex; i >= startIndex; i--) {
		if (expression[i] == ")") {
			i = bracketsMatches[i];
		}

		if (Utility::isOperator(expression[i]) &&
		    (splitIndex == 0 ||
		     Utility::getOperatorPrecedence(expression[i]) < minSplitPrecedence)) {
			splitIndex = i;
			minSplitPrecedence = Utility::getOperatorPrecedence(expression[i]);
		}
	}
	return splitIndex;
}

std::vector<unsigned long> Utility::matchBrackets(std::vector<std::string> expression) {
	std::vector<unsigned long> matches(expression.size());
	std::stack<std::pair<char, unsigned long>> bracketsStack;
	for (unsigned long i = 0; i < expression.size(); i++) {
		if (expression[i] == "(") {
			bracketsStack.emplace('(', i);
		} else if (expression[i] == ")") {
			std::pair<char, unsigned long> top = bracketsStack.top();
			if (top.first == '(') {
				matches[i] = top.second;
			} else {
				std::string exception = "Missing opening bracket for position " + std::to_string(i);
				throw std::invalid_argument(exception);
			}
			bracketsStack.pop();
		}
	}

	if (!bracketsStack.empty()) {
		std::pair<char, int> top = bracketsStack.top();
		std::string exception = "Missing closing bracket for position " + std::to_string(top.second);
		throw std::invalid_argument(exception);
	}

	return matches;
}


std::string Utility::extractExpression(const std::string &source) {
	unsigned long i = 0;
	while (source[i] != '=') {
		i++;
	}
	std::string expression = source.substr(i + 1);
	return expression;
}

std::string Utility::trimString(std::string &source) {
	unsigned long startIndex = 0;
	while (startIndex < source.length() && isspace(source[startIndex])) {
		startIndex++;
	}
	unsigned long endIndex = source.length() - 1;
	while (endIndex >= 0 && isspace(source[startIndex])) {
		endIndex--;
	}
	return source.substr(startIndex, endIndex + 1);
}

std::vector<double> Utility::getNumbersFromString(std::string source) {
	std::vector<double> result;
	for (unsigned long i = 0; i < source.length(); i++) {
		if (isdigit(source[i])) {
			try {
				std::string number = extractNumber(source.substr(i));
				result.push_back(stof(number));
				i += number.length();
			} catch (const std::invalid_argument &e) {
				throw std::invalid_argument("The elements of the matrix must be numbers");
			}
		}
	}
	return result;
}

void Utility::logMatrix(linalg::Matrix<double> &matrix) {
	std::vector<std::vector<std::string>> stringMatrix(matrix.height(), std::vector<std::string>(matrix.width()));

	for (int i = 0; i < matrix.height(); i++) {
		for (int j = 0; j < matrix.width(); j++) {
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << matrix[i][j];
			stringMatrix[i][j] = stream.str();
		}
	}

	std::vector<unsigned long> columnSizes(matrix.width());

	for (int col = 0; col < stringMatrix[0].size(); col++) {
		for (auto &row : stringMatrix) {
			if (row[col].length() > columnSizes[col]) {
				columnSizes[col] = row[col].length();
			}
		}
	}

	for (int i = 0; i < stringMatrix.size(); i++) {
		for (int j = 0; j < stringMatrix[0].size(); j++) {
			auto size = columnSizes[j] - stringMatrix[i][j].length() + 1;
			std::string trailingSpaces = std::string(size, ' ');
			std::cout << stringMatrix[i][j] << trailingSpaces;
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}