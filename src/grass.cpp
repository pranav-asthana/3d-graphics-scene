#include "grass.h"

Grass::Grass(glm::vec2 left_bottom, glm::vec2 top_right)
{
    Mesh texture = Mesh();
    for (float i = 0; i < 0.1; i += 0.03)
    {
        for (float j = 0; j < 0.1; j += 0.03)
        {
            float x = (float)rand()/(float)RAND_MAX;
            float y = 1;
            float z = (float)rand()/(float)RAND_MAX;
            glm::vec3 orientation(x, y, z);
            float height = 0.1;//+0.1*(x+y);
            Cylinder strand = Cylinder(height, 0.003, orientation, 8);
            Mesh mesh = strand.getMesh();

            glm::mat4 T;
            T = glm::translate(T, glm::vec3(i, height/2, j));

            mesh.transform(T);

            texture.joinMesh(mesh);
        }
    }

    for (float i = left_bottom.x; i < top_right.x; i += 0.1)
    {
        for (float j = left_bottom.y; j < top_right.y; j += 0.1)
        {
            Mesh new_tex = texture;

            glm::mat4 T;
            T = glm::translate(T, glm::vec3(i, 0, j));

            new_tex.transform(T);

            grass.joinMesh(new_tex);
        }
    }
}

Mesh Grass::getMesh()
{
    return grass;
}
