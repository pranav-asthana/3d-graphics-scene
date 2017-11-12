#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H

#include "mesh.h"
#include <vector>

class Icosahedron
{
public:
    /// Create an Icosahedron object of given radius
    Icosahedron(float radius);

    /// Return a Mesh object of the Icosahedron
    Mesh getMesh();
private:
    Mesh mesh;

    Mesh createMesh(float radius);
};
#endif
