//#include <movableglm/vec3.hpp>
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "cube.h"
#include "shape.h"
#include "face.h"

enum class Side {
    Front,
    Back,
    Left,
    Right,
    Up,
    Down
};

class RubiksCube {
private:
    std::vector<Cube> cubes;
    Face left, right, up, down, front, back;

public:
    int size;
    float angle;
    bool isClockwise;

    RubiksCube() = default;
    RubiksCube(int size, std::vector<Shape*>& shapes);
    std::vector<Cube*> reverseVec(const std::vector<Cube*>& vec);
    void rotateRubiksCube(const glm::vec3& axis, float angle);
    void rotateFace(Side side);
    void increaseAngle();
    void decreaseAngle();
    void flipRotation();
    void fillFaces(int size);
   
};
