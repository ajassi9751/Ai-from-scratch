#ifndef MATRIX
#include "matrix.hpp"
#endif

matrix::matrix () {
    storage = new std::vector<std::vector<number>>;
}

matrix::~matrix () {
    delete storage;
}

matrix::matrix (const matrix& copyee) { // Copy constructor
    if (this == &copyee) {
        // Do nothing
    }
    else {
        storage = new std::vector<std::vector<number>>;
        // Std vector uses its own assignment operator to copy
        *storage = *copyee.storage;
    }
}

matrix::matrix (matrix&& movee) { // Move constructor
    if (this == &movee) {
        // Do nothing
    }
    else {
        storage = movee.storage; // Steal the pointer
        movee.~matrix(); // Call the destructor
    }
}

matrix& matrix::operator= (const matrix& copyee) {  // Asignment operator overload
    if (this == &copyee) {
        return *this;
    }
    else {
        storage = new std::vector<std::vector<number>>;
        // Std vector uses its own assignment operator to copy
        *storage = *copyee.storage;
        return *this;
    }
}

matrix& matrix::operator= (matrix&& movee) noexcept {
    if (this == &movee) {
        return *this;
    }
    else {
        storage = movee.storage; // Steal the pointer
        movee.~matrix(); // Call the destructor
        return *this;
    }
}

// matrix& matrix::operator+ (const matrix& addee) const {

// }

// matrix& matrix::operator* (const matrix& multiplee) const {

// }