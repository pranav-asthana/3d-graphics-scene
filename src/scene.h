#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh.h"
#include "sphere.h"
#include "cube.h"
#include "cylinder.h"
#include "monkeybars.h"

class Scene
{
public:
    Scene();
    vector<tuple<Mesh, glm::vec3>> getMesh();

    void addCube(glm::vec3 center, glm::vec3 dimensions, glm::vec3 color_vec);
    void addSphere(glm::vec3 center, float radius, glm::vec3 color_vec, int detail_level=2);
    void addCylinder(glm::vec3 center, float height, float radius, glm::vec3 color_vec, glm::vec3 orientation);

    void addMonkeyBars(glm::vec3 position, glm::vec3 color_vec, int length, int height);
private:
    vector<tuple<Mesh, glm::vec3>> meshes;
};
#endif
