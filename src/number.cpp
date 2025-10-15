#ifndef NUMBER
#include "number.hpp"
#endif

// Could instead use malloc.h
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
		bitsNeededE = (int)(log2(posPlaces)+1);
	}
	else if (round(log2(posPlaces))>log2(posPlaces)) {
		bitsNeededE = (int)round(log2(posPlaces));
	}
	else {
		bitsNeededE = (int)(round(log2(posPlaces))+1);
	}
	bitsNeededE +=1; // The idea is that there will zeros until there is a one which comes before the mantissa
	// Rename to charsNeeded?
	unsigned int bytesNeededE = ((double)(bitsNeededE)/8==round((double)(bitsNeededE)/8)) ? bitsNeededE/8 : bitsNeededE/8+1;

	// Allocates the neccecary memmory
	if (storage != nullptr) {
		free(storage);
	}
	storage = (unsigned char*)malloc(sizeof(unsigned char)*bytesNeeded);
	stsz = bytesNeeded;
	if (exponent != nullptr) {
		free(exponent);
	}
	exponent = (unsigned char*)malloc(sizeof(unsigned char)*bytesNeededE);
	exsz = bytesNeededE;
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
		temp <<= bitsR;
		// Prefaces the sign bit with a 1
		storage[bytesNeeded-1] |= temp; // This is the "or operator" not the "logical or operator" so it "adds" the bits
		// Adds the sign bit (1 is positive and 0 is negative)
		if (((bytesNeeded-1)*8)<(bitsNeeded-1)) {
			temp >>= 1; // Bit shift right so it will be 11 once added
			storage[bytesNeeded-1] |= temp;
		}
		else {
			temp = 1;
			temp <<= 7;
			storage[bytesNeeded-2] |= temp;
		}
	}
	else {
		// Same as before
		unsigned char temp = 1;
		int bits = bytesNeeded*8 - bitsNeeded;
		int bitsR = 8 - bits;
		temp <<= bitsR;
		storage[bytesNeeded-1] |= temp;
		// No need to add a sign bit because it is already zero by default
	}
	// Do the mantissa
	// Make sure the input has no decimals
	double cleanInput = input;
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
			temp <<= bitShift;
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
		temp <<= bitsR;
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
			temp <<= bitShift;
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

// TO construct classes from temporary arrays
number::number (unsigned char* moveeS, unsigned char* moveeE) {
	storage = moveeS;
	exponent = moveeE;
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
	//movee.~number();
}

number::number (const number& copyee)  {
	if (copyee.storage != nullptr && copyee.exponent != nullptr) {
		// Allocate
		storage = (unsigned char*)malloc(copyee.stsz*sizeof(unsigned char));
		exponent = (unsigned char*)malloc(copyee.exsz*sizeof(unsigned char));
		// Copy
		memcpy(storage,copyee.storage,stsz*sizeof(unsigned char));	
		memcpy(exponent,copyee.exponent,exsz*sizeof(unsigned char));	
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
		// movee.~number();
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
			storage = (unsigned char*)malloc(stsz*sizeof(unsigned char));
			exponent = (unsigned char*)malloc(exsz*sizeof(unsigned char));
			// Copy
			memcpy(storage,copyee.storage,stsz*sizeof(unsigned char));	
			memcpy(exponent,copyee.exponent,exsz*sizeof(unsigned char));	
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

// Need to fully implement
number number::operator+ (const number& addee) const {
	// Calculate the size of the new array
	size_t st;
	size_t ex;
	// Find the starting bit
	// I also might need better logic for the stopping part
	int sStart = 0;
	int eStart = 0;
	// unsigned char* bigArrayS;
	// unsigned char* smallArrayS;
	// unsigned char* bigArrayE;
	// unsigned char* smallArrayE;
	// This will be used to know when to break the loop
	// NOTE: make sure to subract 1 because of the sign bit
	if (stsz >= addee.stsz) {
		st = stsz+1;
		// bigArrayS = storage;
		// smallArrayS = addee.storage;
		// Need to move this outside and calculate all values
		// Maybe should be 8
		for (int i = 8;i>0;--i) {
			if (((storage[st/sizeof(unsigned char)]>>i)&1)==1) {
				sStart = i;
				break;
			}
		}
		// Makes sure we know the position of the bit
		sStart = 8-sStart;
	}
	else {
		st = addee.stsz+1;
		// bigArrayS = addee.storage;
		// smallArrayS = storage;
		// Maybe should be 8
		for (int i = 8;i>0;--i) {
			if (((addee.storage[st/sizeof(unsigned char)]>>i)&1)==1) {
				sStart = i;
				break;
			}
		}
		// Makes sure we know the position of the bit
		sStart = 8-sStart;
	}
	if (exsz >= addee.exsz) {
		ex = exsz+1;
		// bigArrayE = exponent;
		// smallArrayE = addee.exponent;
		// Maybe should be 8
		for (int i = 8;i>0;--i) {
			if (((exponent[ex/sizeof(unsigned char)]>>i)&1)==1) {
				eStart = i;
				break;
			}
		}
		// Makes sure we know the position of the bit
		eStart = 8-eStart;
	}
	else {
		ex = addee.exsz+1;
		// bigArrayE = addee.exponent;
		// smallArrayE = exponent;
		// Maybe should be 8
		for (int i = 8;i>0;--i) {
			if (((addee.exponent[ex/sizeof(unsigned char)]>>i)&1)==1) {
				eStart = i;
				break;
			}
		}
		// Makes sure we know the position of the bit
		eStart = 8-eStart;
	}
	unsigned char* tempS = (unsigned char*)malloc(st); // I think it is garunteed that it needs to be one bit bigger than the largest adden
	unsigned char* tempE = (unsigned char*)malloc(ex);
	bool hasCarry = false;
	// TODO: The issue is with negative
	// Iterate through the array
	// TODO: The other isssue is that this doesn't take into account the sign bit or the bit that marks the end
	int masterIt = 0; // Counts the amount of bits iterated through
	for (int o = 0;o<st/sizeof(unsigned char);++o) {
		// Iterate through the bits
		for (int i = 0;i<8;++i) {
			// So the &1 means that all bits are ignored other than the first one and the bitshift iterates throught the bits
			// Maybe 7 should be 8
			if ((((storage[o]>>i)&1) ^ ((addee.storage[o]>>i)&1))) {
				// Ignore the carry because this will never change the carry
				unsigned char tempB = 1;
				tempB <<= i;
				// Idk if |= is a real operator
				tempS[o] |= tempB;
			}
			else if (((storage[o]>>i)&1)==0 && ((addee.storage[o]>>i)&1)==0) {
				unsigned char tempB;
				if (hasCarry) {
					// Remove the carry
					hasCarry = false;
					tempB = 1;
					tempB <<= i;
					tempS[o] |= tempB;
				}
				else {
					// No need to add 0s because its the same as doing nothing
					//tempB = 0;
					//tempS[o] |= tempB;
				}

			}
			// I think that by now both are garunteed to be 1
			else {
				if (hasCarry) {
					// Techically not needed but its here for readability, the compiler will most likley get rid of it
					hasCarry = true;
					unsigned char tempB = 1;
					tempB <<= i;
					tempS[o] |= tempB;
				}
				else {
					hasCarry = true;
					// Once again there is no need to add a 0
					// unsigned char tempB = 0;
					// tempS[o] |= tempB;
				}
			}
		}
	}
	return number(tempS, tempE);
}

number number::operator* (const number& multiplee) const {
	// Do stuff
	return *this;
}