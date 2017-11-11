#ifndef CUBE_H
#define CUBE_H

#include "mesh.h"
#include <vector>

class Cube
{
public:
    /// Create a cube object with specified width, height and depth
    Cube(float width, float height, float depth);

    /// Return a Mesh object of the cube
    Mesh getMesh();
private:
    Mesh mesh;

    Mesh createMesh(float x, float y, float z);
};
#endif
