/*Assignment C++: 3
Author: Israel Israeli, ID: 01234567
*/

#include <iostream>
#include <string>
#include "Array.h"
#include "Shape.h"
#include "Square.h"
#include "Circle.h"
#include "OrthogonalTriangle.h"

int main() {
    Array<Shape*> shapeArray; // Array of base pointers to manage shapes polymorphically
    int choice = 0;

    // Loop until user chooses option (4) to exit
    while (choice != 4) {
        std::cout << "(1) Add a shape to the end of the array.\n";
        std::cout << "(2) Delete a shape by index.\n";
        std::cout << "(3) Print shape details by index.\n";
        std::cout << "(4) Exit.\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: { // (1) Add a shape to the end of the array
                int shapeType;
                std::cout << "Choose 1 for Square, 2 for Circle, 3 for Triangle: ";
                std::cin >> shapeType;

                // Input validation loop - repeats until valid input is entered
                while (true) {
                    try {
                        std::string color;
                        int width;

                        if (shapeType == 1) { // Square
                            double side;
                            std::cout << "Enter Square's color: ";
                            std::cin >> color;
                            std::cout << "Enter Square's width: ";
                            std::cin >> width;
                            std::cout << "Enter Square's side: ";
                            std::cin >> side;
                            shapeArray.Add(new Square(color.c_str(), width, side));
                        }
                        else if (shapeType == 2) { // Circle
                            int radius;
                            std::cout << "Enter Circle's color: ";
                            std::cin >> color;
                            std::cout << "Enter Circle's width: ";
                            std::cin >> width;
                            std::cout << "Enter Circle's radius: ";
                            std::cin >> radius;
                            shapeArray.Add(new Circle(color.c_str(), width, radius));
                        }
                        else if (shapeType == 3) { // Orthogonal Triangle
                            double side;
                            std::cout << "Enter Triangle's color: ";
                            std::cin >> color;
                            std::cout << "Enter Triangle's width: ";
                            std::cin >> width;
                            std::cout << "Enter Triangle's side: ";
                            std::cin >> side;
                            shapeArray.Add(new OrthogonalTriangle(color.c_str(), width, side));
                        }
                        else {
                            std::cout << "Invalid shape choice!\n";
                            break;
                        }

                        // Input successful, exit the validation loop
                        break;

                    } catch (const std::invalid_argument& e) {
                        // Catch input errors, print message, and prompt for input again
                        std::cout << "Error: " << e.what() << " Please try entering the data again.\n\n";
                    }
                }
                break;
            }

            case 2: { // (2) Delete a shape by index
                int index;
                std::cout << "Enter index to remove: ";
                std::cin >> index;

                try {
                    Shape* removed = shapeArray.remove(index); // Remove from array
                    delete removed; // Free memory of the object to prevent leakage
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }

            case 3: { // (3) Print shape details by index
                int index;
                std::cout << "Enter index to print: ";
                std::cin >> index;

                try {
                    Shape* shape = shapeArray[index];

                    // --- RTTI Section to check the exact type and print correct header ---
                    Square* sq = dynamic_cast<Square*>(shape);
                    Circle* circ = dynamic_cast<Circle*>(shape);
                    OrthogonalTriangle* tri = dynamic_cast<OrthogonalTriangle*>(shape);

                    if (sq != nullptr) {
                        std::cout << "Square details:\n";
                        std::cout << "color=" << shape->getColor()
                                  << ", width=" << shape->getWidth()
                                  << ", side=" << sq->getSide()
                                  << ", area=" << shape->getArea()
                                  << ", perimeter=" << shape->getPerimeter() << "\n";
                        sq->draw(); // Call draw for Square as required
                    }
                    else if (circ != nullptr) {
                        std::cout << "Circle details:\n";
                        std::cout << "color=" << shape->getColor()
                                  << ", width=" << shape->getWidth()
                                  << ", radius=" << circ->getRadius()
                                  << ", area=" << shape->getArea()
                                  << ", perimeter=" << shape->getPerimeter() << "\n";
                    }
                    else if (tri != nullptr) {
                        std::cout << "Orthogonal Triangle details:\n";
                        std::cout << "color=" << shape->getColor()
                                  << ", width=" << shape->getWidth()
                                  << ", side=" << tri->getSide()
                                  << ", area=" << shape->getArea()
                                  << ", perimeter=" << shape->getPerimeter() << "\n";
                        tri->draw(); // Call draw for Triangle as required
                    }

                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }

            case 4: // (4) Exit
                break;

            default:
                break;
        }
    }

    // Final cleanup: free all remaining dynamically allocated shapes in the array
    for (int i = 0; i < shapeArray.getSize(); ++i) {
        delete shapeArray[i];
    }

    return 0;
}