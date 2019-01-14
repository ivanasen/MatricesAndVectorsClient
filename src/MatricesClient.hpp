#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <Matrix.hpp>


#include "Client.hpp"

class MatricesClient : public Client {
private:
	std::unordered_map<std::string, std::shared_ptr<linalg::Matrix<double>>> mVariables;

	linalg::Matrix<double> getMatrixFromInput(const std::string &input);
public:
	MatricesClient();

	void onInput(const std::string &input) override;

	void initialiseMatrixFromInput(std::string input);

	void printMatrix(const std::string &string);

	void printEvaluatedExpression(const std::string &string);

	void printDeterminant(const std::string &string);

	void printTransposed(const std::string &input);

	void printInverse(const std::string &string);

	void printDiagonalMatrix(const std::string &string);

	void printNormalisedVector(const std::string &string);

	static void init();
};
