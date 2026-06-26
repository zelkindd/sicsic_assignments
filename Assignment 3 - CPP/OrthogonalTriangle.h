/*Assignment C++: 3
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*/

#ifndef ORTHOGONAL_TRIANGLE_H
#define ORTHOGONAL_TRIANGLE_H

#include "Shape.h"
#include <cmath> // Needed for sqrt

class OrthogonalTriangle : public Shape {
private:
    double side; // Length of the orthogonal sides

public:
    // Default constructor
    OrthogonalTriangle();

    // Constructor receiving all parameters
    OrthogonalTriangle(const char* colorVal, int widthVal, double sideVal);

    // Destructor - standard explicit declaration
    virtual ~OrthogonalTriangle();

    // Getter and Setter for side
    double getSide() const;
    void setSide(double sideVal);

    // Implementation of pure virtual methods from Shape
    virtual double getPerimeter() const override;
    virtual double getArea() const override;

    // Draw method specific to OrthogonalTriangle
    void draw() const;
};

#endif // ORTHOGONAL_TRIANGLE_H