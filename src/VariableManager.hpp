#pragma once

#include <string>
#include <unordered_map>
#include <Matrix.hpp>

class VariableManager {
private:
	std::unordered_map<std::string, std::shared_ptr<linalg::Matrix<double>>> mVariables;

	linalg::Matrix<double> &getMatrixFromInput(const std::string &input);

public:
	VariableManager();

	void initialiseMatrixFromInput(std::string input);

	void printMatrix(const std::string &string);

	void initialiseVectorFromInput(const std::string &basic_string);

	void printEvaluatedExpression(const std::string &string);

	void printDeterminant(const std::string &string);

	void printTransposed(const std::string &input);

	void printInverse(const std::string &string);

	void printDiagonalMatrix(const std::string &string);

	void printNormalisedVector(const std::string &string);

};



