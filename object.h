//Parent Class of all onscreen objects

#ifndef PLAYGROUND_OBJECT_H
#define PLAYGROUND_OBJECT_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <vector>

#include "Shader.h"

//Shape Types:
enum Shape{
    Square,
    Circle,
    RoundedSquare
};

class Object {
private:
    int BASE_SUBDIVISIONS = 64;
    int RS_BS = 15;

    int scWidth;
    int scHeight;

    float rsRadius;

    //Object information for buffers
    vector<float> vertices;
    vector<int> indices;

    //Add necessary buffers
    unsigned int va, vb, eb;

    /* assignBuffandArr
     * Assigned the Buffers and Vertex arrays for this object as well as store the information in a
     * Element array Buffer, which allows us to put 2 triangles together and have OpenGL know what to do
     */
    void assignBuffandArr();

    //Generates the respective 3D Shapes
    void generateCircle();
    void generateSquare();
    void generateRoundedSquare();


    //Simplifies adding vec3's to vectors<>
    static void addVerts(vector<float> &vector, glm::vec3 info);
    static void addIndices(vector<int> &vector, glm::vec3 info);

protected:
    glm::vec2 convertPixToScSp(glm::vec2 pixCoord);
    glm::vec2 convertScSpToPix(glm::vec2 scSpCoord);

public:
    glm::vec2 position;
    glm::vec2 scale;
    glm::vec3 color;

    /* Object Constructor
     * Holds info about: position, scale, velocity, color, if its dynamic / static, and the screen size
     */
    Object(glm::vec2 position, glm::vec2 scale, float rsRadius, glm::vec3 color, Shape shape, int scWidth, int scHeight);
    Object(glm::vec2 position, glm::vec2 scale, glm::vec3 color, Shape shape, int scWidth, int scHeight);
    ~Object();

    /*Display
     * Applys any transformations the object has had and displays the object
     */
    void display(Shader* shader);



};


#endif //PLAYGROUND_OBJECT_H
