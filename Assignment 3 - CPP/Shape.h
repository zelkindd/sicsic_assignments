/*Assignment C++: 3
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <cstring>
#include <stdexcept>

class Shape {
private:
    char* color;     // Dynamic string for the shape's color
    int width;       // Shape's thickness (width)

public:
    // Constructor receiving all parameters
    Shape(const char* colorVal, int widthVal);

    // Default constructor
    Shape();

    // Copy constructor (Deep Copy for color)
    Shape(const Shape& other);

    // Assignment operator (Deep Copy for color)
    Shape& operator=(const Shape& other);

    // Virtual destructor
    virtual ~Shape();

    // Getters and Setters
    const char* getColor() const;
    void setColor(const char* colorVal);

    int getWidth() const;
    void setWidth(int widthVal);

    // Pure virtual methods (Abstract methods)
    virtual double getPerimeter() const = 0;
    virtual double getArea() const = 0;
};

#endif // SHAPE_H