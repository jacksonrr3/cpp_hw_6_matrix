/**
\file
\brief Заголовочный файл с описанием классов
Данный файл содержит в себе определения основных
структур и функций, используемых в программе
*/


#pragma once

#include <iostream>
#include <map>
#include <unordered_map>
#include <array>

/**
 * @brief Шаблонный класс бесконечной матрицы
 * T шаблонный параметр типа аргумента
 * def шаблонный параметр значения ячейки по умолчанию
 * rang шаблонный параметр размерности матрицы, по умолчанию 2.
 *
 */
template <typename T, T def, size_t rang = 2>
class Matrix {
	using index = std::array<size_t, rang>;
	using matrix = std::map<index, T>;

	matrix _map;

public:
	Matrix() :_map() {
	}

	size_t size() const {
		return _map.size();
	}

	/**
 * @brief Шаблонный вспомогательный класс, для реализации оператора []
 * T шаблонный параметр типа аргумента
 * def шаблонный параметр значения ячейки по умолчанию
 * ind шаблонный параметр индекса
 *
 */
 //template <typename T, T def, size_t ind>
	template <size_t ind>
	class Proxy {
		friend class Matrix;
		matrix* _matrix_pointer;
		index _index;

		Proxy(matrix* matrix, index other) {
			_matrix_pointer = matrix;
			_index = other;
		}

		Proxy(const Proxy& p) = default;

		void operator=(const Proxy& other) = delete;
	public:
		~Proxy() = default;

		Proxy<ind + 1> operator[](size_t m) {
			_index[ind - 1] = m;
			return (Proxy<ind + 1>(_matrix_pointer, _index));
		}
	};

	/**
* @brief Специализация шаблонного вспомогательного класса, для реализации оператора [] и доступа к элементам
* T шаблонный параметр типа аргумента
* def шаблонный параметр значения ячейки по умолчанию
* шаблонный параметр индекса равняется размерности матрицы
*
*/
	template<>
	class Proxy<rang> {
		friend class Matrix;
		matrix* _matrix_pointer;
		index _index;

		Proxy(matrix* matrix, index other) {
			_matrix_pointer = matrix;
			_index = other;
		}
	public:
		Proxy(const Proxy& p) = default;

		void operator=(const Proxy& other) = delete;
		~Proxy() = default;

		const T& operator[](size_t m) const {
			index temp = _index;
			temp[rang - 1] = m;
			if (_matrix_pointer->find(temp) == _matrix_pointer->end()) {
				temp = def;
			}
			else {
				temp = _matrix_pointer->at(temp);
			}
			return temp;
		}

		operator const T&() const {
			T temp;
			if (_matrix_pointer->find(_index) == _matrix_pointer->end()) {
				temp = def;
			}
			else {
				temp = _matrix_pointer->at(_index);
			}
			return temp;
		}

		Proxy<rang> operator[](size_t m) {
			_index[rang - 1] = m;
			return *this;
		}

		Proxy& operator=(const T& value) {
			if (value != def) {
				_matrix_pointer->emplace(_index, value);
			}
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& out, const Proxy<rang>& proxy) {
			T temp;
			auto it = proxy._matrix_pointer->find(proxy._index);
			if (it == proxy._matrix_pointer->end()) {
				temp = def;
			}
			else {
				temp = proxy._matrix_pointer->at(proxy._index);
			}
			out << temp;
			return out;
		}
	};


	Proxy<2> operator[](size_t n) {
		index temp_ind;
		temp_ind[0] = n;
		Proxy<2> temp(&_map, temp_ind);
		return temp;
	}


	/**
 * @brief Шаблонный вспомогательный класс, для реализации интерфейса итератора дял матрицы
 * T шаблонный параметр типа аргумента
 *
 */
	class Matrix_iterator {
		using Iterator = typename std::map<index, T>::iterator;
		Iterator _it;

	public:

		Matrix_iterator(const Iterator& other) {
			_it = other;
		}

		bool operator!=(const Matrix_iterator& other) {
			return _it != other._it;
		}

		Iterator& operator++() {
			return ++_it;
		}

		auto operator*() {
			return *_it;
		}
	};

	Matrix_iterator begin() {
		return Matrix_iterator(_map.begin());
	}

	Matrix_iterator end() {
		return Matrix_iterator(_map.end());
	}
};
