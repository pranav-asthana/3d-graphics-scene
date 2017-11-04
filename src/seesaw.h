#ifndef SEESAW_H
#define SEESAW_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh.h"

class SeeSaw
{
public:
    SeeSaw();
    Mesh * getMesh();

private:
    Mesh * mesh;
    void createMesh();
};
#endif
