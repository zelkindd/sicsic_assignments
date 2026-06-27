/*Assignment C++: 3
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*/

#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"

// Square inherits publicly from Shape
class Square : public Shape {
private:
    double side; // Length of the square's side

public:
    // Default constructor
    Square();

    // Constructor receiving all parameters (color, width, side)
    Square(const char* colorVal, int widthVal, double sideVal);

    // Destructor
    virtual ~Square() = default;

    // Getter and Setter for side
    double getSide() const;
    void setSide(double sideVal);

    // Implementation of pure virtual methods from Shape
    virtual double getPerimeter() const override;
    virtual double getArea() const override;

    // Draw method specific to Square
    void draw() const;
};

#endif // SQUARE_H