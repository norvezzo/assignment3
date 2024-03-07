#include "Face.h"


Face::Face(int size) {
    top.resize(size, nullptr);
    bot.resize(size, nullptr);
    left.resize(size, nullptr);
    right.resize(size, nullptr);
    all.resize(size);
    for (auto& inner : all)
        inner.resize(size, nullptr);
    is45 = false;
    counter45 = 0;
}

Face::~Face() {
}

void Face::rotClockWise() {
    std::vector<Cube*> temp = this->top;
    this->top = this->left;
    this->left = this->bot;
    this->bot = this->right;
    this->right = temp;
}

void Face::rotCounterClock() {
    std::vector<Cube*> temp = this->top;
    this->top = this->right;
    this->right = this->bot;
    this->bot = this->left;
    this->left = temp;
}

void Face::rotate(float angle, bool isClockwise, glm::vec3 axis) {
    if (std::fabs(angle) == 45.0f) {
        is45 = !is45;

        if (isClockwise)
            counter45++;
        else
            counter45--;
    }

    for (int i = 0; i < this->top.size(); i++) {
        auto& shape = this->top.at(i);
        glm::mat4 inv = glm::inverse(shape->shape->getLocalRot());
        glm::vec4 localRotAxis = inv * glm::vec4(axis, 0.0f);
        shape->shape->MyLocRot(-angle, glm::vec3(localRotAxis), 0);
    }
    for (int i = 1; i < this->right.size(); i++) {
        auto& shape = this->right.at(i);
        glm::mat4 inv = glm::inverse(shape->shape->getLocalRot());
        glm::vec4 localRotAxis = inv * glm::vec4(axis, 0.0f);
        shape->shape->MyLocRot(-angle, glm::vec3(localRotAxis), 0);
    }
    for (int i = 1; i < this->bot.size(); i++) {
        auto& shape = this->bot.at(i);
        glm::mat4 inv = glm::inverse(shape->shape->getLocalRot());
        glm::vec4 localRotAxis = inv * glm::vec4(axis, 0.0f);
        shape->shape->MyLocRot(-angle, glm::vec3(localRotAxis), 0);
    }
    for (int i = 1; i < this->left.size() - 1; i++) {
        auto& shape = this->left.at(i);
        glm::mat4 inv = glm::inverse(shape->shape->getLocalRot());
        glm::vec4 localRotAxis = inv * glm::vec4(axis, 0.0f);
        shape->shape->MyLocRot(-angle, glm::vec3(localRotAxis), 0);
    }

    for (int i = 1; i < all.size() - 1; i++) {
        for (int j = 1; j < all[i].size() - 1; j++) {
            auto& shape = this->all.at(i).at(j);
            glm::mat4 inv = glm::inverse(shape->shape->getLocalRot());
            glm::vec4 localRotAxis = inv * glm::vec4(axis, 0.0f);
            shape->shape->MyLocRot(-angle, glm::vec3(localRotAxis), 0);
        }
    }

    switch (std::abs((int)angle/45)) 
    {
        case 1:
        {
            if ((counter45 != 1) && (counter45 != -1) && (counter45 != 0)) {
                if (isClockwise)
                    rotClockWise();
                else 
                    rotCounterClock();
            }
        } break;
        case 2:
        {
            if (isClockwise)
                rotClockWise();
            else
                rotCounterClock();
        } break;
        case 4:
        {
            int i = 0;
            while (i < 2) {
                if (isClockwise)
                    rotClockWise();
                else
                    rotCounterClock();
                i++;
            }
        } break;
    }
}