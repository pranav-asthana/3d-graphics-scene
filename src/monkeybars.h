#ifndef MONKEYBARS_H
#define MONKEYBARS_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh.h"

class MonkeyBars
{
public:
    MonkeyBars(int length, int height);
    Mesh getMesh();

private:
    Mesh mesh;
    void createMesh(int length, int height);
    Mesh createSideMesh(int size);
};
#endif
