//
// Created by brado on 11/23/2023.
//

#ifndef PLAYGROUND_ENTERVALUE_H
#define PLAYGROUND_ENTERVALUE_H

#include "../object.h"
#include "../Text.h"

class EnterValue : Object {
private:
    float value;
    bool isSelected;

    glm::vec2 scrPixelScale;

public:
    EnterValue(glm::vec2 position, glm::vec2 scale, glm::vec3 color, Shape shape, float rsRadius);
};


#endif //PLAYGROUND_ENTERVALUE_H
