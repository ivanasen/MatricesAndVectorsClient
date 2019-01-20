#pragma once

#include <string>
#include <unordered_map>
#include <Matrix.hpp>
#include <MatrixOrScalar.hpp>

class VariableManager {
private:
	std::unordered_map<std::string, std::shared_ptr<linalg::MatrixOrScalar<double>>>
			mVariables;

	linalg::MatrixOrScalar<double> evaluateVariable(const std::basic_string<char> &variable);

	linalg::MatrixOrScalar<double>
	evaluateExpression(const std::string &expression);

	linalg::MatrixOrScalar<double>
	evaluateExpression(const std::vector<std::string> &expression, long startIndex, long endIndex,
	                   std::vector<unsigned long> &bracketMatches);

public:
	VariableManager();

	void initialiseMatrixFromInput(std::string input);

	void printVariable(const std::string &string);

	void initialiseVectorFromInput(const std::string &basic_string);

	void printEvaluatedExpression(const std::string &expression);

	void printDeterminant(const std::string &string);

	void printTransposed(const std::string &input);

	void printInverse(const std::string &string);

	void printDiagonalMatrix(const std::string &string);

	void printNormalisedVector(const std::string &string);

	void printAssignedExpression(const std::string &input);
};