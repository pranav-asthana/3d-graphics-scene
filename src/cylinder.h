#ifndef CYLINDER_H
#define CYLINDER_H

#include "mesh.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cylinder
{
public:
    /// Create a cylinder object with specified height, radius and orientation
    /// orientation is specified as a glm::vec3
    /// Optional argument: Number of quads that make up the cylinder surface (defualt: 36)
    Cylinder(float height, float radius, glm::vec3 orientation, int num_segments=36);

    /// Return a Mesh object of the cylinder
    Mesh getMesh();
private:
    Mesh mesh;
    Mesh createMesh(float height, float radius, glm::vec3 orientation, int num_segments);
};
#endif
