//
// Created by brado on 3/5/2023.
//

#include "object.h"


//Private////////////
/* assignBuffandArr
 * Assigned the Buffers and Vertex arrays for this object as well as store the information in a
 * Element array Buffer, which allows us to put 2 triangles together and have OpenGL know what to do
 */
void Object::assignBuffandArr(){
    //Assign Buffers and arrays
    glGenVertexArrays(1, &this->va);
    glGenBuffers(1, &this->vb);
    glGenBuffers(1, &this->eb);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(this->va);


    glBindBuffer(GL_ARRAY_BUFFER, this->vb);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), 0, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), &vertices.front());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eb);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_DYNAMIC_DRAW);

    //Assign vertex attribute pointer telling OpenGL how the array of verts is organized
    //i.e tell it if there is an offset or a stride it needs to be aware of
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Unbinds the buffer and vertex array now that we are done with them
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Enables faceculling so faces facing the other direction from the camera arent being displayed
    glEnable(GL_CULL_FACE);

//    For Testing Purposes:
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void Object::generateCircle() {
    //Creates triangle fan type of sphere:
    float theta = 0;
    float x,y;
    glm::vec2 center = position;
    float radX = scale.x/2;
    float radY = scale.y/2;
    addVerts(vertices, {center, 0.0});

    for(int i = 1; i <= BASE_SUBDIVISIONS; i++){
        float x = position.x + (radX * cos(theta));
        float y = position.y + (radY * sin(theta));
        addVerts(vertices, {x,y, 0.0});
        if(i != BASE_SUBDIVISIONS){
            addIndices(indices, {i, i+1, 0});
        }else{
            addIndices(indices, {i, 1, 0});
        }
        theta += 2 * M_PI/BASE_SUBDIVISIONS;
    }

}

//Method to generate a cube
void Object::generateSquare() {
    //Creates a square out of 2 triangles
    float x,y;
    x = position.x;
    y = position.y;
    addVerts(vertices, {x - scale.x/2,y - scale.y/2, 0.0});
    addVerts(vertices, {x + scale.x/2,y - scale.y/2, 0.0});
    addVerts(vertices, {x + scale.x/2,y + scale.y/2, 0.0});
    addVerts(vertices, {x - scale.x/2,y + scale.y/2, 0.0});

    addIndices(indices, {0,1,3});
    addIndices(indices,{1,2,3});
}

void Object::generateRoundedSquare() {
//    Do this for each of the 4 corners:
//                       \/Duped verts\/
//                      **----------- **
//                  *    |            |    *
//               *       |            |       *
//             *         |            |
//            *----------* <- center of edge rad
//            |
    int extra_points = 1;
    float theta = 0;
    float x,y, circ_x, circ_y;
    //Keeping track of which corner we are on:
    glm::vec2 corner = {1,1}; // 1,1 -> 1,-1 -> -1,-1, -> -1,1
    int xy = 0;

    addVerts(vertices, {position, 0.0});

//    Makes a triangle from all edge points to the center
    for(int i = 1; i <= BASE_SUBDIVISIONS + extra_points; i++){
        if(i%(BASE_SUBDIVISIONS/4+1) == 0){
            corner[xy] *= -1;
            xy = abs(xy - 1);
            theta -= 2 * M_PI/BASE_SUBDIVISIONS;
            extra_points++;
        }

        circ_x = rsRadius * cos(theta);
        circ_y = rsRadius * sin(theta);

        x = position.x + (scale.x/2 - rsRadius) * corner.x + circ_x;
        y = position.y + (scale.y/2 - rsRadius) * corner.y + circ_y;
        addVerts(vertices, {x,y,0.0});

        if(i != BASE_SUBDIVISIONS + extra_points){
            addIndices(indices, {i, i+1, 0});
        }else{
            addIndices(indices, {i, 1, 0});
        }
        theta += 2 * M_PI/BASE_SUBDIVISIONS;
    }

}

//simplifies adding (float)vec3's to a vector<>
void Object::addVerts(vector<float> &vector, glm::vec3 info) {
    vector.push_back(info.x);
    vector.push_back(info.y);
    vector.push_back(info.z);
}

//simplifies adding (int)vec3's to a vector<>
void Object::addIndices(vector<int> &vector, glm::vec3 info) {
    vector.push_back((int) info.x);
    vector.push_back((int) info.y);
    vector.push_back((int) info.z);

}

//Public//////////
/* Object Constructor
 * Holds info about: position, scale, color, and the screen size
 */
Object::Object(glm::vec2 position, glm::vec2 scale, float rsRadius, glm::vec3 color, Shape shape, int scWidth, int scHeight){
    this->position = position;
    this->scale = scale;
    this->rsRadius = rsRadius;
    this->color = color;
    this->scWidth = scWidth;
    this->scHeight = scHeight;

    if(shape == Shape::Square){
        generateSquare();
    }else if(shape == Shape::Circle){
        generateCircle();
    }else if(shape == Shape::RoundedSquare) {
        generateRoundedSquare();
    }else{
        cout<< "ERROR: Invalid Shape Entered: " << endl;
        terminate();
    }

    assignBuffandArr();
}

//Destructor: deletes the created buffers
Object::~Object() {
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &this->eb);
}



/*Display
 * Applys any transformations the object has had and displays the object
 */
void Object::display(Shader* shader) {

    //Calculating Transforms:
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, {position,0.0});


    //Setting Uniforms:
    shader->bindShader();
    shader->setUniformMat4("transform", transform);
    shader->setVec3("color", color);

    //Displaying object
    glBindVertexArray(this->va); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, indices.size() * sizeof(int), GL_UNSIGNED_INT, 0);

}

