#include <iostream>
#include <regex>
#include <memory>

#include "MatricesClient.hpp"
#include "Constants.hpp"

void MatricesClient::init() {
	MatricesClient client;
	client.start();
}

void MatricesClient::onInput(const std::string &input) {
	std::smatch matches;

	if (std::regex_search(input, matches, Constants::MATRIX_INIT_REGEX)) {
		initialiseMatrixFromInput(input);
	} else if (std::regex_search(input, matches, Constants::MATRIX_PRINT_REGEX)) {
		printMatrix(input);
	} else if (std::regex_search(input, matches, Constants::MATRIX_TRANSPOSE_REGEX)) {
		printTransposed(input);
	} else if (std::regex_search(input, matches, Constants::MATRIX_DETERMINANT_REGEX)) {
		printDeterminant(input);
	} else if (std::regex_search(input, matches, Constants::MATRIX_INVERSE_REGEX)) {
		printInverse(input);
	} else if (std::regex_search(input, matches, Constants::MATRIX_DIAGONAL_REGEX)) {
		printDiagonalMatrix(input);
	} else if (std::regex_search(input, matches, Constants::VECTOR_NORMALISE_REGEX)) {
		printNormalisedVector(input);
	} else if (std::regex_search(input, matches, Constants::EXPRESSION_REGEX)) {
		printEvaluatedExpression(input);
	} else {
		std::cerr << "Unknown command " + input + "\n";
	}
}

void MatricesClient::initialiseMatrixFromInput(std::string input) {
	std::regex nameRegex("[a-zA-Z_$][a-zA-Z_$0-9]*");
	std::regex dimensionRegex("[0-9]+");
	std::smatch nameMatch;
	std::smatch dimensionsMatch;

	std::regex_search(input, nameMatch, nameRegex);
	std::string matrixName = nameMatch[0];

	std::regex_search(input, dimensionsMatch, dimensionRegex);
	unsigned long matrixHeight = stoul(dimensionsMatch[0]);
	input = dimensionsMatch.suffix();
	std::regex_search(input, dimensionsMatch, dimensionRegex);
	unsigned long matrixWidth = stoul(dimensionsMatch[0]);

	std::vector<std::vector<double>> matrixValues(matrixHeight, std::vector<double>(matrixWidth));
	for (int i = 0; i < matrixHeight; i++) {
		std::cout << "Enter row " + std::to_string(i + 1) + ": ";
		for (int j = 0; j < matrixWidth; j++) {
			std::cin >> matrixValues[i][j];
		}
	}

	auto matrix = std::make_shared<linalg::Matrix<double>>(matrixValues);

	mVariables[matrixName] = matrix;
}

void MatricesClient::printMatrix(const std::string &name) {
	linalg::Matrix<double> matrix = getMatrixFromInput(name);
	std::cout << matrix;
}

void MatricesClient::printDeterminant(const std::string &input) {
	linalg::Matrix<double> matrix = getMatrixFromInput(input);
	try {
		std::cout << matrix.det();
	} catch (const std::invalid_argument &e) {
		std::cerr << e.what() << std::endl;
	}
}

void MatricesClient::printInverse(const std::string &input) {
	linalg::Matrix<double> matrix = getMatrixFromInput(input);
	try {
		std::cout << matrix.invert();
	} catch (const std::invalid_argument &e) {
		std::cerr << e.what() << std::endl;
	}
}

void MatricesClient::printDiagonalMatrix(const std::string &input) {
	linalg::Matrix<double> matrix = getMatrixFromInput(input);
	try {
		std::cout << matrix.toDiagonalMatrix();
	} catch (const std::invalid_argument &e) {
		std::cerr << e.what() << std::endl;
	}
}

void MatricesClient::printTransposed(const std::string &input) {
	linalg::Matrix<double> matrix = getMatrixFromInput(input);
	std::cout << matrix.transpose();
}

void MatricesClient::printNormalisedVector(const std::string &string) {

}

void MatricesClient::printEvaluatedExpression(const std::string &string) {

}

linalg::Matrix<double> MatricesClient::getMatrixFromInput(const std::string &input) {
	std::smatch nameMatch;
	std::regex_search(input, nameMatch, Constants::MATRIX_NAME_REGEX);
	std::string matrixName = nameMatch[0];

	std::shared_ptr<linalg::Matrix<double>> matrix = mVariables[matrixName];
	if (matrix) {
		return *matrix;
	} else {
		std::cerr << "There is no matrix with name " << matrixName;
	}
}


MatricesClient::MatricesClient() : Client() {
	mVariables = std::unordered_map<std::string, std::shared_ptr<linalg::Matrix<double>>>();
}


