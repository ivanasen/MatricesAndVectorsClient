#include <iostream>
#include <regex>
#include <memory>
#include <Vector.hpp>
#include <VariableManager.hpp>


#include "VariableManager.hpp"
#include "Constants.hpp"
#include "Utility.hpp"

VariableManager::VariableManager() {
	mVariables = std::unordered_map<std::string, std::shared_ptr<linalg::MatrixOrScalar<double>>>();
}

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
	linalg::Matrix<double> matrix(matrixValues);
	auto matrixVariable = std::make_shared<linalg::MatrixOrScalar<double>>(matrix);
	mVariables[matrixName] = matrixVariable;
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

	linalg::Vector<double> vector(vectorValues);
	auto vectorVariable = std::make_shared<linalg::MatrixOrScalar<double>>(vector);
	mVariables[vectorName] = vectorVariable;
}

void VariableManager::printVariable(const std::string &name) {
	try {
		linalg::MatrixOrScalar<double> variable = evaluateVariable(name);
		std::cout << variable;
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}

}

void VariableManager::printDeterminant(const std::string &input) {
	try {
		linalg::MatrixOrScalar<double> variable = evaluateVariable(input);
		if (variable.isMatrix) {
			std::cout << variable.matrixValue().det() << std::endl;
		} else {
			throw std::invalid_argument("Variable \"" + input + "\" is not a matrix.");
		}
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void VariableManager::printInverse(const std::string &input) {
	try {
		linalg::MatrixOrScalar<double> variable = evaluateVariable(input);
		if (variable.isMatrix) {
			std::cout << variable.matrixValue().invert();
		} else {
			throw std::invalid_argument("Variable \"" + input + "\" is not a matrix.");
		}
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void VariableManager::printDiagonalMatrix(const std::string &input) {
	try {
		linalg::MatrixOrScalar<double> variable = evaluateVariable(input);
		if (variable.isMatrix) {
			std::cout << variable.matrixValue().toDiagonalMatrix();
		} else {
			throw std::invalid_argument("Variable \"" + input + "\" is not a matrix.");
		}
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

void VariableManager::printTransposed(const std::string &input) {
	linalg::MatrixOrScalar<double> variable = evaluateVariable(input);
	if (variable.isMatrix) {
		std::cout << variable.matrixValue().transpose();
	} else {
		throw std::invalid_argument("Variable \"" + input + "\" is not a matrix.");
	}
}

void VariableManager::printNormalisedVector(const std::string &input) {
	linalg::MatrixOrScalar<double> variable = evaluateVariable(input);
	if (variable.isMatrix) {
		std::cout << linalg::Vector(variable.matrixValue()).normalise();
	} else {
		throw std::invalid_argument("Variable \"" + input + "\" is not a matrix.");
	}
}

void VariableManager::printEvaluatedExpression(const std::string &input) {
	try {
		linalg::MatrixOrScalar<double> result = evaluateExpression(input);
		std::cout << result;
	} catch (const std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}
}

linalg::MatrixOrScalar<double> VariableManager::evaluateVariable(const std::string &input) {
	std::string name = Utility::extractName(input);
	if (!name.empty()) {
		if (mVariables.find(name) != mVariables.end()) {
			return *(mVariables[name]);
		} else {
			throw std::invalid_argument("There is no variable with name " + name);
		}
	} else if (isdigit(input[0])) {
		double scalar = std::stof(input);
		return linalg::MatrixOrScalar<double>(scalar);
	}
}

linalg::MatrixOrScalar<double> VariableManager::evaluateExpression(const std::string &expressionStr) {
	long startIndex = 0;
	std::vector<std::string> expression = Utility::splitExpression(expressionStr);
	long endIndex = expression.size() - 1;
	std::vector<unsigned long> matches = Utility::matchBrackets(expression);
	return evaluateExpression(expression, startIndex, endIndex, matches);
}

linalg::MatrixOrScalar<double>
VariableManager::evaluateExpression(const std::vector<std::string> &expression, long startIndex, long endIndex,
                                    std::vector<unsigned long> &bracketMatches) {
	if (expression[endIndex] == ")" && bracketMatches[endIndex] == startIndex) {
		return evaluateExpression(expression, startIndex + 1, endIndex - 1, bracketMatches);
	}

	if (endIndex - startIndex == 0) {
		return evaluateVariable(expression[startIndex]);
	}

	long splitIndex = Utility::findExpressionSplitIndex(expression, bracketMatches, startIndex, endIndex);

	linalg::MatrixOrScalar<double> leftResult = evaluateExpression(expression, startIndex, splitIndex - 1,
	                                                               bracketMatches);
	linalg::MatrixOrScalar<double> rightResult = evaluateExpression(expression, splitIndex + 1, endIndex,
	                                                                bracketMatches);
	linalg::MatrixOrScalar<double> result = Utility::applyOperator(leftResult, rightResult, expression[splitIndex]);

	return result;
}

void VariableManager::printAssignedExpression(const std::string &input) {
	std::string variableName = Utility::extractName(input);
	std::string expression = Utility::extractExpression(input);

	linalg::MatrixOrScalar<double> result = evaluateExpression(expression);
	mVariables[variableName] = std::make_shared<linalg::MatrixOrScalar<double>>(result);

	std::cout << result;
}
