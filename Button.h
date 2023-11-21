//
// Created by brado on 10/24/2023.
//

#ifndef PLAYGROUND_BUTTON_H
#define PLAYGROUND_BUTTON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Text.h"
#include "object.h"


class Button : public Object {
private:
    string textStr;
    glm::vec2 texLoc;
    float texScale;
    glm::vec3 texCol;
    Alignment texAlign[2];
    Text* physicalText;
    bool toggleable;
    bool On;

    glm::vec2 scrPixelScale;

public:
    Button(glm::vec2 position, glm::vec2 scale, glm::vec3 color, Shape shape, float rsRadius,
           string text, glm::vec2 localTexLoc, float texScale, glm::vec3 texCol, Alignment* texAlign,
           bool toggleable, bool defaultVal, int scrWidth, int scrHeight);

    Button(glm::vec2 position, glm::vec2 scale, glm::vec3 color, Shape shape, float rsRadius,
           string text, glm::vec2 localTexLoc, float texScale, glm::vec3 texCol,
           bool toggleable, bool defaultVal, int scrWidth, int scrHeight);

    Button(glm::vec2 position, glm::vec2 scale, glm::vec3 color, Shape shape, float rsRadius,
           string text, float texScale, glm::vec3 texCol, Alignment* texAlign,
           bool toggleable, bool defaultVal, int scrWidth, int scrHeight);

    Button(glm::vec2 position, glm::vec2 scale, glm::vec3 color, Shape shape, float rsRadius,
           bool toggleable, bool defaultVal, int scrWidth, int scrHeight);
    ~Button();

    void display(Shader* objShader, Shader* texShader);
    bool clickOnButton(glm::vec2 clickPos);

};


#endif //PLAYGROUND_BUTTON_H
