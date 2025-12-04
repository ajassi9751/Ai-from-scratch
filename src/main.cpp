#include "matrix.hpp"
#include "number.hpp"
#include "intmatrix.hpp"
#include <vector>
#include <utility>
#include <iostream>

int main () {
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> inputother;
	std::vector<int> temp;
	temp.push_back(3);
	input.push_back(temp);
	inputother.push_back(temp);
	intmatrix mat(std::move(input));	
	intmatrix matother(std::move(inputother));
	mat = mat+ matother;
	//matrix mat;
	// number num(3.14);
	// num.print();
	return 0;
}
