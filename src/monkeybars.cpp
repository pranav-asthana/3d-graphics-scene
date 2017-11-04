#include "monkeybars.h"
#include "cylinder.h"

MonkeyBars::MonkeyBars(int length, int height)
{
    mesh = new Mesh();
    createMesh(length, height);
}

Mesh * MonkeyBars::getMesh()
{
    return mesh;
}

Mesh * MonkeyBars::createSideMesh(int size)
{
    Mesh * side = new Mesh();
    for (int i = 0; i < size; i++)
    {
        Cylinder * c = new Cylinder(1, 0.05, glm::vec3(1, 0, 0));
        Mesh * mesh = c -> getMesh();
        glm::mat4 T;
        T = glm::translate(T, glm::vec3(0.5, i-(size/2)+0.5*(!(1&size%2)), 0));
        mesh -> transform(T);
        side -> joinMesh(mesh);
    }

    Cylinder * c1 = new Cylinder(size+1, 0.1, glm::vec3(0, 1, 0));
    Mesh * mesh1 = c1 -> getMesh();
    side -> joinMesh(mesh1);
    free(c1);

    Cylinder * c2 = new Cylinder(size+1, 0.1, glm::vec3(0, 1, 0));
    Mesh * mesh2 = c2 -> getMesh();
    glm::mat4 T;
    T = glm::translate(T, glm::vec3(1, 0, 0));
    mesh2 -> transform(T);
    side -> joinMesh(mesh2);
    free(c2);

    return side;
}

void MonkeyBars::createMesh(int length, int height)
{
    height = 4;
    Mesh * side1 = createSideMesh(height);
    Mesh * side2 = createSideMesh(height);
    Mesh * top = createSideMesh(length);

    glm::mat4 T;
    T = glm::translate(T, glm::vec3(0, 0, -length-1));
    side2 -> transform(T);

    glm::mat4 T2;
    T2 = glm::rotate(T2, (float)glm::radians(90.0), glm::vec3(1, 0, 0));
    T2 = glm::translate(T2, glm::vec3(0, -(float)(length+1)/2, -height + (height-1)*0.5));
    top -> transform(T2);

    side1 -> joinMesh(side2);
    side1 -> joinMesh(top);

    this -> mesh = side1;
}
