#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H

#include "mesh.h"
#include <vector>

class Icosahedron
{
public:
    Icosahedron(float radius);

    Mesh getMesh();
private:
    Mesh mesh;

    Mesh createMesh(float radius);
};
#endif
