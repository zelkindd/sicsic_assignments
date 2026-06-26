/*Assignment C++: 3
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

// Circle inherits publicly from Shape
class Circle : public Shape {
private:
    int radius; // Radius of the circle

public:
    // Default constructor
    Circle();

    // Constructor receiving all parameters (color, width, radius)
    Circle(const char* colorVal, int widthVal, int radiusVal);

    // Destructor
    virtual ~Circle() = default;

    // Getter and Setter for radius
    int getRadius() const;
    void setRadius(int radiusVal);

    // Implementation of pure virtual methods from Shape
    virtual double getPerimeter() const override;
    virtual double getArea() const override;
};

#endif // CIRCLE_H