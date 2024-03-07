#pragma once
#include <vector>
#include "Cube.h" // Include your Cube definition

class Face {
public:
    std::vector<Cube*> top;
    std::vector<Cube*> bot;
    std::vector<Cube*> left;
    std::vector<Cube*> right;
    std::vector<std::vector<Cube*>> all;

    bool is45;
    int counter45;

    Face(int size); // Constructor to initialize the vectors
    ~Face(); // Destructor for any needed cleanup
    void rotate(float angle, bool isClockwise, glm::vec3 axis);
    void rotClockWise();
    void rotCounterClock();
};
