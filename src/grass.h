/** @file */
#ifndef GRASS_H
#define GRASS_H

#include <glm/glm.hpp>
#include <vector>
#include "cylinder.h"

class Grass
{
public:
    /// Create a Grass object in a rectangular patch with given endpoints
    Grass(glm::vec2 left_bottom, glm::vec2 top_right); // For rectangular patch

    /// Return a Mesh object of the Grass
    Mesh getMesh();
private:
    Mesh grass;
};
#endif
