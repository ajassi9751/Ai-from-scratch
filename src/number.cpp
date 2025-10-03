#ifndef NUMBER
#include "number.hpp"
#endif

#include <stdlib.h>

convertDouble(double input) {
	int posPlaces;
	bool isPositive = true;
	{
		if (input < 0) {
			isPositive = false;
			input *= -1;
		}
		double tinput = input;
		if (input > 10) {
			int i = 0;
			while (tinput>10) {
				i++;
				tinput /= 10;
			}
		}
		else if (input < 0) {	
			int i = 0;
			while (tinput>10) {
				i++;
				tinput *= 10;
			}
		}
	}
}
number::number () {
	storage = (char*)malloc(sizeof(char));
}
number::number (double input) {
	storage = (char*)malloc(sizeof(char));
	convertDouble(input);
}
number::number (int input) {
	storage = (char*)malloc(sizeof(char));
	convertInt(input);
}
