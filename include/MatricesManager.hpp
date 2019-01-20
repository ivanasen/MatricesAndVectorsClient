#pragma once

#include <string>
#include <unordered_map>
#include <Matrix.hpp>

class MatricesManager {
private:
	std::unordered_map<std::string, std::shared_ptr<linalg::Matrix<double>>>
			mMatrices;

	linalg::Matrix<double> evaluateMatrix(const std::basic_string<char> &matrix);

	linalg::Matrix<double>
	evaluateExpression(const std::string &expression);

	linalg::Matrix<double>
	evaluateExpression(const std::vector<std::string> &expression, long startIndex, long endIndex,
	                   std::vector<unsigned long> &bracketMatches);

	linalg::Matrix<double> initialiseMatrix(std::string &name, unsigned long height, unsigned long width);

public:
	MatricesManager();

	void initialiseMatrixFromInput(std::string input);

	void printMatrix(const std::string &string);

	void initialiseVectorFromInput(const std::string &basic_string);

	void printEvaluatedExpression(const std::string &expression);

	void printDeterminant(const std::string &string);

	void printTransposed(const std::string &input);

	void printInverse(const std::string &string);

	void printDiagonalMatrix(const std::string &string);

	void printNormalisedVector(const std::string &string);

	void printAssignedExpression(const std::string &input);
};