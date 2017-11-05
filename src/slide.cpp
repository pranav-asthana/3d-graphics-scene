#include "slide.h"
#include "cylinder.h"
#include "cube.h"

Slide::Slide(int height)
{
    mesh = Mesh();
    createMesh(height);
}

Mesh Slide::getMesh()
{
    return mesh;
}

Mesh Slide::createLadderMesh(int height)
{
    Mesh ladder = Mesh();
    for (int i = 0; i < height; i++)
    {
        Cylinder c = Cylinder(1, 0.05, glm::vec3(1, 0, 0));
        Mesh mesh = c.getMesh();
        glm::mat4 T;
        T = glm::translate(T, glm::vec3(0.5, i-(height/2)+0.5*(!(1&height%2)), 0));
        mesh.transform(T);
        ladder.joinMesh(mesh);
    }

    Cylinder c1 = Cylinder(height+1, 0.1, glm::vec3(0, 1, 0));
    Mesh mesh1 = c1.getMesh();
    ladder.joinMesh(mesh1);


    Cylinder c2 = Cylinder(height+1, 0.1, glm::vec3(0, 1, 0));
    Mesh mesh2 = c2.getMesh();
    glm::mat4 T;
    T = glm::translate(T, glm::vec3(1, 0, 0));
    mesh2.transform(T);
    ladder.joinMesh(mesh2);

    return ladder;
}

void Slide::createMesh(int height)
{
    Mesh ladderMesh = createLadderMesh(height);

    glm::mat4 T;
    T = glm::translate(glm::mat4(1.0), glm::vec3(2*height*cos(30*3.1415/180), height/2 + 0.5  + 0.5*((1&height%2)), 1));
    T = glm::rotate(T, (float)glm::radians(90.0), glm::vec3(0, 1, 0));
    ladderMesh.transform(T);

    Cube slide = Cube(2*height, 0.1, 1);
    Mesh slideMesh = slide.getMesh();

    T = glm::rotate(glm::mat4(1.0), (float)glm::radians(30.0), glm::vec3(0, 0, 1));
    slideMesh.transform(T);

    (this -> mesh).joinMesh(ladderMesh);
    (this -> mesh).joinMesh(slideMesh);


    // T = glm::translate(glm::mat4(1.0), glm::vec3(0, height/2 + 0.5  + 0.5*((1&height%2)), 0));
    // this -> mesh.transform(T);
}
