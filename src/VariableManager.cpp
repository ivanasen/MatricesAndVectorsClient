#include <iostream>
#include <regex>
#include <memory>
#include <Vector.hpp>
#include <VariableManager.hpp>


#include "VariableManager.hpp"
#include "Constants.hpp"
#include "Utility.hpp"

void VariableManager::initialiseMatrixFromInput(std::string input) {
	std::smatch dimensionsMatch;
	std::string matrixName = Utility::extractName(input);

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

	auto
	matrix = std::make_shared<linalg::Matrix < double>>
	(matrixValues);
	mVariables[matrixName] = matrix;
}

void VariableManager::initialiseVectorFromInput(const std::string &input) {
	std::string vectorName = Utility::extractName(input);

	std::smatch dimensionsMatch;
	std::regex_search(input, dimensionsMatch, Constants::MATRIX_DIMENSION_REGEX);
	unsigned long vectorSize = stoul(dimensionsMatch[0]);

	std::vector<double> vectorValues(vectorSize);
	std::cout << "Enter values: ";
	for (int i = 0; i < vectorSize; i++) {
		std::cin >> vectorValues[i];
	}

	auto
	vector = std::make_shared<linalg::Vector < double>>
	(vectorValues);
	mVariables[vectorName] = vector;
}

void VariableManager::printMatrix(const std::string &name) {
	try {
		linalg::Matrix<double> matrix = getMatrixWithName(name);
		std::cout << matrix;
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}

}

void VariableManager::printDeterminant(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = getMatrixWithName(input);
		std::cout << matrix.det() << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void VariableManager::printInverse(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = getMatrixWithName(input);
		std::cout << matrix.invert() << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void VariableManager::printDiagonalMatrix(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = getMatrixWithName(input);
		std::cout << matrix.toDiagonalMatrix();
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void VariableManager::printTransposed(const std::string &input) {
	linalg::Matrix<double> matrix = getMatrixWithName(input);
	std::cout << matrix.transpose();
}

void VariableManager::printNormalisedVector(const std::string &input) {
	linalg::Vector<double> vector = linalg::Vector<double>(getMatrixWithName(input));
	std::cout << vector.normalise();
}

void VariableManager::printEvaluatedExpression(const std::string &input) {
	try {
		std::vector expression = Utility::splitExpression(input);
		std::vector<unsigned long> matches = Utility::matchBrackets(expression);
		linalg::MatrixOrScalar<double> result = evaluateExpression(expression, 0, expression.size() - 1, matches);
		if (result.isMatrix) {
			std::cout << result.matrixValue();
		} else {
			std::cout << result.scalarValue() << std::endl;
		}
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}

}

linalg::Matrix<double> &VariableManager::getMatrixWithName(const std::string &input) {
	std::string matrixName = Utility::extractName(input);

	if (mVariables.find(matrixName) != mVariables.end()) {
		return *(mVariables[matrixName]);
	} else {
		throw std::invalid_argument("There is no matrix with name " + matrixName);
	}
}

VariableManager::VariableManager() {
	mVariables = std::unordered_map<std::string, std::shared_ptr<linalg::Matrix < double>> > ();
}

linalg::MatrixOrScalar<double>
VariableManager::evaluateExpression(const std::vector<std::string> &expression, long startIndex, long endIndex,
                                    std::vector<unsigned long> &bracketMatches) {
	if (expression[endIndex] == ")" && bracketMatches[endIndex] == startIndex) {
		return evaluateExpression(expression, startIndex + 1, endIndex - 1, bracketMatches);
	}

	if (endIndex - startIndex == 0) {
		if (Utility::isName(expression[startIndex])) {
			linalg::Matrix<double> matrix = getMatrixWithName(expression[startIndex]);
			return linalg::MatrixOrScalar<double>(matrix);
		} else if (isdigit(expression[startIndex][0])) {
			double scalar = std::stof(expression[startIndex]);
			return linalg::MatrixOrScalar<double>(scalar);
		}
	}

	long splitIndex = Utility::findExpressionSplitIndex(expression, bracketMatches, startIndex, endIndex);

	linalg::MatrixOrScalar<double> leftResult = evaluateExpression(expression, startIndex, splitIndex - 1,
	                                                               bracketMatches);
	linalg::MatrixOrScalar<double> rightResult = evaluateExpression(expression, splitIndex + 1, endIndex,
	                                                                bracketMatches);
	linalg::MatrixOrScalar<double> result = Utility::applyOperator(leftResult, rightResult, expression[splitIndex]);

	return result;
}
