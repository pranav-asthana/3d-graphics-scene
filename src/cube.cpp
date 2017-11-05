#include "cube.h"
#include <stdio.h>

Cube::Cube(float width, float height, float depth)
{
    mesh = createMesh(width, height, depth);
}

Mesh Cube::getMesh()
{
    return mesh;
}

Mesh Cube::createMesh(float x, float y, float z)
{
    Mesh mesh = Mesh();

    glm::vec3 vertices[8] = {
        glm::vec3(0, 0, 0),
        glm::vec3(x, 0, 0),
        glm::vec3(0, y, 0),
        glm::vec3(0, 0, z),
        glm::vec3(x, y, 0),
        glm::vec3(0, y, z),
        glm::vec3(x, 0, z),
        glm::vec3(x, y, z)
    };

    mesh.addQuad(vertices[0], vertices[1], vertices[4], vertices[2]);
    mesh.addQuad(vertices[0], vertices[3], vertices[5], vertices[2]);
    mesh.addQuad(vertices[1], vertices[6], vertices[7], vertices[4]);
    mesh.addQuad(vertices[0], vertices[1], vertices[6], vertices[3]);
    mesh.addQuad(vertices[2], vertices[4], vertices[7], vertices[5]);
    mesh.addQuad(vertices[3], vertices[6], vertices[7], vertices[5]);

    return mesh;
}
