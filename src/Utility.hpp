#pragma once

#include <string>
#include <vector>
#include <Matrix.hpp>
#include <MatrixOrScalar.hpp>

class Utility {
public:
	static bool isOperator(const char &c);

	static bool isOperator(const std::string &s);

	static bool isBracket(const char &c);

	static bool isName(const std::string &name);

	static bool isWhiteSpace(const char &c);

	static std::string extractNumber(const std::string &source);

	static std::string extractName(const std::string &source);

	static std::vector<std::string> splitExpression(const std::string &expression);

	static int getOperatorPrecedence(const char &c);

	static int getOperatorPrecedence(const std::string &s);

	static long
	findExpressionSplitIndex(const std::vector<std::string> &expression, std::vector<unsigned long> &bracketsMatches,
		                         long i, long i1);

	static linalg::MatrixOrScalar<double>
	applyOperator(linalg::MatrixOrScalar<double> &leftOperand, linalg::MatrixOrScalar<double> &rightOperand,
	              const std::string &op);

	static std::vector<unsigned long> matchBrackets(std::vector<std::string> expression);

	static linalg::MatrixOrScalar<double>
	calculateDotProduct(linalg::Matrix<double> &matrix, linalg::Matrix<double> &value);

	static std::string extractExpression(const std::string &source);

	static std::vector<std::vector<double>> readMatrixFromInput(int height, int width);
};


