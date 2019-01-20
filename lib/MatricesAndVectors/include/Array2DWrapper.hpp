#pragma once

#include <vector>
#include <initializer_list>
#include <iterator>

namespace linalg {

	template<class T>
	class Array2DWrapper {
	protected:
		std::vector<std::vector<T>> m_array;
	public:
		Array2DWrapper() = default;

		Array2DWrapper(const std::initializer_list<std::vector<T>> &values) : m_array(values) {
		}

		explicit Array2DWrapper(const std::vector<std::vector<T>> &values) : m_array(values) {
		}

		Array2DWrapper(const unsigned long &height, const unsigned long &width) {
			m_array = std::vector<std::vector<T>>(height, std::vector<T>(width));
		}

		Array2DWrapper(const Array2DWrapper &source) : m_array(source.getWrappedArray()) {
		}

		const T &get(const int &row, const int &col) const {
			return m_array[row][col];
		}

		unsigned long height() const {
			return m_array.size();
		}

		unsigned long width() const {
			return m_array[0].size();
		}

		const std::vector<std::vector<T>> &getWrappedArray() const {
			return m_array;
		}

		class Proxy {
		public:
			explicit Proxy(std::vector<T> &row) : m_row(&row) {}

			T &operator[](int index) {
				return (*m_row)[index];
			}

		private:
			std::vector<T> *m_row;
		};

		Proxy operator[](int index) {
			return Proxy(m_array[index]);
		}

		typename std::vector<std::vector<T>>::iterator begin() {
			return m_array.begin();
		}

		typename std::vector<std::vector<T>>::const_iterator begin() const {
			return m_array.cbegin();
		}

		typename std::vector<std::vector<T>>::iterator end() {
			return m_array.end();
		}

		typename std::vector<std::vector<T>>::const_iterator end() const {
			return m_array.cend();
		}
	};
}

