#ifndef NUMBER
#include "number.hpp"
#endif

#ifndef VECTOR
#include <vector>
#endif

#ifndef MATRIX
#define MATRIX
class matrix {
	private:
        std::vector<std::vector<number>> *storage = nullptr; // Makes the 2d or matrix
    public:
        matrix();
        ~matrix();
        matrix(const matrix& copyee); // Copy constructor
        matrix(matrix&& movee); // Move constructor
        matrix& operator= (const matrix& copyee); // Asignment overload
        matrix& operator= (matrix&& movee) noexcept; // Move assignment overload
        matrix& operator+ (const matrix& addee) const;
        matrix& operator* (const matrix& multiplee) const;
};
#endif
