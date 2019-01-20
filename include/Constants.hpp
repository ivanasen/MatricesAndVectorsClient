#pragma once

#include <regex>

class Constants {
public:
	static const std::regex VARIABLE_NAME_REGEX;
	static const std::regex MATRIX_INIT_REGEX;
	static const std::regex VECTOR_INIT_REGEX;
	static const std::regex MATRIX_PRINT_REGEX;
	static const std::regex MATRIX_TRANSPOSE_REGEX;
	static const std::regex MATRIX_DETERMINANT_REGEX;
	static const std::regex MATRIX_INVERSE_REGEX;
	static const std::regex MATRIX_DIAGONAL_REGEX;
	static const std::regex MATRIX_DIMENSION_REGEX;
	static const std::regex VECTOR_NORMALISE_REGEX;
	static const std::regex EXPRESSION_REGEX;
	static const std::regex ASSIGNMENT_EXPRESSION_REGEX;
};
