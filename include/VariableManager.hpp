#pragma once

#include <string>
#include <unordered_map>
#include <Matrix.hpp>
#include <MatrixOrScalar.hpp>

class VariableManager {
private:
	std::unordered_map<std::string, std::shared_ptr<linalg::Matrix < double>>>
	mVariables;

	linalg::Matrix<double> &getMatrixWithName(const std::string &input);

	linalg::MatrixOrScalar<double>
	evaluateExpression(const std::vector<std::string> &expression, long startIndex, long endIndex,
	                   std::vector<unsigned long> &bracketMatches);

public:
	VariableManager();

	void initialiseMatrixFromInput(std::string input);

	void printMatrix(const std::string &string);

	void initialiseVectorFromInput(const std::string &basic_string);

	void printEvaluatedExpression(const std::string &expression);

	void printDeterminant(const std::string &string);

	void printTransposed(const std::string &input);

	void printInverse(const std::string &string);

	void printDiagonalMatrix(const std::string &string);

	void printNormalisedVector(const std::string &string);

};



