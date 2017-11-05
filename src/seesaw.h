#ifndef SEESAW_H
#define SEESAW_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "utilities.h"
#include "mesh.h"

class SeeSaw
{
public:
    SeeSaw();
    Mesh * getMesh();
    vector<GLfloat> getColors();

private:
    Mesh * mesh;
    vector<GLfloat> colors;
    Mesh * getHandle();
    void createShaft();
    void createBase();
    void createMesh();
};
#endif
