#pragma once

#include "Matrix.hpp"

namespace linalg {

	template<class T>
	class Scalar : public Matrix<T> {
	public:
		explicit Scalar(const T &value) : Matrix<T>(std::vector<std::vector<T>>(1, std::vector<T>(1, value))) {
		}

		explicit Scalar(const Matrix<T> &source) : Matrix<T>(
				std::vector<std::vector<T>>(1, std::vector<T>(1, source[0][0]))) {
		}

		T value() {
			return (*this)[0][0];
		}
	};

}
