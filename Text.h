//
// Created by brado on 10/20/2023.
//

#ifndef PLAYGROUND_TEXT_H
#define PLAYGROUND_TEXT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "map"
#include "filesystem"



class Text {
private:
    /// Holds all state information relevant to a character as loaded using FreeType
    struct Character {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2   Size;      // Size of glyph
        glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };

    std::map<GLchar, Character> Characters;
    unsigned int VAO, VBO;


public:
    Text();
    bool initText();
    void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);

};

#endif //PLAYGROUND_TEXT_H
