#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <Matrix.hpp>


#include "Client.hpp"

class MatricesClient : public Client {
private:
	std::unordered_map<std::string, std::shared_ptr<linalg::Matrix<double>>> mVariables;
public:
	MatricesClient();

	void onInput(const std::string &input) override;

	void initMatrix(std::string string);

	void printMatrix(const std::string &string);

	void evaluateExpression(const std::string &string);

	void printDeterminant();

	void transposeMatrix();

	void printInverse();

	void printDiagonalMatrix();

	void printNormalisedVector();

	static void init();
};
