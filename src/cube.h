#ifndef CUBE_H
#define CUBE_H

#include "mesh.h"
#include <vector>

class Cube
{
public:
    Cube(float width, float height, float depth);

    Mesh getMesh();
private:
    Mesh mesh;

    Mesh createMesh(float x, float y, float z);
};
#endif
