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
 * dim шаблонный параметр размерности матрицы, по умолчанию 2. 
 *
 */
template <typename T, T def, size_t dim = 2>
class Matrix {
	using index = std::array<size_t, dim>;
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
	class Proxy<dim> {
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

		Proxy& operator=(const T& n) {
			if (n != def) {
				_matrix_pointer->emplace(_index, n);
			}
			return *this;
		}

		const T& operator[](size_t m) const {
			if (_matrix_pointer->find(_index) == _matrix_pointer->end()) {
				return def;
			}
			else {
				return _matrix_pointer->at[_index];
			}
		}

		Proxy<dim>& operator[](size_t m) {
			_index[dim - 1] = m;
			return *this;
		}


		operator const T() const {
			if (_matrix_pointer->find(_index) == _matrix_pointer->end()) {
				return def;
			}
			else {
				return _matrix_pointer->at(_index);
			}
		}


		friend std::ostream& operator<<(std::ostream& out, const Proxy<dim>& proxy) {
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
