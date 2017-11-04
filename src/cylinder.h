#ifndef CYLINDER_H
#define CYLINDER_H

#include "mesh.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cylinder
{
public:
    Cylinder(float height, float radius, glm::vec3 orientation);

    Mesh * getMesh();
private:
    Mesh * mesh;
    Mesh * createMesh(float height, float radius, glm::vec3 orientation);
};
#endif
