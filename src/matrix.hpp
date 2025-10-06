#ifndef NUMBER
#include "number.hpp"
#endif

#ifndef MATRIX
#define MATRIX
class matrix {
	private:
        number* num;
    public:
        matrix();
        ~matrix();
        matrix(const matrix& copyee); // Copy constructor
        matrix(matrix&& movee);
        matrix& operator= (const matrix& copyee); // Asignment overload
};
#endif
