#include "Constants.hpp"

const std::regex Constants::VARIABLE_NAME_REGEX("[a-zA-Z]+");
const std::regex Constants::MATRIX_INIT_REGEX(
		"^[ ]*[a-zA-Z]+[ ]*=[ ]*\\[[ ]*[0-9]+[ ]*,[ ]*[0-9]+[ ]*\\]+[ ]*$");
const std::regex Constants::VECTOR_INIT_REGEX("^[ ]*[a-zA-Z]+[ ]*=[ ]*\\[[ ]*[0-9]+[ ]*\\]+[ ]*$");
const std::regex Constants::MATRIX_PRINT_REGEX("^[ ]*[a-zA-Z]+*[ ]*$");
const std::regex Constants::MATRIX_TRANSPOSE_REGEX("^[ ]*[a-zA-Z]+*.T[ ]*$");
const std::regex Constants::MATRIX_DETERMINANT_REGEX("^[ ]*[a-zA-Z]+*.det[ ]*$");
const std::regex Constants::MATRIX_INVERSE_REGEX("^[ ]*[a-zA-Z]+*.inverse[ ]*$");
const std::regex Constants::MATRIX_DIAGONAL_REGEX("^[ ]*[a-zA-Z]+*.diagonal[ ]*$");
const std::regex Constants::MATRIX_DIMENSION_REGEX("[0-9]+");
const std::regex Constants::VECTOR_NORMALISE_REGEX("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.normalise[ ]*$");
const std::regex Constants::ASSIGNMENT_EXPRESSION_REGEX("[a-zA-Z]+[ ]*=[ ]*.*[+\\-*.0-9].*");
const std::regex Constants::EXPRESSION_REGEX(".*[+\\-*.0-9].*");

