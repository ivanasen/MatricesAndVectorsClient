#pragma once

#include <string>
#include <vector>
#include <Matrix.hpp>

class Utility {
public:
	static bool isOperator(const char &c);

	static bool isOperator(const std::string &s);

	static bool isBracket(const char &c);

	static bool isWhiteSpace(const char &c);

	static std::string extractNumber(const std::string &source);

	static std::string extractName(const std::string &source);

	static std::vector<std::string> splitExpression(const std::string &expression);

	static int getOperatorPrecedence(const char &c);

	static int getOperatorPrecedence(const std::string &s);

	static long
	findExpressionSplitIndex(const std::vector<std::string> &expression, std::vector<unsigned long> &bracketsMatches,
	                         long i, long i1);

	static linalg::Matrix<double>
	applyOperator(linalg::Matrix<double> &leftOperand, linalg::Matrix<double> &rightOperand,
	              const std::string &op);

	static std::vector<unsigned long> matchBrackets(std::vector<std::string> expression);

	static std::string extractExpression(const std::string &source);

	static std::string trimString(std::string &source);

	static std::vector<double> getNumbersFromString(std::string source);

	static void logMatrix(linalg::Matrix<double> &matrix);
};
