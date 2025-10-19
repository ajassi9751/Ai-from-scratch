#ifndef MATRIX
#include "matrix.hpp"
#endif

matrix::matrix () {
    storage = new std::vector<std::vector<number>>;
}

matrix::~matrix () {
    delete storage;
}

// Needed for operatons that have to return a new matrix
matrix::matrix(std::vector<std::vector<number>>* movee) {
    storage = movee;
}

matrix::matrix (const matrix& copyee) { // Copy constructor
    storage = new std::vector<std::vector<number>>;
    // Std vector uses its own assignment operator to copy
    *storage = *copyee.storage;
}

matrix::matrix (matrix&& movee) noexcept { // Move constructor
    storage = movee.storage; // Steal the pointer
    // movee.~matrix(); // Call the destructor
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
        // movee.~matrix(); // Call the destructor
        return *this;
    }
}

matrix matrix::operator+ (const matrix& addee) const {
    if (getHeight() == addee.getHeight() && getWidth() == addee.getHeight()) {
        // Creates the vector that will be used to create the class
        std::vector<std::vector<number>>* temp = new std::vector<std::vector<number>>;
        // Makes sure there is enough space in the vector
        temp->resize(getWidth());
        for (std::vector<number>& vec : *temp) {
            vec.resize(getHeight());
        }
        // Creates a new vector with the result of the added values
        // Iterates through both vectors
        for (int o = 0;o<getWidth();++o) {
            for (int i = 0;i<getHeight();++i) {
                temp->at(o).at(i) = storage->at(o).at(i) + addee.storage->at(o).at(i);
            }
        }
        return matrix(temp);
    }
    else {
        // Make sure to handle accordingly
        throw std::invalid_argument("Matrix dimensions don't match.");
        // Need to use try catch for this to work
    }
}

// I think everything here is wrong depending on the way the matrix faces and grows in 2d space
matrix matrix::operator* (const matrix& multiplee) const {
    if (getWidth() == multiplee.getHeight()) {
        // Creates the vector that will be used to create the class
        std::vector<std::vector<number>>* temp;
        // Makes sure there is enough space in the vector
        temp->resize(getHeight());
        for (std::vector<number>& vec : *temp) {
            vec.resize(multiplee.getWidth());
        }
        // Might need to iterate backwards for it to work
        // Iterates through the hieght of storage
        for (int o = 0;o<getHeight();++o) {
            // Iterates through the width of the multiplee
            for (int s = 0;s<multiplee.getWidth();++s) {
                std::vector<number> rtemp;
                // Iterates through the element
                for (int i = 0;i<getWidth();++i) {
                    // This is might be wrong
                    rtemp.push_back(storage->at(i).at(o)*multiplee.storage->at(s).at(i));
                }
                number num;
                // Reference to prevent copying large objects
                for (const number& rnum : rtemp) {
                    num = num + rnum;
                }
                // Definetly wrong
                temp->at(s).at(o) = num;
            }
       }
       return matrix(temp);
    }
    else {
        throw std::invalid_argument("Matrix dimensions don't match.");
    }
}

int matrix::getHeight () const {
    // Hopefully the array is garunteed to be initialized by a constructor and doesn't deference a nullptr but I think the vectors methods are safe
    return storage->size();
}

int matrix::getWidth () const {
    return storage->front().size();
}