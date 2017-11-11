#ifndef SLIDE_H
#define SLIDE_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh.h"

class Slide
{
public:
    /// Create a slide object of given height
    Slide(int height);

    /// Return a Mesh object of the Slide
    Mesh getMesh();

private:
    Mesh mesh;
    void createMesh(int height);
    Mesh createLadderMesh(int height);
};
#endif
