#ifndef NUMBER
#include "number.hpp"
#endif

// Could instead use malloc.h
#include <stdlib.h>
#include <cstring>
#include <cmath>

void number::convertDouble(double input) {
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
			posPlaces = i;
		}
		else if (input < 0) {
			int i = 0;
			while (tinput>10) {
				i++;
				tinput *= 10;
			}
			posPlaces = i;
		}
		else {
			posPlaces = 1; // Maybe change
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
	// Rename to charsNeeded?
	unsigned int bytesNeededE = ((double)(bitsNeededE)/8==round((double)(bitsNeededE)/8)) ? bitsNeededE/8 : bitsNeededE/8+1;

	// Allocates the neccecary memmory
	if (storage != nullptr) {
		free(storage);
	}
	storage = (unsigned char*)malloc(sizeof(unsigned char)*bytesNeeded);
	if (exponent != nullptr) {
		free(exponent);
	}
	exponent = (unsigned char*)malloc(sizeof(unsigned char)*bytesNeededE);
	// Yes im setting chars to int values because I tested it and it sets it to the bianary value
	for (int i = 0; i < bytesNeeded; i++) {
		storage[i] = 0; // Assures that all chars are set to 00000000 because that is the bianary value of 0
	}
	for (int i = 0; i < bytesNeededE; i++) {
		exponent[i] = 0; // Assures that all chars are set to 00000000 because that is the bianary value of 0
	}
	if (isPositive) {
		unsigned char temp = 1;
		// Might need to change
		int bits = bytesNeeded*8 - bitsNeeded;
		int bitsR = 8 - bits;
		temp = temp << bitsR;
		// Prefaces the sign bit with a 1
		storage[bytesNeeded-1] |= temp; // This is the "or operator" not the "logical or operator" so it "adds" the bits
		// Adds the sign bit (1 is positive and 0 is negative)
		if (((bytesNeeded-1)*8)<(bitsNeeded-1)) {
			temp = temp >> 1; // Bit shift right so it will be 11 once added
			storage[bytesNeeded-1] |= temp;
		}
		else {
			temp = 1;
			temp = temp << 7;
			storage[bytesNeeded-2] |= temp;
		}
	}
	else {
		// Same as before
		unsigned char temp = 1;
		int bits = bytesNeeded*8 - bitsNeeded;
		int bitsR = 8 - bits;
		temp = temp << bitsR;
		storage[bytesNeeded-1] |= temp;
		// No need to add a sign bit because it is already zero by default
	}
	// Do the mantissa
	// Make sure the input has no decimals
	int cleanInput = input;
	if (round(input) != input) {
		while(round(cleanInput) != input) {
			cleanInput *= 10;	
		}
	}
	else {
		cleanInput = input;
	}
	// Actually do the bianary stuff
	// TODO: Might be reversed
	double place = 0;
	while (cleanInput != 0) {
		if (cleanInput/2 != round(cleanInput/2)) {
			// Add a one
			unsigned char temp = 1;
			// Calculate the bitshift
			int index = round(place/8); // Finds which array to use (not doing +1 because array indexes start at 0)
			int bitShift = place - index*8;
			// Do the bitshift
			temp = temp << bitShift;
			// Add it to the storage
			storage[index] |= temp;
			// Note: the integer version may need to be casted to a double
			cleanInput = round(cleanInput/2)-1; // It will get rounded up so -1
		}
		else {
			// Add a zero (do nothing)
			cleanInput = cleanInput/2;
		}
		place++;
	}
	// Do the exponent. Note: The exponent shouldn't be negative so there is no need for a sign bit
	// Used an empty scope ({}) to make sure stack allocated memory would be freed early and for organization
	{
		// Prefaces the mantissa with a 1
		unsigned char temp = 1;
		int bits = bytesNeeded*8 - bitsNeeded;
		int bitsR = 8 - bits;
		temp = temp << bitsR;
		exponent[bytesNeeded-1] |= temp;
	}
	// Do bianary stuff
	place = 0;
	double tempPlace = posPlaces;
	while (tempPlace != 0) {
		if (tempPlace/2 != round(tempPlace/2)) {
			// Add a one
			unsigned char temp = 1;
			// Calculate the bitshift
			int index = round(place/8); // Finds which array to use (not doing +1 because array indexes start at 0)
			int bitShift = place - index*8;
			// Do the bitshift
			temp = temp << bitShift;
			// Add it to the storage
			exponent[index] |= temp;
			// Note: the integer version may need to be casted to a double
			tempPlace = round(tempPlace/2)-1; // It will get rounded up so -1
		}
		else {
			// Add a zero (do nothing)
			tempPlace = tempPlace/2;
		}
		place++;
	}
}

void number::convertInt (int input) {
	// Simmilar to convertDouble but have to be carefull of integer division
	// I can probably just cast the input to a double because they are 64 bits vs 32 bits so it wont overflow
}

number::~number () {
	if (storage != nullptr) {
		free(storage);
	}
	if (exponent != nullptr) {
		free(exponent);
	}
}

number::number () {
	// Is the allocation really needed?
	storage = (unsigned char*)malloc(sizeof(unsigned char));
	exponent = (unsigned char*)malloc(sizeof(unsigned char));
}

number::number (double input) {
	// Is the allocation really needed?
	storage = (unsigned char*)malloc(sizeof(unsigned char));
	exponent = (unsigned char*)malloc(sizeof(unsigned char));
	convertDouble(input);
}

number::number (int input) {
	// Is the allocation really needed?
	storage = (unsigned char*)malloc(sizeof(unsigned char));
	exponent = (unsigned char*)malloc(sizeof(unsigned char));
	//convertInt(input);
}

number::number (number&& movee) noexcept {
	// Need to check if movee.storage and exponent are nullptr or maybe not
	// Also its probably not possible to be nullptr
	storage = movee.storage;
	exponent = movee.exponent;
	movee.storage = nullptr;
	movee.exponent = nullptr;
	movee.~number();
}

number::number (const number& copyee)  {
	if (copyee.storage != nullptr && copyee.exponent != nullptr) {
		// Allocate
		storage = (unsigned char*)malloc(sizeof(copyee.storage));
		exponent = (unsigned char*)malloc(sizeof(copyee.exponent));
		// Copy
		memcpy(storage,copyee.storage,sizeof(copyee.storage));	
		memcpy(exponent,copyee.exponent,sizeof(copyee.exponent));	
	}
	else {
		// Replicate the default constructor
		// Is this the correct behavior?
		storage = (unsigned char*)malloc(sizeof(unsigned char));
		exponent = (unsigned char*)malloc(sizeof(unsigned char));
	}
}

// Should this really be noexcept
number& number::operator= (number&& movee) noexcept { // Move assignment operator
	// If its the same object return it
	if (this == &movee) {
		return *this;
	}
	else {
		// Wait how does this work if these are private members
		if (storage != nullptr) {
			free(storage);
		}
		if (exponent != nullptr) {
			free(exponent);
		}
		// Need to check if movee.storage and exponent are nullptr or maybe not
		// Also its probably not possible to be nullptr
		storage = movee.storage;
		exponent = movee.exponent;
		movee.storage = nullptr;
		movee.exponent = nullptr;
		movee.~number();
		return *this;
	}
}

number& number::operator= (const number& copyee) {
	// If its the same object just return it
	if (this == &copyee) {
		return *this;
	}
	else {
		// I don't think it is possible for the object to have nullptr's
		if (copyee.storage != nullptr && copyee.exponent != nullptr) {
			// Free memory
			// Couldn't I just not do this?
			if (storage != nullptr) {
				free(storage);
			}
			if (exponent != nullptr) {
				free(exponent);
			}
			// Allocate
			storage = (unsigned char*)malloc(sizeof(copyee.storage));
			exponent = (unsigned char*)malloc(sizeof(copyee.exponent));
			// Copy
			memcpy(storage,copyee.storage,sizeof(copyee.storage));	
			memcpy(exponent,copyee.exponent,sizeof(copyee.exponent));	
			// Return for linked statements
			return *this;
		}
		else {
			// Replicate the default constructor
			// Is this the correct behavior?
			storage = (unsigned char*)malloc(sizeof(unsigned char));
			exponent = (unsigned char*)malloc(sizeof(unsigned char));
			return *this;
		}
	}
}

number& number::operator= (const int& copyee) {
	convertInt(copyee);
	return *this;
}

number& number::operator= (const double& copyee) {
	convertDouble(copyee);
	return *this;
}

//number number::operator+ (const number& addee) const {
	// TODO: Do this
//}