/*Assignment C++: 3
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*/

#include "Circle.h"

// Math constant for PI
const double PI = 3.14159;

// Default constructor
Circle::Circle() : Shape(), radius(1) {}

// Constructor receiving all parameters
Circle::Circle(const char* colorVal, int widthVal, int radiusVal)
    : Shape(colorVal, widthVal), radius(1) {
    if (radiusVal <= 0) {
        throw std::invalid_argument("Circle radius must be a positive integer.");
    }
    radius = radiusVal;
}

// Getter and Setter
int Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(int radiusVal) {
    if (radiusVal <= 0) {
        throw std::invalid_argument("Circle radius must be a positive integer.");
    }
    radius = radiusVal;
}

// Implementation of getPerimeter (2 * PI * radius)
double Circle::getPerimeter() const {
    return 2.0 * PI * radius;
}

// Implementation of getArea (PI * radius * radius)
double Circle::getArea() const {
    return PI * radius * radius;
}