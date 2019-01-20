#include <stdexcept>
#include <regex>
#include <Constants.hpp>
#include <MatrixOrScalar.hpp>
#include <Vector.hpp>
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
	std::regex_search(source, nameMatch, Constants::MATRIX_NAME_REGEX);
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

bool Utility::isName(const std::string &name) {
	return std::regex_match(name, Constants::MATRIX_NAME_REGEX);
}

linalg::MatrixOrScalar<double>
Utility::applyOperator(linalg::MatrixOrScalar<double> &leftOperand,
                       linalg::MatrixOrScalar<double> &rightOperand,
                       const std::string &op) {
	if (op == "+") {
		return leftOperand + rightOperand;
	} else if (op == "-") {
		return leftOperand + rightOperand;
	} else if (op == "*") {
		if (leftOperand.isMatrix && rightOperand.isMatrix &&
		    leftOperand.matrixValue().width() == 1 &&
		    rightOperand.matrixValue().width() == 1) {
			linalg::Vector leftVector = linalg::Vector(leftOperand.matrixValue());
			linalg::Vector rightVector = linalg::Vector(rightOperand.matrixValue());
			return linalg::MatrixOrScalar<double>(leftVector.cross(rightVector));
		}

		return leftOperand * rightOperand;
	} else if (op == ".") {
		if (!leftOperand.isMatrix || !rightOperand.isMatrix) {
			throw std::invalid_argument("Operands need to be vectors in order to calculate dot product");
		} else {
			return calculateDotProduct(leftOperand.matrixValue(), rightOperand.matrixValue());
		}
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
			std::pair<char, int> top = bracketsStack.top();
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

linalg::MatrixOrScalar<double>
Utility::calculateDotProduct(linalg::Matrix<double> &first, linalg::Matrix<double> &second) {
	if (first.height() != second.height()) {
		throw std::invalid_argument("Vectors must be of same height in order to calculate dot product.");
	} else {
		linalg::Vector<double> firstVector(first);
		linalg::Vector<double> secondVector(second);
		return linalg::MatrixOrScalar(firstVector.dot(secondVector));
	}
}
