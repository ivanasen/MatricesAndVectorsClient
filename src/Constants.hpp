#pragma once

#include <regex>

class Constants {
public:
	static const std::regex MATRIX_NAME_REGEX;
	static const std::regex MATRIX_INIT_REGEX;
	static const std::regex MATRIX_PRINT_REGEX;
	static const std::regex MATRIX_TRANSPOSE_REGEX;
	static const std::regex MATRIX_DETERMINANT_REGEX;
	static const std::regex MATRIX_INVERSE_REGEX;
	static const std::regex MATRIX_DIAGONAL_REGEX;
	static const std::regex VECTOR_NORMALISE_REGEX;
	static const std::regex EXPRESSION_REGEX;
};
