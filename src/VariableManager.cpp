#include "VariableManager.hpp"

#include <iostream>
#include <regex>
#include <memory>
#include <Vector.hpp>

#include "VariableManager.hpp"
#include "Constants.hpp"

void VariableManager::initialiseMatrixFromInput(std::string input) {
	std::smatch nameMatch;
	std::smatch dimensionsMatch;

	std::regex_search(input, nameMatch, Constants::MATRIX_NAME_REGEX);
	std::string matrixName = nameMatch[0];

	std::regex_search(input, dimensionsMatch, Constants::MATRIX_DIMENSION_REGEX);
	unsigned long matrixHeight = stoul(dimensionsMatch[0]);
	input = dimensionsMatch.suffix();
	std::regex_search(input, dimensionsMatch, Constants::MATRIX_DIMENSION_REGEX);
	unsigned long matrixWidth = stoul(dimensionsMatch[0]);

	std::vector<std::vector<double>> matrixValues(matrixHeight, std::vector<double>(matrixWidth));
	for (int i = 0; i < matrixHeight; i++) {
		std::cout << "Enter row " << i + 1 << ": ";

		for (int j = 0; j < matrixWidth; j++) {
			std::cin >> matrixValues[i][j];
		}
	}

	auto matrix = std::make_shared<linalg::Matrix<double>>
			(matrixValues);
	mVariables[matrixName] = matrix;
}

void VariableManager::initialiseVectorFromInput(const std::string &input) {
	std::smatch nameMatch;
	std::smatch dimensionsMatch;

	std::regex_search(input, nameMatch, Constants::MATRIX_NAME_REGEX);
	std::string vectorName = nameMatch[0];

	std::regex_search(input, dimensionsMatch, Constants::MATRIX_DIMENSION_REGEX);
	unsigned long vectorSize = stoul(dimensionsMatch[0]);

	std::vector<double> vectorValues(vectorSize);
	std::cout << "Enter values: ";
	for (int i = 0; i < vectorSize; i++) {
		std::cin >> vectorValues[i];
	}

	auto vector = std::make_shared<linalg::Vector<double>>(vectorValues);
	mVariables[vectorName] = vector;
}

void VariableManager::printMatrix(const std::string &name) {
	try {
		linalg::Matrix<double> matrix = getMatrixFromInput(name);
		std::cout << matrix;
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}

}

void VariableManager::printDeterminant(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = getMatrixFromInput(input);
		std::cout << matrix.det() << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void VariableManager::printInverse(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = getMatrixFromInput(input);
		std::cout << matrix.invert() << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void VariableManager::printDiagonalMatrix(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = getMatrixFromInput(input);
		std::cout << matrix.toDiagonalMatrix();
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void VariableManager::printTransposed(const std::string &input) {
	linalg::Matrix<double> matrix = getMatrixFromInput(input);
	std::cout << matrix.transpose();
}

void VariableManager::printNormalisedVector(const std::string &input) {
	linalg::Vector<double> vector = linalg::Vector<double>(getMatrixFromInput(input));
	std::cout << vector.normalise();
}

void VariableManager::printEvaluatedExpression(const std::string &string) {
	std::cout << "Magic\n";
}

linalg::Matrix<double> &VariableManager::getMatrixFromInput(const std::string &input) {
	std::smatch nameMatch;
	std::regex_search(input, nameMatch, Constants::MATRIX_NAME_REGEX);
	std::string matrixName = nameMatch[0];

	if (mVariables.find(matrixName) != mVariables.end()) {
		return *(mVariables[matrixName]);
	} else {
		throw std::invalid_argument("There is no matrix with name " + matrixName);
	}
}

VariableManager::VariableManager() {
	mVariables = std::unordered_map<std::string, std::shared_ptr<linalg::Matrix<double>>>();
}