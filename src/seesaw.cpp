#include "seesaw.h"
#include "cylinder.h"
#include "cube.h"

SeeSaw::SeeSaw()
{
    mesh = new Mesh();
    createMesh();
}

Mesh * SeeSaw::getMesh()
{
    return mesh;
}

vector<GLfloat> SeeSaw::getColors()
{
    return colors;
}

Mesh * SeeSaw::drawHandle()
{
    Mesh * handleMesh = new Mesh();
    glm::mat4 T;

    Cylinder * s1 = new Cylinder(0.2, 0.01, glm::vec3(0, 1, 0));
    Mesh * s1Mesh = s1 -> getMesh();
    T = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
    s1Mesh->transform(T);

    Cylinder * s2 = new Cylinder(0.2, 0.01, glm::vec3(0, 1, 0));
    Mesh * s2Mesh = s2 -> getMesh();
    T = glm::translate(glm::mat4(1.0), glm::vec3(0.4, 0, 0));
    s2Mesh->transform(T);

    Cylinder * top = new Cylinder(0.4, 0.01, glm::vec3(1, 0, 0));
    Mesh * topMesh = top -> getMesh();
    T = glm::translate(glm::mat4(1.0), glm::vec3(0.2, 0.1, 0));
    topMesh->transform(T);

    handleMesh -> joinMesh(s1Mesh);
    handleMesh -> joinMesh(s2Mesh);
    handleMesh -> joinMesh(topMesh);

    T = glm::rotate(glm::mat4(1.0), (float)glm::radians(90.0), glm::vec3(0, 1, 0));
    handleMesh->transform(T);

    delete s1;
    delete s2;
    delete top;

    return handleMesh;
}

void SeeSaw::createShaft()
{
    Cylinder * shaft = new Cylinder(6, 0.1, glm::vec3(1, 0, 0));
    Mesh * shaftMesh = shaft -> getMesh();

    glm::mat4 T;

    Cube * seat1 = new Cube(1, 0.1, 0.5);
    Mesh * seat1Mesh = seat1 -> getMesh();
    T = glm::translate(glm::mat4(1.0), glm::vec3(-3, 0, -0.25));
    seat1Mesh->transform(T);

    Cube * seat2 = new Cube(1, 0.1, 0.5);
    Mesh * seat2Mesh = seat2 -> getMesh();
    T = glm::translate(glm::mat4(1.0), glm::vec3(2, 0, -0.25));
    seat2Mesh->transform(T);

    Mesh * handle1 = drawHandle();
    T = glm::translate(glm::mat4(1.0), glm::vec3(2.02, 0.2, 0.2));
    handle1 -> transform(T);

    Mesh * handle2 = drawHandle();
    T = glm::translate(glm::mat4(1.0), glm::vec3(-2.02, 0.2, 0.2));
    handle2 -> transform(T);

    this->mesh -> joinMesh(shaftMesh);
    this->mesh -> joinMesh(seat1Mesh);
    this->mesh -> joinMesh(seat2Mesh);
    this->mesh -> joinMesh(handle1);
    this->mesh -> joinMesh(handle2);


    vector<GLfloat> color_shaft = getColorVector(glm::vec3(0.5, 0.5, 0.5), shaftMesh->getVertices().size());
    vector<GLfloat> color_seat = getColorVector(glm::vec3(0, 1, 0), seat1Mesh->getVertices().size()*2);
    vector<GLfloat> color_handles = getColorVector(glm::vec3(0.75, 0.75, 0.75), handle1->getVertices().size()*2);
    vector<GLfloat> color = joinColors(color_shaft, color_seat);
    colors = joinColors(color, color_handles);

    delete shaft;
    delete seat1;
    delete seat2;
}

void SeeSaw::createMesh()
{
    createShaft();

    glm::mat4 T;
    T = glm::rotate(glm::mat4(1.0), (float)glm::radians(15.0), glm::vec3(0, 0, 1));
    this -> mesh -> transform(T);
}
