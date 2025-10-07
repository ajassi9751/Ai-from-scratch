#ifndef BITSET
#define BITSET
#include <bitset>
#endif

#ifndef NUMBER
#define NUMBER
class number {
	private:
		// Chars happen to be one byte so im using them
		unsigned char* storage;
		unsigned char* exponent;
		void convertDouble(double input);
		void convertInt(int input);
	public:
	 	// Constructors
		number(); // Default constructor
		number(double input);
		number(int input);
		// Operator overloads
};
#endif
