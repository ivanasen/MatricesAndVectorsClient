#pragma once

#include "Matrix.hpp"

namespace linalg {
	template<class T>
	struct MatrixOrScalar {
		bool isMatrix;

		MatrixOrScalar() : isMatrix(false) {
		}

		explicit MatrixOrScalar(const Matrix<T> &matrix) : isMatrix(true) {
			value.matrix = matrix;
		}

		explicit MatrixOrScalar(const T &scalar) : isMatrix(false) {
			value.scalar = scalar;
		}

		MatrixOrScalar(MatrixOrScalar &source) : isMatrix(source.isMatrix) {
			if (isMatrix) {
				value.matrix = source.matrixValue();
			} else {
				value.scalar = source.scalarValue();
			}
		}

		Matrix<T> &matrixValue() {
			if (isMatrix) {
				return value.matrix;
			} else {
				throw std::runtime_error("Variable is of type scalar.");
			}
		}

		T &scalarValue() {
			if (isMatrix) {
				throw std::runtime_error("Variable is of type matrix.");
			} else {
				return value.scalar;
			}
		}

		MatrixOrScalar operator+(MatrixOrScalar<T> &other) {
			if (isMatrix) {
				if (other.isMatrix) {
					return MatrixOrScalar(value.matrix + other.matrixValue());
				} else {
					auto identity = Matrix<T>::makeIdentity(value.matrix.height());
					Matrix<T> scaledIdentity = other.scalarValue() * identity;
					return MatrixOrScalar(value.matrix + scaledIdentity);
				}
			} else {
				if (other.isMatrix) {
					auto identity = Matrix<T>::makeIdentity(other.matrixValue().height());
					Matrix<T> scaledIdentity = value.scalar * identity;
					return MatrixOrScalar(scaledIdentity + other.matrixValue());
				} else {
					return MatrixOrScalar(value.scalar + other.scalarValue());
				}
			}
		}

		MatrixOrScalar operator*(MatrixOrScalar<T> &other) {
			if (isMatrix) {
				if (other.isMatrix) {
					return MatrixOrScalar(value.matrix * other.matrixValue());
				} else {
					return MatrixOrScalar(value.matrix * other.scalarValue());
				}
			} else {
				if (other.isMatrix) {
					return MatrixOrScalar(value.scalar * other.matrixValue());
				} else {
					return MatrixOrScalar(value.scalar * other.scalarValue());
				}
			}
		}

		MatrixOrScalar operator/(MatrixOrScalar<T> other) {
			if (isMatrix) {
				if (other.isMatrix) {
					throw std::runtime_error("Can't divide matrices");
				} else {
					return MatrixOrScalar(value.matrix / other.scalarValue());
				}
			} else {
				if (other.isMatrix) {
					throw std::runtime_error("Can't divide scalars by matrices");
				} else {
					return MatrixOrScalar(value.scalar / other.scalarValue());
				}
			}
		}

		~MatrixOrScalar() = default;

		friend std::ostream &operator<<(std::ostream &stream, MatrixOrScalar &matrixOrScalar) {
			if (matrixOrScalar.isMatrix) {
				stream << matrixOrScalar.matrixValue();
			} else {
				stream << matrixOrScalar.scalarValue() << std::endl;
			}
			return stream;
		}

	private:
		union MatrixOrScalarValue {
			Matrix<T> matrix;
			T scalar;

			MatrixOrScalarValue() : matrix() {
			}

			~MatrixOrScalarValue() {
			}
		} value;
	};
}


