//
// Created by brado on 10/20/2023.
//

#ifndef PLAYGROUND_GUI_H
#define PLAYGROUND_GUI_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Text.h"
#include "Shader.h"

#include "vector"

// Per element we need:
// location
// scale
// color(s)
// input handling
// a defined output
// Labels



class GUI {
    GUI(int ScreenWidth, int ScreenHeight);
    bool initGUI();
    void RenderGUI(Shader shader);

    vector<bool> checkInputs();
};


#endif //PLAYGROUND_GUI_H
