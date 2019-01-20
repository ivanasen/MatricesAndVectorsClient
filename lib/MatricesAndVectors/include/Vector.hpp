#pragma once

#include <cmath>
#include "Matrix.hpp"

namespace linalg {
	template<class T>
	class Vector : public Matrix<T> {
	private:
		std::vector<std::vector<T>> toMatrixVector(const std::vector<T> &values) {
			std::vector<std::vector<T>> matrixVector(values.size(), std::vector<T>(1));

			for (int i = 0; i < values.size(); i++) {
				matrixVector[i][0] = values[i];
			}

			return matrixVector;
		}

	public:
		Vector(const std::initializer_list<T> &values) : Matrix<T>(toMatrixVector(values)) {
		}

		explicit Vector(const std::vector<T> &values) : Matrix<T>(toMatrixVector(values)) {
		}

		explicit Vector(const Matrix<T> &source) : Matrix<T>(source) {
		}

		T magnitude() {
			T magnitude = 0;
			for (int i = 0; i < this->size(); i++) {
				magnitude += (*this)[i] * (*this)[i];
			}
			magnitude = std::sqrt(magnitude);
			return magnitude;
		}

		Vector normalise() {
			T vectorMagnitude = magnitude();
			std::vector<T> normalizedArray(this->height());
			for (int i = 0; i < this->height(); i++) {
				normalizedArray[i] = (*this)[i] / vectorMagnitude;
			}
			return Vector(normalizedArray);
		}

		T dot(Vector &other) {
			auto result = other.transpose() * *this;
			return result[0][0];
		}

		Vector cross(Vector &other) {
			if (this->size() != 3) {
				throw std::invalid_argument("Cross product is only defined for 3-Dimensional vectors.");
			}

			Vector crossProduct{(*this)[1] * other[2] - (*this)[2] * other[1],
			                    (*this)[2] * other[0] - (*this)[0] * other[2],
			                    (*this)[0] * other[1] - (*this)[1] * other[0]};
			return crossProduct;
		}

		const T &operator[](int index) {
			return this->m_array[index][0];
		}

		friend const Vector operator*(Matrix<T> &matrix, Vector &vector) {
			auto vectorMatrix = static_cast<Matrix<T>>(vector);
			return Vector(matrix * vectorMatrix);
		}

		unsigned long size() {
			return this->height();
		}
	};
}
