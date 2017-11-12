#include "icosahedron.h"
#include <stdio.h>

Icosahedron::Icosahedron(float radius)
{
    mesh = createMesh(radius);
}

Mesh Icosahedron::getMesh()
{
    return mesh;
}

Mesh Icosahedron::createMesh(float radius)
{
    Mesh mesh = Mesh();

    const float t = (1 + sqrt(5.0)) / 2.0;
    // So each side has a length of sqrt( t*t + 1.0 )
    float rScale = radius / sqrt(t*t + 1.0); // correct the radius
    glm::vec3 v[12]= {
        glm::vec3(-1, t, 0), glm::vec3(1, t, 0), glm::vec3(-1, -t, 0), glm::vec3(1, -t, 0),
        glm::vec3(0, -1, t), glm::vec3(0, 1, t), glm::vec3(0, -1, -t), glm::vec3(0, 1, -t),
        glm::vec3(t, 0, -1), glm::vec3(t, 0, 1), glm::vec3(-t, 0, -1), glm::vec3(-t, 0, 1)
    };

    for (int i = 0;i < 12; i++)
        v[i] = radius * glm::normalize(v[i]);
        // v[i] = rScale * v[i];

    mesh.addTriangle(v[0], v[11], v[5]);
    mesh.addTriangle(v[0], v[5], v[1]);
    mesh.addTriangle(v[0], v[1], v[7]);
    mesh.addTriangle(v[0], v[7], v[10]);
    mesh.addTriangle(v[0], v[10], v[11]);

    mesh.addTriangle(v[1], v[5], v[9]);
    mesh.addTriangle(v[5], v[11], v[4]);
    mesh.addTriangle(v[11], v[10], v[2]);
    mesh.addTriangle(v[10], v[7], v[6]);
    mesh.addTriangle(v[7], v[1], v[8]);

    mesh.addTriangle(v[3], v[9], v[4]);
    mesh.addTriangle(v[3], v[4], v[2]);
    mesh.addTriangle(v[3], v[2], v[6]);
    mesh.addTriangle(v[3], v[6], v[8]);
    mesh.addTriangle(v[3], v[8], v[9]);

    mesh.addTriangle(v[4], v[9], v[5]);
    mesh.addTriangle(v[2], v[4], v[11]);
    mesh.addTriangle(v[6], v[2], v[10]);
    mesh.addTriangle(v[8], v[6], v[7]);
    mesh.addTriangle(v[9], v[8], v[1]);

    return mesh;
}
