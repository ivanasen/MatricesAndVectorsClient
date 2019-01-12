#include <iostream>
#include <regex>

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
	std::regex matrixInitRegex("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*[ ]*\\[[ ]*[0-9]+,[ ]*[0-9]+[ ]*\\]+[ ]*$");
	std::regex matrixPrintRegex("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*[ ]*$");
	std::regex matrixTransposeRegex("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.T[ ]*$");
	std::regex matrixDeterminantRegex("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.det[ ]*$");
	std::regex matrixInverseRegex("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.inverse[ ]*$");
	std::regex matrixDiagonalRegex("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.diagonal[ ]*$");
	std::regex vectorNormaliseRegex("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.normalise[ ]*$");
	std::regex expressionRegex(R"(^[ ]*(([a-zA-Z_$][a-zA-Z_$0-9]*|\d+(\.\d+)?)[ ]*([-+/*])*[ ]*)*$)");

	std::smatch matches;

	if (std::regex_search(input, matches, matrixInitRegex)) {
		initMatrix();
	} else if (std::regex_search(input, matches, matrixPrintRegex)) {
		printMatrix();
	} else if (std::regex_search(input, matches, matrixTransposeRegex)) {
		transposeMatrix();
	} else if (std::regex_search(input, matches, matrixDeterminantRegex)) {
		printDeterminant();
	} else if (std::regex_search(input, matches, matrixInverseRegex)) {
		printInverse();
	} else if (std::regex_search(input, matches, matrixDiagonalRegex)) {
		printDiagonalMatrix();
	} else if (std::regex_search(input, matches, vectorNormaliseRegex)) {
		printNormalisedVector();
	} else if (std::regex_search(input, matches, expressionRegex)) {
		evaluateExpression(input);
	} else {
		std::cerr << "Unknown command " + input + "\n";
	}
}

void MatricesClient::initMatrix() {

}

void MatricesClient::printMatrix() {

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
