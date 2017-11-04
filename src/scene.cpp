#include "scene.h"

Scene::Scene()
{
}

vector<Mesh> Scene::getMesh()
{
    return meshes;
}

vector<vector<GLfloat>> Scene::getColors()
{
    return colors;
}

void Scene::addCube(glm::vec3 center, glm::vec3 dimensions, glm::vec3 color_vec)
{
    Cube * cube = new Cube(dimensions.x, dimensions.y, dimensions.z);
    Mesh * mesh = cube -> getMesh();
    int len = (mesh -> getVertices()).size();
    printf("cube mesh len: %d\n", len);

    vector<GLfloat> color_vector = getColorVector(color_vec, len);

    glm::mat4 T;
    T = glm::translate(T, center);
    T = glm::translate(T, glm::vec3(-dimensions.x/2, -dimensions.y/2, -dimensions.z/2));
    mesh -> transform(T);

    meshes.push_back(*mesh);
    colors.push_back(color_vector);

    delete cube;
    delete mesh;
}

void Scene::addSphere(glm::vec3 center, float radius, glm::vec3 color_vec, int detail_level)
{
    Sphere * sphere = new Sphere(radius, detail_level);
    Mesh * mesh  = sphere -> getMesh();
    int len = (mesh -> getVertices()).size();

    vector<GLfloat> color_vector = getColorVector(color_vec, len);

    glm::mat4 T;
    T = glm::translate(T, center);
    mesh -> transform(T);

    meshes.push_back(*mesh);
    colors.push_back(color_vector);

    delete sphere;
    delete mesh;
}

void Scene::addCylinder(glm::vec3 center, float height, float radius, glm::vec3 color_vec, glm::vec3 orientation)
{
    Cylinder * cylinder = new Cylinder(height, radius, orientation);
    Mesh * mesh = cylinder -> getMesh();
    int len = (mesh -> getVertices()).size();

    vector<GLfloat> color_vector = getColorVector(color_vec, len);

    glm::mat4 T;
    T = glm::translate(T, center);
    mesh -> transform(T);

    meshes.push_back(*mesh);
    colors.push_back(color_vector);

    delete cylinder;
    delete mesh;
}

void Scene::addMonkeyBars(glm::vec3 position, glm::vec3 color_vec, int length, int height)
{
    MonkeyBars * monkeybars = new MonkeyBars(length, height);
    Mesh * mesh = monkeybars -> getMesh();
    int len = (mesh -> getVertices()).size();

    vector<GLfloat> color_vector = getColorVector(color_vec, len);

    glm::mat4 T;
    T = glm::translate(T, position);
    mesh -> transform(T);

    meshes.push_back(*mesh);
    colors.push_back(color_vector);

    delete monkeybars;
    delete mesh;
}

void Scene::addSeeSaw(glm::vec3 position, glm::vec3 color_vec)
{
    SeeSaw * seesaw = new SeeSaw();
    Mesh * mesh = seesaw -> getMesh();
    vector<GLfloat> color_vector = seesaw -> getColors();
    // int len = (mesh -> getVertices()).size();
    //
    // vector<GLfloat> color_vector = getColorVector(color_vec, len);


    glm::mat4 T;
    T = glm::translate(T, position);
    mesh -> transform(T);

    meshes.push_back(*mesh);
    colors.push_back(color_vector);

    delete seesaw;
    delete mesh;
}
