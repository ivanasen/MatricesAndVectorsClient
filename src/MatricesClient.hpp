#pragma once

#include <vector>
#include <string>
#include <map>
#include "Client.hpp"
#include <Matrix.hpp>

class MatricesClient : public Client {
private:
	std::map<std::string, linalg::Matrix<double>> mVariables;
public:
	void onInput(const std::string &input) override;

	void initMatrix();

	void printMatrix();

	void evaluateExpression(const std::string &string);

	void printDeterminant();

	void transposeMatrix();

	void printInverse();

	void printDiagonalMatrix();

	void printNormalisedVector();

	static void init();
};
