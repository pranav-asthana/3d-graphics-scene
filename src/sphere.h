#ifndef SPHERE_H
#define SPHERE_H

#include "icosahedron.h"

class Sphere
{
public:
    Sphere(float radius, int detail_level);
    Mesh * getMesh();
private:
    Mesh * sphereMesh;
    Mesh * fromIcosahedron(Icosahedron * i, float radius, int detail_level);
};
#endif
