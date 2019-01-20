#include <iostream>
#include <regex>
#include <memory>
#include <Vector.hpp>

#include "MatricesClient.hpp"
#include "Constants.hpp"

MatricesClient::MatricesClient() : Client() {
	mVariableManager = VariableManager();
}

void MatricesClient::init() {
	MatricesClient client;
	client.start();
}

void MatricesClient::onInput(const std::string &input) {
	if (std::regex_match(input, Constants::MATRIX_INIT_REGEX)) {
		mVariableManager.initialiseMatrixFromInput(input);
	} else if (std::regex_match(input, Constants::VECTOR_INIT_REGEX)) {
		mVariableManager.initialiseVectorFromInput(input);
	} else if (std::regex_match(input, Constants::MATRIX_PRINT_REGEX)) {
		mVariableManager.printVariable(input);
	} else if (std::regex_match(input, Constants::MATRIX_TRANSPOSE_REGEX)) {
		mVariableManager.printTransposed(input);
	} else if (std::regex_match(input, Constants::MATRIX_DETERMINANT_REGEX)) {
		mVariableManager.printDeterminant(input);
	} else if (std::regex_match(input, Constants::MATRIX_INVERSE_REGEX)) {
		mVariableManager.printInverse(input);
	} else if (std::regex_match(input, Constants::MATRIX_DIAGONAL_REGEX)) {
		mVariableManager.printDiagonalMatrix(input);
	} else if (std::regex_match(input, Constants::VECTOR_NORMALISE_REGEX)) {
		mVariableManager.printNormalisedVector(input);
	} else if (std::regex_match(input, Constants::ASSIGNMENT_EXPRESSION_REGEX)) {
		mVariableManager.printAssignedExpression(input);
	} else if (std::regex_match(input, Constants::EXPRESSION_REGEX)) {
		mVariableManager.printEvaluatedExpression(input);
	} else {
		std::cout << "Unknown command " + input + "\n";
	}
}
