#ifndef NUMBER
#include "number.hpp"
#endif

#include <stdlib.h>
#include <cmath>

convertDouble(double input) {
	int posPlaces;
	bool isPositive = true;
	{
		double tinput = input;
		if (input < 0) {
			isPositive = false;
			input *= -1;
		}
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
	// Calculate the bytes for the number
	unsigned int bitsNeeded;
	if (log2(input)==round(log2(input))) {
		bitsNeeded = (int)(log2(input)+1);
	}
	else if (round(log2(input))>log2(input)) {
		bitsNeeded = (int)round(log2(input));
	}
	else {
		bitsNeeded = (int)(round(log2(input))+1);
	}
	unsigned int bytesNeeded = ((double)(bitsNeeded)/8==round((double)(bitsNeeded)/8)) ? bitsNeeded/8 : bitsNeeded/8+1;
	// Calculate bytes for the exponent
	unsigned int bitsNeededE;
	if (log2(posPlaces)==round(log2(posPlaces))) {
		bitsNeededE = (int)(log2(input)+1);
	}
	else if (round(log2(posPlaces))>log2(posPlaces)) {
		bitsNeededE = (int)round(log2(input));
	}
	else {
		bitsNeededE = (int)(round(log2(input))+1);
	}
	unsigned int bytesNeededE = ((double)(bitsNeededE)/8==round((double)(bitsNeededE)/8)) ? bitsNeededE/8 : bitsNeededE/8+1;

	free(storage);
	storage = (char*)malloc(sizeof(char)*bytesNeeded);
	free(exponent);
	storage = (char*)malloc(sizeof(char)*bytesNeededE);
	if (isPositive) {
		unsigned char temp = 1;
		temp << .
		// Add it to the respective char in the respective place
	}
	else {
	}
}
number::number () {
	storage = (char*)malloc(sizeof(char));
	exponent = (char*)malloc(sizeof(char));
}
number::number (double input) {
	storage = (char*)malloc(sizeof(char));
	exponent = (char*)malloc(sizeof(char));
	convertDouble(input);
}
number::number (int input) {
	storage = (char*)malloc(sizeof(char));
	exponent = (char*)malloc(sizeof(char));
	convertInt(input);
}
