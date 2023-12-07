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
#include "GUIElements/Button.h"
#include "GUIElements/EnterValue.h"
#include "GUI.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, GUI* gui, glm::vec2 mousePos);
void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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

    GUI* gui = new GUI(SCR_WIDTH,SCR_HEIGHT);
//    glfwSetWindowUserPointer(window, &gui);
//
//
//    glfwSetMouseButtonCallback(window, mouse_callback);
//    glfwSetKeyCallback(window, key_callback);

    Text text;

//    EnterValue* e = new EnterValue({-0.4,0.4}, {0.25,0.25},{0.5,0.2,0.2}, RoundedSquare, 0.1, 0.0, {0.5,0.5,0.5}, true, SCR_WIDTH, SCR_HEIGHT);
//    Object* b = new Button({0,0}, {0.5,0.5},{0.5,0.2,0.2}, RoundedSquare, 0.1, "8=-:-=8", {0, 0}, 1.5, {0.5,0.5,0.0},new Alignment[2]{Center, Center}, false, false, true, SCR_WIDTH, SCR_HEIGHT);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {


        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        gui->checkInput(window);

//        e->display(shader, texShader);




//        text.RenderText(texShader, "8=-:-=8", {150.0f, 25.0f}, 1.0f, glm::vec3(0.5, 0.8f, 0.2f), new Alignment[2]{Center, Top});
        gui->RenderGUI(shader, texShader);

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
void processInput(GLFWwindow *window, GUI* gui, glm::vec2 mousePos)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
//    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
//        b->clickOnButton(mousePos, true);
//    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
//        b->setPressed(false);
//    }

}

//void mouse_callback(GLFWwindow* window, int button, int action, int mods){
//    double x;
//    double y;
//    glfwGetCursorPos(window, &x, &y);
//    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
//        GUI* gui = static_cast<GUI*>(glfwGetWindowUserPointer(window));
//        gui->click_callback(glm::vec2{x,y});
//    }
//}

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    GUI* gui = static_cast<GUI*>(glfwGetWindowUserPointer(window));
//    gui->key_callback(key, scancode, action, mods);
//}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
