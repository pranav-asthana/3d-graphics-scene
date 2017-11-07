#ifndef GRASS_H
#define GRASS_H

#include <glm/glm.hpp>
#include <vector>
#include "cylinder.h"

class Grass
{
public:
    Grass(glm::vec2 left_bottom, glm::vec2 top_right); // For rectangular patch
    Mesh getMesh();
private:
    Mesh grass;
};
#endif
