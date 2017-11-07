#include "grass.h"

Grass::Grass(glm::vec2 left_bottom, glm::vec2 top_right)
{
    for (float i = left_bottom.x; i < top_right.x; i += 0.04)
    {
        for (float j = left_bottom.y; j < top_right.y; j += 0.04)
        {
            float x = (float)rand()/(float)RAND_MAX;
            float y = 1;
            float z = (float)rand()/(float)RAND_MAX;
            glm::vec3 orientation(x, y, z);
            Cylinder strand = Cylinder(0.1+0.2*x, 0.005, orientation, 4);
            Mesh mesh = strand.getMesh();

            glm::mat4 T;
            T = glm::translate(T, glm::vec3(i, 0, j));

            mesh.transform(T);

            grass.joinMesh(mesh);
        }
    }
}

Mesh Grass::getMesh()
{
    return grass;
}
