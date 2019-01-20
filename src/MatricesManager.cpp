#include <iostream>
#include <regex>
#include <memory>
#include <Vector.hpp>
#include <MatricesManager.hpp>
#include <Scalar.hpp>


#include "MatricesManager.hpp"
#include "Constants.hpp"
#include "Utility.hpp"

MatricesManager::MatricesManager() {
	mMatrices = std::unordered_map<std::string, std::shared_ptr<linalg::Matrix<double>>>();
}

void MatricesManager::initialiseMatrixFromInput(std::string input) {
	try {
		std::smatch dimensionsMatch;
		std::string name = Utility::extractName(input);

		std::regex_search(input, dimensionsMatch, Constants::MATRIX_DIMENSION_REGEX);
		unsigned long height = stoul(dimensionsMatch[0]);
		input = dimensionsMatch.suffix();
		std::regex_search(input, dimensionsMatch, Constants::MATRIX_DIMENSION_REGEX);
		unsigned long width = stoul(dimensionsMatch[0]);
		linalg::Matrix matrix = initialiseMatrix(name, height, width);
		mMatrices[name] = std::make_shared<linalg::Matrix<double>>(matrix);
		Utility::logMatrix(matrix);
	} catch (const std::invalid_argument &e) {
		std::cout << e.what();
	}
}

void MatricesManager::initialiseVectorFromInput(const std::string &input) {
	try {
		std::string name = Utility::extractName(input);
		std::smatch dimensionsMatch;
		std::regex_search(input, dimensionsMatch, Constants::MATRIX_DIMENSION_REGEX);
		unsigned long size = stoul(dimensionsMatch[0]);
		linalg::Matrix matrix = initialiseMatrix(name, 1, size).transpose();
		mMatrices[name] = std::make_shared<linalg::Matrix<double>>(matrix);
		Utility::logMatrix(matrix);
	} catch (const std::invalid_argument &e) {
		std::cout << e.what();
	}
}


linalg::Matrix<double> MatricesManager::initialiseMatrix(std::string &name, unsigned long height, unsigned long width) {
	std::vector<std::vector<double>> matrixValues(height, std::vector<double>(width));
	for (int i = 0; i < height; i++) {
		std::cout << "Enter row " << i + 1 << ": ";
		std::vector<double> rowVector;
		while (rowVector.size() < width) {
			std::string line;
			std::getline(std::cin, line);
			std::vector<double> addedValues = Utility::getNumbersFromString(line);
			rowVector.insert(rowVector.end(), addedValues.begin(), addedValues.end());
		}
		matrixValues[i] = rowVector;
	}
	linalg::Matrix<double> matrix(matrixValues);
	return matrix;
}

void MatricesManager::printMatrix(const std::string &string) {
	try {
		linalg::Matrix<double> variable = evaluateMatrix(string);
		Utility::logMatrix(variable);
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void MatricesManager::printDeterminant(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = evaluateMatrix(input);
		std::cout << matrix.det() << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void MatricesManager::printInverse(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = evaluateMatrix(input);
		linalg::Matrix<double> inverse = matrix.invert();
		Utility::logMatrix(inverse);
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void MatricesManager::printDiagonalMatrix(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = evaluateMatrix(input);
		linalg::Matrix<double> diagonal = matrix.toDiagonalMatrix();
		Utility::logMatrix(diagonal);
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void MatricesManager::printTransposed(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = evaluateMatrix(input);
		linalg::Matrix<double> transposed = matrix.transpose();
		Utility::logMatrix(transposed);
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void MatricesManager::printNormalisedVector(const std::string &input) {
	try {
		linalg::Matrix<double> matrix = evaluateMatrix(input);
		linalg::Vector<double> normalised = linalg::Vector<double>(matrix).normalise();
		Utility::logMatrix(normalised);
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void MatricesManager::printEvaluatedExpression(const std::string &input) {
	try {
		linalg::Matrix<double> result = evaluateExpression(input);
		Utility::logMatrix(result);
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

linalg::Matrix<double> MatricesManager::evaluateMatrix(const std::string &variable) {
	std::string name = Utility::extractName(variable);
	if (!name.empty()) {
		if (mMatrices.find(name) != mMatrices.end()) {
			return *(mMatrices[name]);
		} else {
			throw std::invalid_argument("There is no variable with name " + name);
		}
	} else if (isdigit(variable[0])) {
		try {
			double scalar = std::stof(variable);
			return linalg::Scalar<double>(scalar);
		} catch (const std::invalid_argument &e) {
			throw std::invalid_argument("Invalid variable: " + variable);
		}
	}
	throw std::invalid_argument("Invalid variable: " + variable);
}

linalg::Matrix<double> MatricesManager::evaluateExpression(const std::string &expressionStr) {
	long startIndex = 0;
	std::vector<std::string> expression = Utility::splitExpression(expressionStr);
	long endIndex = expression.size() - 1;
	std::vector<unsigned long> matches = Utility::matchBrackets(expression);
	return evaluateExpression(expression, startIndex, endIndex, matches);
}

linalg::Matrix<double>
MatricesManager::evaluateExpression(const std::vector<std::string> &expression, long startIndex, long endIndex,
                                    std::vector<unsigned long> &bracketMatches) {
	if (expression[endIndex] == ")" && bracketMatches[endIndex] == startIndex) {
		return evaluateExpression(expression, startIndex + 1, endIndex - 1, bracketMatches);
	}

	if (endIndex - startIndex == 0) {
		return evaluateMatrix(expression[startIndex]);
	}

	long splitIndex = Utility::findExpressionSplitIndex(expression, bracketMatches, startIndex, endIndex);

	linalg::Matrix<double> leftResult = evaluateExpression(expression, startIndex, splitIndex - 1,
	                                                       bracketMatches);
	linalg::Matrix<double> rightResult = evaluateExpression(expression, splitIndex + 1, endIndex,
	                                                        bracketMatches);
	linalg::Matrix<double> result = Utility::applyOperator(leftResult, rightResult, expression[splitIndex]);

	return result;
}

void MatricesManager::printAssignedExpression(const std::string &input) {
	try {
		std::string matrixName = Utility::extractName(input);
		std::string expression = Utility::extractExpression(input);

		linalg::Matrix<double> result = evaluateExpression(expression);
		mMatrices[matrixName] = std::make_shared<linalg::Matrix<double>>(result);

		Utility::logMatrix(result);
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}
