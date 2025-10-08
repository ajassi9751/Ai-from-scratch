#include "matrix.hpp"
#include "number.hpp"
#include <stdio.h>
#include <iostream>

int main () {
	// 00010000
	// 00000001
	// <<
	// >>
	// 00000001
	unsigned char c = 16;
	unsigned char x = c>>5;
	bool b = x==' ';
	// 00010001
	//printf("%c%c",c|x);
	std::cout << b;
	return 0;
}
