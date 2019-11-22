#include <iostream>
#include <map>
#include <unordered_map>
#include <array>

template <typename T, T def, size_t dim = 2>
class Matrix {
	using index = std::array<size_t, dim>;
	using matrix = std::map<index, T>;

	matrix _map;
	//T _default = def;
	//size_t _size = 0;

public:
	Matrix():_map() {
	}

	size_t size() const {
		return _map._size();
	}

	//template <typename T, T def, size_t dim = 2>
	struct Proxy {
		matrix* _matrix_pointer;
		index _index;

		Proxy(matrix* matrix, size_t m){
			_matrix_pointer = matrix;
			_index[0] = m;
		}

		 Proxy(const Proxy& p) = default; 
		//Proxy(Proxy&& p) = delete;

		void operator=(const Proxy& other) = delete;
	
		~Proxy() = default;

		Proxy& operator=(const T& n) {
			_matrix_pointer->emplace( _index, n);
			return *this;
		}

		T operator[](size_t m) const {
			if (_matrix_pointer->find(_index) == _matrix_pointer->end()) {
				return def;
			}
			else {
				return _matrix_pointer->at[_index];
			}
		}

		Proxy& operator[](size_t m) {
			_index[1] = m;
			return *this;
		}

		/*
		//operator const T& () const noexcept
		operator const T&() const {
			if (_matrix_pointer->find(_index) == _matrix_pointer->end()) { 
				return def;
			}
			else {
				return _matrix_pointer->at(_index);
			}
		}*/
	};

	Proxy operator[](size_t n) {
		return Proxy(&_map, n);
	}
	
	


};


int main() {

	std::unordered_map<int, std::unordered_map<int, int> > map;

	std::unordered_map<int, int> temp;
	temp.try_emplace(10, 10);
	map.insert({ 10, temp});
	auto it = map.find(10);
	auto it2 = it->second.find(10);

	Matrix<int, -1> m1;
	int a = m1[10][10];
	m1[100][100] = 320;


	std::unordered_map<int, int> temp2;
	temp2.insert({ 1, 10 });
	temp2.insert_or_assign(1, 20);
	temp2.find(1)->second = 30;

	

	return 0;
}
