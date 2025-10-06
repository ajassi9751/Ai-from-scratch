#ifndef BITSET
#define BITSET
#include <bitset>
#endif

#ifndef NUMBER
#define NUMBER
class number {
	private:
		char* storage;
		char* exponent;
		void convertDouble(double input);
		void convertInt(int input);
	public:
		number();
		number(double input);
		number(int input);
};
#endif
