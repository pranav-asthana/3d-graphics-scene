#ifndef CYLINDER_H
#define CYLINDER_H

#include "mesh.h"
#include <vector>

class Cylinder
{
public:
    Cylinder(float height, float radius);

    Mesh * getMesh();
private:
    Mesh * mesh;
    Mesh * createMesh(float height, float radius);
};
#endif
