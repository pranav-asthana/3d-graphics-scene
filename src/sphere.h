#ifndef SPHERE_H
#define SPHERE_H

#include "icosahedron.h"

class Sphere
{
public:
    /// Create a sphere of given radius.
    /// Optional argument: Level of recursion to go while generating vertices from Icosahedron
    Sphere(float radius, int detail_level);

    /// Return a Mesh object of the Sphere
    Mesh getMesh();
private:
    Mesh sphereMesh;
    Mesh fromIcosahedron(Icosahedron i, float radius, int detail_level);
};
#endif
