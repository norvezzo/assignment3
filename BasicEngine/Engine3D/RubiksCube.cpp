#include "RubiksCube.h"
#include <iostream> // for debugging


void RubiksCube::fillFaces(int size) {
    int num = 0;
    while (num < 3) {
        int index = 0;
        if (num == 0) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    left.all[j][k] = &cubes.at((0 * size * size + (size - 1 - j) * size + (size - 1 - k) * 1));
                    right.all[j][k] = &cubes.at(((size - 1) * size * size + (size - 1 - j) * size + (size - 1 - k) * 1));
                    index++;
                }
            }
        }
        else if (num == 1) {
            for (int i = 0; i < size; i++) {
                for (int k = 0; k < size; k++) {
                    up.all[i][k] = &cubes.at((i * size * size + (size - 1) * size + k * 1));
                    down.all[i][k] = &cubes.at((i * size * size + 0 * size + k * 1));
                    index++;
                }
            }
        }
        else if (num == 2) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    front.all[i][j] = &cubes.at((i * size * size + (size - 1 - j) * size + (size - 1) * 1));
                    back.all[i][j] = &cubes.at((i * size * size + (size - 1 - j) * size + 0 * 1));
                    index++;
                }
            }
        }
        num++;
    }
}

RubiksCube::RubiksCube(int size, std::vector<Shape*>& shapes) : size(size), left(size), right(size), up(size), down(size), front(size), back(size){
    angle = 90.0f;
    isClockwise = true;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                cubes.push_back(Cube(i * size * size + j * size + k * 1, shapes.at(i * size * size + j * size + k * 1)));
            }
        }
    }
    for (int index = 0; index < size; index++) {
        left.bot[index] = &cubes.at((0 *  size * size + 0 * size + index * 1));
        left.top[index] = &cubes.at((0 *  size * size + (size - 1) * size + (size - 1 - index) * 1));
        left.left[index] = &cubes.at((0 *  size * size + index * size + (size - 1) * 1));
        left.right[index] = &cubes.at((0 *  size * size + (size - 1 - index) * size + 0 * 1));

        right.bot[index] = &cubes.at(((size - 1) *  size * size + 0 * size + index * 1));
        right.top[index] = &cubes.at(((size - 1) *  size * size + (size - 1) * size + (size - 1 - index) * 1));
        right.left[index] = &cubes.at(((size - 1) *  size * size + index * size + (size - 1) * 1));
        right.right[index] = &cubes.at(((size - 1) *  size * size + (size - 1 - index) * size + 0 * 1));

        front.bot[index] = &cubes.at(((size - 1 - index) *  size * size + 0 * size + (size - 1) * 1));
        front.top[index] = &cubes.at((index *  size * size + (size - 1) * size + (size - 1) * 1));
        front.left[index] = &cubes.at((0 *  size * size + index * size + (size - 1) * 1));
        front.right[index] = &cubes.at(((size - 1) *  size * size + (size - 1 - index) * size + (size - 1) * 1));

        back.bot[index] = &cubes.at(((size - 1 - index) *  size * size + 0 * size + 0 * 1));
        back.top[index] = &cubes.at((index *  size * size + (size - 1) * size + 0 * 1));
        back.left[index] = &cubes.at((0 *  size * size + index * size + 0 * 1));
        back.right[index] = &cubes.at(((size - 1) *  size * size + (size - 1 - index) * size + 0 * 1));

        up.bot[index] = &cubes.at(((size - 1 - index) *  size * size + (size - 1) * size + (size - 1) * 1));
        up.top[index] = &cubes.at((index *  size * size + (size - 1) * size + 0 * 1));
        up.left[index] = &cubes.at((0 *  size * size + (size - 1) * size + (size - 1 - index) * 1));
        up.right[index] = &cubes.at(((size - 1) *  size * size + (size - 1) * size + index * 1));

        down.bot[index] = &cubes.at(((size - 1 - index) *  size * size + 0 * size + (size - 1) * 1));
        down.top[index] = &cubes.at((index *  size * size + 0 * size + 0 * 1));
        down.left[index] = &cubes.at((0 *  size * size + 0 * size + (size - 1 - index) * 1));
        down.right[index] = &cubes.at(((size - 1) *  size * size + 0 * size + index * 1));

        fillFaces(size);
    }
}

std::vector<Cube*> RubiksCube::reverseVec(const std::vector<Cube*>& vec) {
    std::vector<Cube*> reversed = vec;
    std::reverse(reversed.begin(), reversed.end());
    return reversed;
}

void RubiksCube::increaseAngle() {
    if (angle < 180.0f)
        angle *= 2.0f;
}

void RubiksCube::decreaseAngle() {
    if (angle > 45.0f)
        angle /= 2.0f;
}

void RubiksCube::flipRotation() {
    angle *= -1.0f;
    isClockwise = !isClockwise;
}

void RubiksCube::rotateRubiksCube(const glm::vec3& axis, float angle) {
    for (auto& cube : cubes) {
        glm::mat4 inv = glm::inverse(cube.shape->getRot());
        glm::vec4 localRotAxis = inv * glm::vec4(axis, 0.0f);
        cube.shape->MyRotate(angle, glm::vec3(localRotAxis), 0);
    }
}

void RubiksCube::rotateFace(Side side) {
    switch (side)
    {
        case Side::Right:
        {
            if (front.is45 || back.is45 || up.is45 || down.is45) {
                std::cout << "can't rotate" << std::endl;
                break;
            }

            right.rotate(angle, isClockwise, glm::vec3(1, 0, 0));

            if ((std::fabs(angle) == 45.0f) && ((right.counter45 == 1) || (right.counter45 == -1) || (right.counter45 == 0))) {
                break;
            }
            else {
                for (int i = 0; i < size; i++) {
                    down.right.at(i) = right.bot.at(i);
                    up.right.at(i) = reverseVec(right.top).at(i);
                    front.right.at(i) = reverseVec(right.left).at(i);
                    back.right.at(i) = right.right.at(i);
                }
                down.top.at(size - 1) = down.right.at(0);
                down.bot.at(0) = down.right.at(size - 1);
                up.top.at(size - 1) = up.right.at(0);
                up.bot.at(0) = up.right.at(size - 1);
                front.top.at(size - 1) = front.right.at(0);
                front.bot.at(0) = front.right.at(size - 1);
                back.top.at(size - 1) = back.right.at(0);
                back.bot.at(0) = back.right.at(size - 1);

                if ((right.counter45 == 2) || (right.counter45 == -2))
                    right.counter45 = 0;
            }
        
        } break;

        case Side::Left:
        {
            if (front.is45 || back.is45 || up.is45 || down.is45) {
                std::cout << "can't rotate" << std::endl;
                break;
            }

            left.rotate(angle, isClockwise, glm::vec3(1, 0, 0));

            if ((std::fabs(angle) == 45.0f) && ((left.counter45 == 1) || (left.counter45 == -1) || (left.counter45 == 0))) {
                break;
            }
            else {
                for (int i = 0; i < size; i++) {
                    down.left.at(i) = reverseVec(left.bot).at(i);
                    up.left.at(i) = left.top.at(i);
                    front.left.at(i) = left.left.at(i);
                    back.left.at(i) = reverseVec(left.right).at(i);
                }

                down.bot.at(size - 1) = down.left.at(0);
                down.top.at(0) = down.left.at(size - 1);
                up.bot.at(size - 1) = up.left.at(0);
                up.top.at(0) = up.left.at(size - 1);
                front.bot.at(size - 1) = front.left.at(0);
                front.top.at(0) = front.left.at(size - 1);
                back.bot.at(size - 1) = back.left.at(0);
                back.top.at(0) = back.left.at(size - 1);

                if ((left.counter45 == 2) || (left.counter45 == -2))
                    left.counter45 = 0;
            }
        } break;

        case Side::Front:
        {
            if (left.is45 || right.is45 || up.is45 || down.is45) {
                std::cout << "can't rotate" << std::endl;
                break;
            }

            front.rotate(angle, isClockwise, glm::vec3(0, 0, 1));

            if ((std::fabs(angle) == 45.0f) && ((front.counter45 == 1) || (front.counter45 == -1) || (front.counter45 == 0))) {
                break;
            }
            else {
                for (int i = 0; i < size; i++) {
                    down.bot.at(i) = front.bot.at(i);
                    up.bot.at(i) = reverseVec(front.top).at(i);
                    left.left.at(i) = front.left.at(i);
                    right.left.at(i) = reverseVec(front.right).at(i);
                }

                down.right.at(size - 1) = down.bot.at(0);
                down.left.at(0) = down.bot.at(size - 1);
                up.right.at(size - 1) = up.bot.at(0);
                up.left.at(0) = up.bot.at(size - 1);
                left.bot.at(size - 1) = left.left.at(0);
                left.top.at(0) = left.left.at(size - 1);
                right.bot.at(size - 1) = right.left.at(0);
                right.top.at(0) = right.left.at(size - 1);

                if ((front.counter45 == 2) || (front.counter45 == -2))
                    front.counter45 = 0;
            }
        } break;

        case Side::Back:
        {
            if (left.is45 || right.is45 || up.is45 || down.is45) {
                std::cout << "can't rotate" << std::endl;
                break;
            }

            back.rotate(angle, isClockwise, glm::vec3(0, 0, 1));

            if ((std::fabs(angle) == 45.0f) && ((back.counter45 == 1) || (back.counter45 == -1) || (back.counter45 == 0))) {
                break;
            }
            else {
                for (int i = 0; i < size; i++) {
                    down.top.at(i) = reverseVec(back.bot).at(i);
                    up.top.at(i) = back.top.at(i);
                    left.right.at(i) = reverseVec(back.left).at(i);
                    right.right.at(i) = back.right.at(i);
                }

                down.left.at(size - 1) = down.top.at(0);
                down.right.at(0) = down.top.at(size - 1);
                up.left.at(size - 1) = up.top.at(0);
                up.right.at(0) = up.top.at(size - 1);
                left.top.at(size - 1) = left.right.at(0);
                left.bot.at(0) = left.right.at(size - 1);
                right.top.at(size - 1) = right.right.at(0);
                right.bot.at(0) = right.right.at(size - 1);

                if ((back.counter45 == 2) || (back.counter45 == -2))
                    back.counter45 = 0;
            }
        } break;

        case Side::Up:
        {
            if (left.is45 || right.is45 || front.is45 || back.is45) {
                std::cout << "can't rotate" << std::endl;
                break;
            }

            up.rotate(angle, isClockwise, glm::vec3(0, 1, 0));

            if ((std::fabs(angle) == 45.0f) && ((up.counter45 == 1) || (up.counter45 == -1) || (up.counter45 == 0))) {
                break;
            }
            else {
                for (int i = 0; i < size; i++) {
                    front.top.at(i) = reverseVec(up.bot).at(i);
                    back.top.at(i) = up.top.at(i);
                    left.top.at(i) = up.left.at(i);
                    right.top.at(i) = reverseVec(up.right).at(i);
                }

                front.left.at(size - 1) = front.top.at(0);
                front.right.at(0) = front.top.at(size - 1);
                back.left.at(size - 1) = back.top.at(0);
                back.right.at(0) = back.top.at(size - 1);
                left.left.at(size - 1) = left.top.at(0);
                left.right.at(0) = left.top.at(size - 1);
                right.left.at(size - 1) = right.top.at(0);
                right.right.at(0) = right.top.at(size - 1);

                if ((up.counter45 == 2) || (up.counter45 == -2))
                    up.counter45 = 0;
            }
        } break;

        case Side::Down:
        {
            if (left.is45 || right.is45 || front.is45 || back.is45) {
                std::cout << "can't rotate" << std::endl;
                break;
            }

            down.rotate(angle, isClockwise, glm::vec3(0, 1, 0));

            if ((std::fabs(angle) == 45.0f) && ((down.counter45 == 1) || (down.counter45 == -1) || (down.counter45 == 0))) {
                break;
            }
            else {
                for (int i = 0; i < size; i++) {
                    front.bot.at(i) = down.bot.at(i);
                    back.bot.at(i) = reverseVec(down.top).at(i);
                    left.bot.at(i) = reverseVec(down.left).at(i);
                    right.bot.at(i) = down.right.at(i);
                }

                front.right.at(size - 1) = front.bot.at(0);
                front.left.at(0) = front.bot.at(size - 1);
                back.right.at(size - 1) = back.bot.at(0);
                back.left.at(0) = back.bot.at(size - 1);
                left.right.at(size - 1) = left.bot.at(0);
                left.left.at(0) = left.bot.at(size - 1);
                right.right.at(size - 1) = right.bot.at(0);
                right.left.at(0) = right.bot.at(size - 1);

                if ((down.counter45 == 2) || (down.counter45 == -2))
                    down.counter45 = 0;
            }
        } break;
    }
}


