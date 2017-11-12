#ifndef MONKEYBARS_H
#define MONKEYBARS_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh.h"

class MonkeyBars
{
public:
    /// Create a MonkeyBars object of given length and height
    MonkeyBars(int length, int height);

    /// Return a Mesh object of the MonkeyBars
    Mesh getMesh();

private:
    Mesh mesh;
    void createMesh(int length, int height);
    Mesh createSideMesh(int size);
};
#endif
