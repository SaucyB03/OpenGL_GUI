#include <iostream>
#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "shader.h"
#include "Text.h"
#include "Object.h"
#include "Button.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Button* b, glm::vec2 mousePos);
void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1200;


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    // Initialize glew to utilize OpenGl
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize glew" << endl;
        glfwTerminate();
        return -1;
    }

    // OpenGL state
    // ------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // compile and setup the shader
    // ----------------------------
    Shader* shader = new Shader("../vertexShader.glsl", "../fragmentShader.glsl");
    Shader* texShader = new Shader("../vertexTextShader.glsl", "../fragmentTextShader.glsl");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    texShader->bindShader();
    texShader->setUniformMat4("projection", projection);


    Text text("This is sample text", {25.0f, 25.0f}, 1.0f, glm::vec3(0.5, 0.8f, 0.2f), Left);

    Button* b = new Button({0,0}, {0.5,0.5},{0.5,0.2,0.2}, Square, 0.0, "ooolooo", {0, 0}, 1.5, {0.5,0.5,0.0}, false, false, SCR_WIDTH, SCR_HEIGHT);
    Object* o = new Object({0.125, 0}, {0.5,0.5}, {0.2,0.2,0.2}, Square, SCR_WIDTH, SCR_HEIGHT);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        //get mouse position
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        yPos = SCR_HEIGHT - yPos;

        // input
        // -----
        processInput(window, b, {xPos, yPos});

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        b->display(shader, texShader);
        o->display(shader);

        text.RenderText(texShader);
//        text.RenderText(texShader, "(C) LearnOpenGL.com", {600.0f, 600.0f}, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), Left);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, Button* b, glm::vec2 mousePos)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        b->clickOnButton(mousePos);
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
