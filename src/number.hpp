#ifndef STDDEF
#define STDDEF
// Provides size_t
#include <cstddef>
#endif

#ifndef NUMBER
#define NUMBER
class number {
	private:
		// Chars happen to be one byte so im using them
		unsigned char* storage = nullptr;
		unsigned char* exponent = nullptr;
		unsigned int stsz = 1;
		unsigned int exsz = 1;
		void convertDouble(double input);
		void convertInt(int input);
	public:
	 	// Constructors
		~number();
		number(); // Default constructor
		number(unsigned char* moveeS, unsigned char* moveeE); // Constructor for new numbers based on basic data types
		number(double input);
		number(int input);
		number(number&& movee) noexcept;
		number(const number& copyee);
		// Operator overloads
		number& operator= (number&& movee) noexcept; // Move assignment overload
		number& operator= (const number& copyee); // Copy assignment overload
		number& operator= (const int& copyee); // Convert from int
		number& operator= (const double& copyee); // Convert from double
		number operator+ (const number& addee) const;
		number operator* (const number& multiplee) const;
		// Methods
};
#endif
