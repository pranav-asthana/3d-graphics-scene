#include "scene.h"

Scene::Scene()
{
}

vector<tuple<Mesh, glm::vec3>> Scene::getMesh()
{
    return meshes;
}

void Scene::addCube(glm::vec3 center, glm::vec3 dimensions, glm::vec3 color_vec)
{
    Cube * cube = new Cube(dimensions.x, dimensions.y, dimensions.z);
    Mesh * mesh = cube -> getMesh();

    glm::mat4 T;
    T = glm::translate(T, center);
    T = glm::translate(T, glm::vec3(-dimensions.x/2, -dimensions.y/2, -dimensions.z/2));
    mesh -> transform(T);

    meshes.push_back(make_tuple(*mesh, color_vec));

    delete cube;
    delete mesh;
}
void Scene::addSphere(glm::vec3 center, float radius, glm::vec3 color_vec, int detail_level)
{
    Sphere * sphere = new Sphere(radius, detail_level);
    Mesh * mesh  = sphere -> getMesh();

    glm::mat4 T;
    T = glm::translate(T, center);
    mesh -> transform(T);

    meshes.push_back(make_tuple(*mesh, color_vec));

    delete sphere;
    delete mesh;
}

void Scene::addCylinder(glm::vec3 center, float height, float radius, glm::vec3 color_vec, glm::vec3 orientation)
{
    Cylinder * cylinder = new Cylinder(height, radius, orientation);

    glm::mat4 T;
    T = glm::translate(T, center);

    Mesh * mesh = cylinder -> getMesh();
    mesh -> transform(T);

    meshes.push_back(make_tuple(*mesh, color_vec));

    delete cylinder;
    delete mesh;
}

void Scene::addMonkeyBars(glm::vec3 position, glm::vec3 color_vec, int length, int height)
{
    MonkeyBars * monkeybars = new MonkeyBars(length, height);
    Mesh * mesh = monkeybars -> getMesh();

    glm::mat4 T;
    T = glm::translate(T, position);
    mesh -> transform(T);

    meshes.push_back(make_tuple(*mesh, color_vec));

    delete monkeybars;
    delete mesh;
}
