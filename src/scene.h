#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utilities.h"
#include "mesh.h"
#include "sphere.h"
#include "cube.h"
#include "cylinder.h"
#include "monkeybars.h"
#include "seesaw.h"
#include "slide.h"
#include "grass.h"

class Scene
{
public:
    /// Initialize a Scene object
    Scene();

    /// Return a Mesh vector of all elements of the scene
    vector<Mesh> getMesh();

    /// Return a vector of the color GLfloat vectors of the elements of the scene
    vector<vector<GLfloat>> getColors();


    void addCube(glm::vec3 center, glm::vec3 dimensions, glm::vec3 color_vec);
    void addSphere(glm::vec3 center, float radius, glm::vec3 color_vec, int detail_level=2);
    void addCylinder(glm::vec3 center, float height, float radius, glm::vec3 color_vec, glm::vec3 orientation);

    void addMonkeyBars(glm::vec3 position, glm::vec3 color_vec, int length, int height, glm::mat4 transformation=glm::mat4(1.0));
    void addSeeSaw(glm::vec3 position, glm::vec3 color_vec, glm::mat4 transformation=glm::mat4(1.0));
    void addSlide(glm::vec3 position, glm::vec3 color_vec, int height, glm::mat4 transformation=glm::mat4(1.0));

    void addFence(glm::vec4 bounds);
    void addFloor(glm::vec4 bounds);
    void addGrass(glm::vec2 left_bottom, glm::vec2 top_right, glm::vec3 color_vec);
    void addPath(glm::vec2 left_bottom, glm::vec2 top_right, glm::vec3 color_vec);
private:
    vector<Mesh> meshes;
    vector<vector<GLfloat>> colors;
};
#endif
