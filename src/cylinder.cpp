#include "cylinder.h"
#include <stdio.h>

#define PI 3.1415

Cylinder::Cylinder(float height, float radius, glm::vec3 orientation, int num_segments)
{
    mesh = createMesh(height, radius, orientation, num_segments);
}

Mesh Cylinder::getMesh()
{
    return mesh;
}

Mesh Cylinder::createMesh(float height, float radius, glm::vec3 orientation, int num_segments)
{
    Mesh mesh = Mesh();

    // int num_segments = 36;

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

    for (int i = 0; i < num_segments; i += 2)
    {
        mesh.addQuad(vertices[i + 0], vertices[i + 1], vertices[i + 3], vertices[i + 2]);
    }

    glm::vec3 initial_orientation = glm::vec3(0, 0, 1);
    if (initial_orientation != orientation)
    {
        glm::vec3 axis_of_rotation = glm::cross(initial_orientation, orientation);
        float angle_of_rotation = acos(glm::dot(glm::normalize(orientation), initial_orientation));

        glm::mat4 T;
        T = glm::rotate(T, angle_of_rotation, axis_of_rotation);
        mesh.transform(T);
    }

    return mesh;
}
