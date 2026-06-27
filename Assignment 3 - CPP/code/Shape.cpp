/*Assignment C++: 3
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*/

#include "Shape.h"

// validate if the color is allowed
static bool isValidColor(const char* colorVal) {
    if (colorVal == nullptr) return false;
    return (std::strcmp(colorVal, "blue") == 0 ||
            std::strcmp(colorVal, "red") == 0 ||
            std::strcmp(colorVal, "green") == 0);
}

// Constructor receiving all parameters
Shape::Shape(const char* colorVal, int widthVal) : color(nullptr), width(0) {
    if (!isValidColor(colorVal)) {
        throw std::invalid_argument("Invalid color! Allowed colors are: blue, red, green.");
    }
    if (widthVal <= 0) {
        throw std::invalid_argument("Width must be a positive integer.");
    }

    color = new char[std::strlen(colorVal) + 1];
    std::strcpy(color, colorVal);
    width = widthVal;
}

// Default constructor
Shape::Shape() : color(nullptr), width(1) {
    color = new char[5];
    std::strcpy(color, "blue"); // Default safe color
}

// Copy constructor (Deep Copy)
Shape::Shape(const Shape& other) : color(nullptr), width(other.width) {
    if (other.color != nullptr) {
        color = new char[std::strlen(other.color) + 1];
        std::strcpy(color, other.color);
    }
}

// Assignment operator (Deep Copy)
Shape& Shape::operator=(const Shape& other) {
    if (this != &other) {
        char* newColor = nullptr;
        if (other.color != nullptr) {
            newColor = new char[std::strlen(other.color) + 1];
            std::strcpy(newColor, other.color);
        }

        delete[] color; // Free old memory
        color = newColor;
        width = other.width;
    }
    return *this;
}

// Destructor
Shape::~Shape() {
    delete[] color; // Free the dynamically allocated color string
}

// Getters and Setters
const char* Shape::getColor() const {
    return color;
}

void Shape::setColor(const char* colorVal) {
    if (!isValidColor(colorVal)) {
        throw std::invalid_argument("Invalid color! Allowed colors are: blue, red, green.");
    }

    char* newColor = new char[std::strlen(colorVal) + 1];
    std::strcpy(newColor, colorVal);

    delete[] color;
    color = newColor;
}

int Shape::getWidth() const {
    return width;
}

void Shape::setWidth(int widthVal) {
    if (widthVal <= 0) {
        throw std::invalid_argument("Width must be a positive integer.");
    }
    width = widthVal;
}