#include <iostream>
#include <regex>
#include <memory>

#include "MatricesClient.hpp"

template<class T>
T applyOperator(T a, T b, char op) {
	switch (op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		default:
			throw std::invalid_argument("Invalid operator.");
	}
}

bool isLetter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void MatricesClient::init() {
	MatricesClient client;
	client.start();
}

void MatricesClient::onInput(const std::string &input) {
	// Regex expressions for matching input commands
	static std::regex matrixInit("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*[ ]*\\[[ ]*[0-9]+[ ]*,[ ]*[0-9]+[ ]*\\]+[ ]*$");
	static std::regex matrixPrint("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*[ ]*$");
	static std::regex matrixTranspose("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.T[ ]*$");
	static std::regex matrixDeterminant("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.det[ ]*$");
	static std::regex matrixInverse("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.inverse[ ]*$");
	static std::regex matrixDiagonal("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.diagonal[ ]*$");
	static std::regex vectorNormalise("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.normalise[ ]*$");
	static std::regex expression(R"(^[ ]*(([a-zA-Z_$][a-zA-Z_$0-9]*|\d+(\.\d+)?)[ ]*([-+/*])*[ ]*)*$)");

	std::smatch matches;

	if (std::regex_search(input, matches, matrixInit)) {
		initMatrix(input);
	} else if (std::regex_search(input, matches, matrixPrint)) {
		printMatrix(input);
	} else if (std::regex_search(input, matches, matrixTranspose)) {
		transposeMatrix();
	} else if (std::regex_search(input, matches, matrixDeterminant)) {
		printDeterminant();
	} else if (std::regex_search(input, matches, matrixInverse)) {
		printInverse();
	} else if (std::regex_search(input, matches, matrixDiagonal)) {
		printDiagonalMatrix();
	} else if (std::regex_search(input, matches, vectorNormalise)) {
		printNormalisedVector();
	} else if (std::regex_search(input, matches, expression)) {
		evaluateExpression(input);
	} else {
		std::cerr << "Unknown command " + input + "\n";
	}
}

void MatricesClient::initMatrix(std::string input) {
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
		std::cout << getCommandPrefix() << "Enter row " + std::to_string(i + 1) + ": ";
		for (int j = 0; j < matrixWidth; j++) {
			std::cin >> matrixValues[i][j];
		}
	}

	auto matrix = std::make_shared<linalg::Matrix<double>>(matrixValues);

	std::cout << matrix;

	mVariables[matrixName] = matrix;
}

void MatricesClient::printMatrix(const std::string &name) {
	std::shared_ptr<linalg::Matrix<double>> matrixPtr = mVariables[name];
	if (matrixPtr) {
		std::cout << *matrixPtr;
	} else {
		std::cout << "There is no matrix with name \"" + name + "\".";
	}
}

void MatricesClient::evaluateExpression(const std::string &string) {

}

void MatricesClient::printDeterminant() {

}

void MatricesClient::printInverse() {

}

void MatricesClient::printDiagonalMatrix() {

}

void MatricesClient::transposeMatrix() {

}

void MatricesClient::printNormalisedVector() {

}

MatricesClient::MatricesClient() : Client() {
	mVariables = std::unordered_map<std::string, std::shared_ptr<linalg::Matrix<double>>>();
}
