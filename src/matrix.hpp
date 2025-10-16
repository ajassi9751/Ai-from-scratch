#ifndef NUMBER
#include "number.hpp"
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef EXCEPT
#define EXCEPT
#include <stdexcept>
#endif

#ifndef MATRIX
#define MATRIX
class matrix {
	private:
        std::vector<std::vector<number>> *storage = nullptr; // Makes the 2d or matrix
        // The outer vector is the width, the vertical vector is the height
    public:
        // Constructors
        // Maybe add a constructor that takes a std::vector<std::vector<number>> as a pointer and uses it
        matrix();
        ~matrix();
        matrix(std::vector<std::vector<number>>* movee); // Steals a pointer to a vector so classes can be made easily
        matrix(const matrix& copyee); // Copy constructor
        matrix(matrix&& movee) noexcept; // Move constructor
        // Operators
        matrix& operator= (const matrix& copyee); // Asignment overload
        matrix& operator= (matrix&& movee) noexcept; // Move assignment overload
        matrix operator+ (const matrix& addee) const;
        matrix operator- (const matrix& subtractee) const; // Wait which number is getting subtracted?
        matrix operator* (const matrix& multiplee) const;
        matrix operator/ (const matrix& dividee) const;
        // Methods
        int getHeight() const;
        int getWidth() const;
};
#endif
