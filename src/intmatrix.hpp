#ifndef INTMATRIX
#define INTMATRIX

#include <vector>
#include <stdexcept>
#include <utility>

class intmatrix {
	private:
        // Could just not use a pointer here and instead use std::move
        std::vector<std::vector<int>> storage; // Makes the 2d or intmatrix
        // The outer vector is the width, the vertical vector is the height
    public:
        // Constructors
        // Maybe add a constructor that takes a std::vector<std::vector<number>> as a pointer and uses it
        intmatrix();
        ~intmatrix();
        intmatrix(std::vector<std::vector<int>>&& movee); // Steals a pointer to a vector so classes can be made easily
        intmatrix(const intmatrix& copyee); // Copy constructor
        intmatrix(intmatrix&& movee) noexcept; // Move constructor
        // Operators
        intmatrix& operator= (const intmatrix& copyee); // Asignment overload
        intmatrix& operator= (intmatrix&& movee) noexcept; // Move assignment overload
        intmatrix operator+ (const intmatrix& addee) const;
        intmatrix operator- (const intmatrix& subtractee) const; // Wait which number is getting subtracted?
        intmatrix operator* (const intmatrix& multiplee) const;
        intmatrix operator/ (const intmatrix& dividee) const;
        // Methods
        int getHeight() const;
        int getWidth() const;
        void print() const;
};
#endif
