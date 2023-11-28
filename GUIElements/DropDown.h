//
// Created by brado on 11/23/2023.
//

#ifndef PLAYGROUND_DROPDOWN_H
#define PLAYGROUND_DROPDOWN_H

#include "../object.h"
#include "../Text.h"
#include "vector"

class DropDown : Object{
private:
    string textStr;
    glm::vec2 texLoc;
    float texScale;
    glm::vec3 texCol;
    Alignment texAlign[2];
    Text* physicalText;
    vector<string> menuOptions;
    bool open;
    bool inView;

    glm::vec2 scrPixelScale;

public:
    DropDown(glm::vec2 position, glm::vec2 scale, glm::vec3 color, Shape shape, float rsRadius,
             string text, glm::vec2 localTexLoc, float texScale, glm::vec3 texCol, Alignment* texAlign,
             bool toggleable, vector<string> options, bool inView, int scrWidth, int scrHeight);
};


#endif //PLAYGROUND_DROPDOWN_H
