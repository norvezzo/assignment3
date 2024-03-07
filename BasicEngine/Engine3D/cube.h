#pragma once
#include <glm/glm.hpp>
#include "Shape.h" 

class Cube {
public:
    int index; 
    Shape* shape;

    Cube() : index(-1), shape(nullptr) {} 
    Cube(int idx, Shape* shapeData);
    ~Cube();
};

