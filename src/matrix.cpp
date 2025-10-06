#ifndef MATRIX
#include "matrix.hpp"
#endif

matrix::matrix () {
    num = new number;
}

matrix::~matrix () {
    delete num;
}

matrix::matrix (const matrix& copyee) { // Copy constructor
    num = new number;
    //(*num) = copyee.*num; //I need to add an asignment operator to the number class
}

matrix::matrix (matrix&& movee) { // Move semantics!
    num = movee.num; // Steal the pointer
    movee.~matrix(); // Call the destructor
}

matrix& matrix::operator= (const matrix& copyee) {  // Asignment operator overload

}