//
// Created by brado on 3/21/2023.
//

#ifndef PLAYGROUND_SHADER_H
#define PLAYGROUND_SHADER_H


#include "iostream"
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

class Shader {
public:
    unsigned int program;

    /*Constructor
     * recieves vertex / fragment shader files, then calls read to read them into strings
     * then creates the shader using those strings
     */
    Shader(const string &vertexSource, const string &fragSource);
    //Destructor: deletes the created shader
    ~Shader();

    /*readFile
     * reads in the shader files and returns them as string
     */
    string readFile(const string &fileName);
    /*createShader
     * generates the shader based off the parsed shader files as strings
     */
    void createShader(const char* sVert, const char* sFrag);
    /*findErrors
     * checks to see if there has been any errors in the creation of the shaders
     */
    void findErrors(unsigned int errorCheck, char type);

    /*bindShader
     * binds the shader, so that whatever is drawn after with use this shader
     */
    void bindShader();

    //Uniforms:

    /*setUniformMat4
     * allows the program to access the vertex shader and pass a matrix 4 uniform
     * based off the variable name entered
     */
    void setUniformMat4(const char *variableName, glm::mat4 &matrix);
    /*setVec3
     * allows the program to access the vertex shader and pass a vec3 uniform
     * based off the variable name entered
     */
    void setVec3(const char *variableName, glm::vec3 vector);
    void setInt(const char *variableName, int integer);
    void setUniform1i(const char *variableName, int index);
};

#endif //OE43DTESTER_SHADER_H
