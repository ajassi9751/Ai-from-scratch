#ifndef NUMBER
#include "number.hpp"
#endif

#include <stdlib.h>
#include <cmath>

convertDouble(double input) {
	// Determines the if the number is poitive or negative and how many decimal places there are
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
	bitsNeeded += 2; // The idea is that there will zeros until there is a one which comes before the sign bit and the mantissa
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
	bitsNeededE +=1; // The idea is that there will zeros until there is a one which comes before the mantissa
	unsigned int bytesNeededE = ((double)(bitsNeededE)/8==round((double)(bitsNeededE)/8)) ? bitsNeededE/8 : bitsNeededE/8+1;

	// Allocates the neccecary memmory
	free(storage);
	storage = (char*)malloc(sizeof(char)*bytesNeeded);
	free(exponent);
	storage = (char*)malloc(sizeof(char)*bytesNeededE);
	if (isPositive) {
		unsigned char temp = 1;
		int indexOfArray;
		for (int i = 0; i < bitsNeeded; i++) {
			bitsNeeded
		}
		temp << (bitsNeeded-1);
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
