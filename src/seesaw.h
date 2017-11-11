#ifndef SEESAW_H
#define SEESAW_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "utilities.h"
#include "mesh.h"

class SeeSaw
{
public:
    /// Create a SeeSaw object
    SeeSaw();

    /// Return a Mesh object of the SeeSaw
    Mesh getMesh();

    /// Return GLfloat vector of colors of each vertex for the SeeSaw
    vector<GLfloat> getColors();

private:
    Mesh mesh;
    vector<GLfloat> colors;
    Mesh getHandle();
    void createShaft();
    void createBase();
    void createMesh();
};
#endif
