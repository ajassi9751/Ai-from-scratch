#include "intmatrix.hpp"

intmatrix::intmatrix () {
    // storage = new std::vector<std::vector<number>>;
}

intmatrix::~intmatrix () {
    // delete storage;
}

// Takes an r value reference to a vector that it steals using std::move (better than using raw pointers)
// Needed for operatons that have to return a new intmatrix
intmatrix::intmatrix(std::vector<std::vector<int>>&& movee) {
    storage = std::move(movee);
}

intmatrix::intmatrix (const intmatrix& copyee) { // Copy constructor
    // storage = new std::vector<std::vector<number>>;
    // Std vector uses its own assignment operator to copy
    // *storage = *copyee.storage;
    storage = copyee.storage;
}

intmatrix::intmatrix (intmatrix&& movee) noexcept { // Move constructor
    // storage = movee.storage; // Steal the pointer
    // movee.~intmatrix(); // Call the destructor
    storage = std::move(movee.storage);
}

intmatrix& intmatrix::operator= (const intmatrix& copyee) {  // Asignment operator overload
    if (this == &copyee) {
        return *this;
    }
    else {
        // storage = new std::vector<std::vector<number>>;
        // Std vector uses its own assignment operator to copy
        // *storage = *copyee.storage;
    	storage = copyee.storage; // Steal the pointer
        return *this;
    }
}

intmatrix& intmatrix::operator= (intmatrix&& movee) noexcept {
    if (this == &movee) {
        return *this;
    }
    else {
        storage = movee.storage; // Steal the pointer
        // movee.~intmatrix(); // Call the destructor
        return *this;
    }
}

intmatrix intmatrix::operator+ (const intmatrix& addee) const {
    if (getHeight() == addee.getHeight() && getWidth() == addee.getHeight()) {
        // Creates the vector that will be used to create the class
        // std::vector<std::vector<number>>* temp = new std::vector<std::vector<number>>;
        std::vector<std::vector<int>> temp;
        // Makes sure there is enough space in the vector
        // temp->resize(getWidth());
        temp.resize(getWidth());
        for (std::vector<int>& vec : temp) {
            vec.resize(getHeight());
        }
        // Creates a new vector with the result of the added values
        // Iterates through both vectors
        for (int o = 0;o<getWidth();++o) {
            for (int i = 0;i<getHeight();++i) {
                // temp->at(o).at(i) = storage->at(o).at(i) + addee.storage->at(o).at(i);
                temp.at(o).at(i) = storage.at(o).at(i) + addee.storage.at(o).at(i);
            }
        }
        // return intmatrix(temp);
        return intmatrix(std::move(temp));
    }
    else {
        // Make sure to handle accordingly
        throw std::invalid_argument("intmatrix dimensions don't match.");
        // Need to use try catch for this to work
    }
}

// I think everything here is wrong depending on the way the intmatrix faces and grows in 2d space
intmatrix intmatrix::operator* (const intmatrix& multiplee) const {
    if (getWidth() == multiplee.getHeight()) {
        // Creates the vector that will be used to create the class
        // std::vector<std::vector<number>>* temp = new std::vector<std::vector<number>>;
        std::vector<std::vector<int>> temp;
        // Makes sure there is enough space in the vector
        // temp->resize(getHeight());
        temp.resize(getHeight());
        for (std::vector<int>& vec : temp) {
            vec.resize(multiplee.getWidth());
        }
        // Might need to iterate backwards for it to work
        // Iterates through the hieght of storage
        for (int o = 0;o<getHeight();++o) {
            // Iterates through the width of the multiplee
            for (int s = 0;s<multiplee.getWidth();++s) {
                std::vector<int> rtemp;
                // Iterates through the element
                for (int i = 0;i<getWidth();++i) {
                    // This is might be wrong
                    // rtemp.push_back(storage->at(i).at(o)*multiplee.storage->at(s).at(i));
                    rtemp.push_back(storage.at(i).at(o)*multiplee.storage.at(s).at(i));
                }
                int num;
                // Reference to prevent copying large objects
                for (const int& rnum : rtemp) {
                    num = num + rnum;
                }
                // Definetly wrong
                // temp->at(s).at(o) = num;
                temp.at(s).at(o) = num;
            }
       }
       // return intmatrix(temp);
       return intmatrix(std::move(temp));
    }
    else {
        throw std::invalid_argument("intmatrix dimensions don't match.");
    }
}

int intmatrix::getHeight () const {
    // Hopefully the array is garunteed to be initialized by a constructor and doesn't deference a nullptr but I think the vectors methods are safe
    // return storage->size();
    return storage.size();
}

int intmatrix::getWidth () const {
    // return storage->front().size();
    return storage.front().size();
}

void intmatrix::print () const {
    // Might be collumn
    for (const std::vector<int>& row : storage) {
        // Might be row
        for (const int& collumn : row) {

        }
    }
}