#include <iostream>
#include <regex>
#include <memory>
#include <Vector.hpp>

#include "MatricesClient.hpp"
#include "Constants.hpp"

MatricesClient::MatricesClient() : Client() {
	mMatrixManager = MatricesManager();
}

void MatricesClient::init() {
	MatricesClient client;
	client.start();
}

void MatricesClient::onInput(const std::string &input) {
	if (std::regex_match(input, Constants::MATRIX_INIT_REGEX)) {
		mMatrixManager.initialiseMatrixFromInput(input);
	} else if (std::regex_match(input, Constants::VECTOR_INIT_REGEX)) {
		mMatrixManager.initialiseVectorFromInput(input);
	} else if (std::regex_match(input, Constants::MATRIX_PRINT_REGEX)) {
		mMatrixManager.printMatrix(input);
	} else if (std::regex_match(input, Constants::MATRIX_TRANSPOSE_REGEX)) {
		mMatrixManager.printTransposed(input);
	} else if (std::regex_match(input, Constants::MATRIX_DETERMINANT_REGEX)) {
		mMatrixManager.printDeterminant(input);
	} else if (std::regex_match(input, Constants::MATRIX_INVERSE_REGEX)) {
		mMatrixManager.printInverse(input);
	} else if (std::regex_match(input, Constants::MATRIX_DIAGONAL_REGEX)) {
		mMatrixManager.printDiagonalMatrix(input);
	} else if (std::regex_match(input, Constants::VECTOR_NORMALISE_REGEX)) {
		mMatrixManager.printNormalisedVector(input);
	} else if (std::regex_match(input, Constants::ASSIGNMENT_EXPRESSION_REGEX)) {
		mMatrixManager.printAssignedExpression(input);
	} else if (std::regex_match(input, Constants::EXPRESSION_REGEX)) {
		mMatrixManager.printEvaluatedExpression(input);
	} else {
		std::cout << "Unknown command " + input + "\n";
	}
}
