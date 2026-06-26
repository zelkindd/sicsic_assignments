/*Assignment C++: 3
Authors: Razel Elmoznino ID: 206004095, Dan Zelkind ID: 211571948
*/

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
private:
    T* data;      // Pointer to the first element in the array
    int size;     // The size of the array

public:
    // Default constructor
    Array() : data(nullptr), size(0) {}

    // Copy constructor (Deep Copy)
    Array(const Array& other) : data(nullptr), size(other.size) {
        if (size > 0) {
            data = new T[size];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    // Assignment operator (Deep Copy)
    Array& operator=(const Array& other) {
        if (this != &other) {
            T* newData = nullptr;
            if (other.size > 0) {
                newData = new T[other.size];
                for (int i = 0; i < other.size; ++i) {
                    newData[i] = other.data[i];
                }
            }
            delete[] data;
            data = newData;
            size = other.size;
        }
        return *this;
    }

    // Destructor
    ~Array() {
        delete[] data;
    }

    // Returns the size of the array
    int getSize() const {
        return size;
    }

    // Adds an element to the end of the array
    void Add(const T& element) {
        T* newData = new T[size + 1];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        newData[size] = element;

        delete[] data;
        data = newData;
        size++;
    }

    // Removes an element by index, returns the deleted value, and resizes to size-1
    T remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        T removedValue = data[index];
        T* newData = nullptr;

        if (size - 1 > 0) {
            newData = new T[size - 1];
            int nextIndex = 0;
            for (int i = 0; i < size; ++i) {
                if (i != index) {
                    newData[nextIndex++] = data[i];
                }
            }
        }

        delete[] data;
        data = newData;
        size--;

        return removedValue;
    }

    // Array index operator [] for accessing elements
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Const version of array index operator []
    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Overloaded << operator for printing all elements in the array
    friend std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
        for (int i = 0; i < arr.size; ++i) {
            os << arr.data[i];
            if (i < arr.size - 1) {
                os << " ";
            }
        }
        return os;
    }
};

#endif // ARRAY_H