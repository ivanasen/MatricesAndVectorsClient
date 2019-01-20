#pragma once

#include <ostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <cmath>
#include <utility>
#include <stdexcept>
#include "Array2DWrapper.hpp"

namespace linalg {


	template<class T>
	class Matrix : public Array2DWrapper<T> {
	public:
		Matrix() : Array2DWrapper<T>() {
		}

		Matrix(const std::initializer_list<std::vector<T>> &values) : Array2DWrapper<T>(values) {
		}

		explicit Matrix(const std::vector<std::vector<T>> &values) : Array2DWrapper<T>(values) {
		}

		Matrix(const unsigned long &height, const unsigned long &width) : Array2DWrapper<T>(height, width) {
		}

		Matrix(const Matrix &source) : Array2DWrapper<T>(source) {
		}

		virtual ~Matrix() = default;

		Matrix add(Matrix &other) {
			if (this->height() == 1 && this->width() == 1) {
				return other.add((*this)[0][0]);
			}

			if (other.height() == 1 && other.width() == 1) {
				return add(other[0][0]);
			}

			Matrix sum(*this);

			for (int i = 0; i < this->height(); i++) {
				for (int j = 0; j < this->width(); j++) {
					sum[i][j] += other[i][j];
				}
			}

			return sum;
		}

		Matrix add(T &value) {
			Matrix identity = Matrix::makeIdentity(this->height());
			Matrix addMatrix = value * identity;
			return add(addMatrix);
		}

		Matrix multiply(T scalar) const {
			Matrix scaled(*this);
			for (auto &row : scaled) {
				for (T &val : row) {
					val *= scalar;
				}
			}
			return scaled;
		}

		Matrix divide(T scalar) const {
			Matrix scaled(*this);
			for (auto &row : scaled) {
				for (T &val : row) {
					val /= scalar;
				}
			}
			return scaled;
		}

		Matrix divide(Matrix other) {
			if (other.height() == 1 && other.width() == 1) {
				return divide(other[0][0]);
			}

			Matrix otherInverse = other.invert();
			return multiply(otherInverse);
		}

		Matrix<T> multiply(Matrix<T> &other) {
			if (other.height() == 1 && other.width() == 1) {
				return multiply(other[0][0]);
			} else if (this->height() == 1 && this->width() == 1) {
				return other.multiply((*this)[0][0]);
			}

			auto height = this->height();
			auto width = this->width();
			auto otherHeight = other.height();
			auto otherWidth = other.width();

			if (width != otherHeight) {
				throw std::invalid_argument("First Matrix's columns have to be the same count as the second\'s rows.");
			}

			Matrix product(height, otherWidth);

			for (int i = 0; i < height; i++) {
				for (int j = 0; j < otherWidth; j++) {
					product[i][j] = 0;
					for (int k = 0; k < width; k++) {
						product[i][j] += (*this)[i][k] * other[k][j];
					}
				}
			}

			return product;
		}

		Matrix<T> transpose() {
			auto width = this->width();
			auto height = this->height();

			Matrix transposed(width, height);
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					transposed[i][j] = (*this)[j][i];
				}
			}
			return transposed;
		}

		Matrix invert() {
			if (this->width() != this->height()) {
				throw std::invalid_argument("Matrix must be square in order to have an inverse.");
			}

			unsigned long size = this->height();

			Matrix copy = Matrix(*this);
			Matrix inverse = makeIdentity(size);

			toUpperDiagonalMatrix(copy, inverse);
			toLowerDiagonalMatrix(copy, inverse);

			if (hasZeroRows(copy)) {
				throw std::invalid_argument("Matrix must not be odd in order to have an inverse.");
			}

			for (unsigned long i = 0; i < size; i++) {
				T scalar = copy[i][i];
				for (unsigned long j = 0; j < size; j++) {
					inverse[i][j] /= scalar;
				}
			}

			return inverse;
		}

		T det() {
			if (this->height() != this->width()) {
				return 0;
			}

			if (this->width() == 2) {
				return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
			}

			Matrix triangularForm(*this);
			toUpperDiagonalMatrix(triangularForm);

			T det = triangularForm[0][0];
			for (int i = 1; i < this->height(); i++) {
				det *= triangularForm[i][i];
			}
			return det;
		}

		virtual Matrix operator+(Matrix &other) {
			Matrix sum = add(other);
			return sum;
		}

		virtual Matrix operator+(T &value) {
			Matrix sum = add(value);
			return sum;
		}

		virtual Matrix operator*(T scalar) const {
			Matrix result = multiply(scalar);
			return result;
		}

		virtual Matrix operator/(T scalar) {
			Matrix result = divide(scalar);
			return result;
		}

		virtual Matrix operator/(Matrix<T> &matrix) {
			Matrix result = divide(matrix);
			return result;
		}

		friend const Matrix<T> operator*(T scalar, Matrix<T> &matrix) {
			return matrix * scalar;
		}

		friend const Matrix<T> operator+(T scalar, Matrix<T> &matrix) {
			return matrix + scalar;
		}

		virtual Matrix<T> operator*(Matrix<T> &other) {
			Matrix<T> result = multiply(other);
			return result;
		}

		bool isOdd() {
			return det() == 0;
		}

		Matrix toDiagonalMatrix() {
			if (this->height() != this->width()) {
				throw std::invalid_argument("Non-Square Matrices don\'t have a diagonal matrix.");
			}

			Matrix triangular(*this);
			toUpperDiagonalMatrix(triangular);
			toLowerDiagonalMatrix(triangular);

			if (hasZeroRows(triangular)) {
				throw std::invalid_argument("Matrices with linearly dependant rows don\'t have a diagonal matrix.");
			}

			return triangular;
		}

		Matrix getCofactor(int rowToRemove, int colToRemove) {
			Matrix cofactor(this->height() - 1, this->width() - 1);

			for (int row = 0, cofactorRow = 0; row < this->height(); row++) {
				if (row == rowToRemove) {
					continue;
				}
				for (int col = 0, cofactorCol = 0; col < this->width(); col++) {
					if (col == colToRemove) {
						continue;
					}
					cofactor[cofactorRow][cofactorCol++] = (*this)[row][col];
				}
				cofactorRow++;
			}

			return cofactor;
		}

		static Matrix makeIdentity(unsigned long size) {
			Matrix identity(size, size);
			for (int i = 0; i < size; i++) {
				identity[i][i] = 1;
			}
			return identity;
		}

	private:
		Matrix getAdjointMatrix() {
			auto size = this->height();
			Matrix adjoint(size, size);

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					Matrix cofactor = getCofactor(i, j);
					int sign = (i + j) % 2 == 0 ? 1 : -1;
					adjoint[j][i] = sign * cofactor.det();
				}
			}
			return adjoint;
		}

		static void toUpperDiagonalMatrix(Matrix &matrix, int colToRemove = 0) {
			Matrix rightSide = makeIdentity(matrix.height());
			toUpperDiagonalMatrix(matrix, rightSide, colToRemove);
		}

		static void toUpperDiagonalMatrix(Matrix &matrix, Matrix &rightSide, int padding = 0) {
			if (padding == matrix.height() - 1) {
				return;
			}

			for (int i = padding + 1; i < matrix.height(); i++) {
				T scalar = -(matrix[i][padding] / matrix[padding][padding]);
				for (int j = 0; j < matrix.width(); j++) {
					matrix[i][j] += matrix[padding][j] * scalar;
					rightSide[i][j] += rightSide[padding][j] * scalar;
				}
			}

			toUpperDiagonalMatrix(matrix, rightSide, padding + 1);
		}

		static void toLowerDiagonalMatrix(Matrix &matrix, Matrix &rightSide, int padding = 0) {
			long colToRemove = matrix.width() - 1 - padding;

			if (padding == matrix.width() - 1) {
				return;
			}

			for (long i = colToRemove - 1; i >= 0; i--) {
				T scalar = -(matrix[i][colToRemove] / matrix[colToRemove][colToRemove]);
				for (long j = matrix.width() - 1; j >= 0; j--) {
					matrix[i][j] += matrix[colToRemove][j] * scalar;
					rightSide[i][j] += rightSide[colToRemove][j] * scalar;
				}
			}

			toLowerDiagonalMatrix(matrix, rightSide, padding + 1);
		}

		static void toLowerDiagonalMatrix(Matrix &matrix, int padding = 0) {
			Matrix rightSide = makeIdentity(matrix.height());
			toLowerDiagonalMatrix(matrix, rightSide, padding);
		}

		static bool hasZeroRows(const Matrix &matrix) {
			for (auto &row : matrix) {
				int i = 0;
				while (i < row.size() && row[i] == 0) {
					if (i == row.size() - 1) {
						return true;
					}
					i++;
				}
			}
			return false;
		}
	};

}
