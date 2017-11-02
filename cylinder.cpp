#include "cylinder.h"
#include <stdio.h>

#define PI 3.1415

Cylinder::Cylinder(float height, float radius)
{
    mesh = createMesh(height, radius);
}

Mesh * Cylinder::getMesh()
{
    return mesh;
}

Mesh * Cylinder::createMesh(float height, float radius)
{
    Mesh * mesh = new Mesh();

    int num_segments = 24;

    glm::vec3 vertices[num_segments*2];

    for (int i = 0; i < num_segments*2; i+=2)
    {
        double angle = ((360/num_segments)*i) * PI / 180;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        float z = height/2;
        vertices[i] = glm::vec3(x, y, -z);
        vertices[i + 1] = glm::vec3(x, y, z);
    }

        // glm::vec3(0, 0, 0),
        // glm::vec3(x, 0, 0),
        // glm::vec3(0, y, 0),
        // glm::vec3(0, 0, z),
        // glm::vec3(x, y, 0),
        // glm::vec3(0, y, z),
        // glm::vec3(x, 0, z),
        // glm::vec3(x, y, z)

    for (int i = 0; i < num_segments*2; i += 2)
    {
        mesh -> addQuad(vertices[i + 0], vertices[i + 1], vertices[i + 3], vertices[i + 2]);
    }

    // mesh -> addQuad(vertices[0], vertices[3], vertices[5], vertices[2]);
    // mesh -> addQuad(vertices[1], vertices[6], vertices[7], vertices[4]);
    // mesh -> addQuad(vertices[0], vertices[1], vertices[6], vertices[3]);
    // mesh -> addQuad(vertices[2], vertices[4], vertices[7], vertices[5]);
    // mesh -> addQuad(vertices[3], vertices[6], vertices[7], vertices[5]);

    return mesh;
}
