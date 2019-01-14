//
// Created by ivanasen on 14.01.19.
//

#include "Constants.hpp"

const std::regex Constants::MATRIX_NAME_REGEX("[a-zA-Z_$][a-zA-Z_$0-9]+");
const std::regex Constants::MATRIX_INIT_REGEX(
		"^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*[ ]*\\[[ ]*[0-9]+[ ]*,[ ]*[0-9]+[ ]*\\]+[ ]*$");
const std::regex Constants::MATRIX_PRINT_REGEX("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*[ ]*$");
const std::regex Constants::MATRIX_TRANSPOSE_REGEX("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.T[ ]*$");
const std::regex Constants::MATRIX_DETERMINANT_REGEX("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.det[ ]*$");
const std::regex Constants::MATRIX_INVERSE_REGEX("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.inverse[ ]*$");
const std::regex Constants::MATRIX_DIAGONAL_REGEX("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.diagonal[ ]*$");
const std::regex Constants::VECTOR_NORMALISE_REGEX("^[ ]*[a-zA-Z_$][a-zA-Z_$0-9]*.normalise[ ]*$");
const std::regex Constants::EXPRESSION_REGEX(R"(^[ ]*(([a-zA-Z_$][a-zA-Z_$0-9]*|\d+(\.\d+)?)[ ]*([-+/*])*[ ]*)*$)");
