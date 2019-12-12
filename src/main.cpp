#include <iostream>
#include "matrix.h"

int main() {
	
	//создаем матрица со значением 0 по умолчанию
	Matrix<int, 0> matrix_main;
	int N = 10;
	int def_num = 0;
	//заполняем диагонали матрицы
	for (int i = 0; i < N; i++) {
		matrix_main[i][i] = i;
		matrix_main[9 - i][i] = i;
	}
	
	//заполняем значением по умолчанию в шахматном порядке, начиная с [0][0], 25 итераций
	for (int i = 0; i <= (N-1)/2; i++) {
		for (int j = i%2; j < N; j+=2) {
			matrix_main[i][j] = def_num;
			matrix_main[N - 1 - i][N - 1 - j] = def_num;
		}
	}

	//выводим фрагмент матрицы от [1][1] до [8][8]
	std::cout << "Matrix part from [1][1] to [8][8]:" << std::endl;
	std::cout << "----------------" << std::endl;
	for (int i = 1; i < N-1; i++) {
		for (int j = 1; j < N-1; j++) {
			std::cout << matrix_main[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "----------------" << std::endl;
	std::cout << "Matrix size - " << matrix_main.size() << " elements." << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << "Matrix elements:" << std::endl;
	for (auto it : matrix_main) {
		auto index = it.first;
		auto value = it.second;
		std::cout << value << " ";
		for (auto a : index) {
			std::cout << "[" << a << "]";
		}
		std::cout << std::endl;
	}
	return 0;
}
