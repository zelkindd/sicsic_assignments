/*Assignment C++: 3
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*/

#include "OrthogonalTriangle.h"

// Default constructor
OrthogonalTriangle::OrthogonalTriangle() : Shape(), side(1.0) {}

// Constructor receiving all parameters
OrthogonalTriangle::OrthogonalTriangle(const char* colorVal, int widthVal, double sideVal)
    : Shape(colorVal, widthVal), side(1.0) {
    if (sideVal <= 0) {
        throw std::invalid_argument("Triangle side must be a positive number.");
    }
    side = sideVal;
}

// Destructor - standard explicit implementation
OrthogonalTriangle::~OrthogonalTriangle() {
    // Nothing to manually free here as 'side' is a primitive double
    // and the dynamic color is managed by the base class Shape destructor.
}

// Getter and Setter
double OrthogonalTriangle::getSide() const {
    return side;
}

void OrthogonalTriangle::setSide(double sideVal) {
    if (sideVal <= 0) {
        throw std::invalid_argument("Triangle side must be a positive number.");
    }
    side = sideVal;
}

// Implementation of getPerimeter: side + side + (side * sqrt(2))
double OrthogonalTriangle::getPerimeter() const {
    return side + side + (side * std::sqrt(2.0));
}

// Implementation of getArea: (side * side) / 2
double OrthogonalTriangle::getArea() const {
    return (side * side) / 2.0;
}

// Implementation of draw method
void OrthogonalTriangle::draw() const {
    // Cast to int to round down as requested
    int sideInt = static_cast<int>(side);

    for (int i = 1; i <= sideInt; ++i) {
        for (int j = 0; j < i; ++j) {
            std::cout << "* ";
        }
        std::cout << std::endl;
    }
}