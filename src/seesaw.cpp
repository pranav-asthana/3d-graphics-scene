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

void SeeSaw::createMesh()
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


    this->mesh -> joinMesh(shaftMesh);
    this->mesh -> joinMesh(seat1Mesh);
    this->mesh -> joinMesh(seat2Mesh);
}
