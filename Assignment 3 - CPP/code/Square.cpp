/*Assignment C++: 3
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*/

#include "Square.h"

// Default constructor
Square::Square() : Shape(), side(1.0) {}

// Constructor receiving all parameters
Square::Square(const char* colorVal, int widthVal, double sideVal)
    : Shape(colorVal, widthVal), side(1.0) {
    if (sideVal <= 0) {
        throw std::invalid_argument("Square side must be a positive number.");
    }
    side = sideVal;
}

// Getter and Setter
double Square::getSide() const {
    return side;
}

void Square::setSide(double sideVal) {
    if (sideVal <= 0) {
        throw std::invalid_argument("Square side must be a positive number.");
    }
    side = sideVal;
}

// Implementation of getPerimeter (side * 4)
double Square::getPerimeter() const {
    return side * 4.0;
}

// Implementation of getArea (side * side)
double Square::getArea() const {
    return side * side;
}

// Implementation of draw method
void Square::draw() const {
    // Cast to int to round down as requested
    int sizeInt = static_cast<int>(side);

    for (int i = 0; i < sizeInt; ++i) {
        for (int j = 0; j < sizeInt; ++j) {
            std::cout << "* ";
        }
        std::cout << std::endl;
    }
}