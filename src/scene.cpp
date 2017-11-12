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
    Cube cube = Cube(dimensions.x, dimensions.y, dimensions.z);
    Mesh mesh = cube.getMesh();
    int len = (mesh.getVertices()).size();

    vector<GLfloat> color_vector = getColorVector(color_vec, len*2);

    glm::mat4 T;
    T = glm::translate(T, center);
    T = glm::translate(T, glm::vec3(-dimensions.x/2, -dimensions.y/2, -dimensions.z/2));
    mesh.transform(T);

    meshes.push_back(mesh);
    colors.push_back(color_vector);
}

void Scene::addSphere(glm::vec3 center, float radius, glm::vec3 color_vec, int detail_level)
{
    Sphere sphere = Sphere(radius, detail_level);
    Mesh mesh  = sphere.getMesh();
    int len = (mesh.getVertices()).size();

    vector<GLfloat> color_vector = getColorVector(color_vec, len);

    glm::mat4 T;
    T = glm::translate(T, center);
    mesh.transform(T);

    meshes.push_back(mesh);
    colors.push_back(color_vector);
}

void Scene::addCylinder(glm::vec3 center, float height, float radius, glm::vec3 color_vec, glm::vec3 orientation)
{
    Cylinder cylinder = Cylinder(height, radius, orientation);
    Mesh mesh = cylinder.getMesh();
    int len = (mesh.getVertices()).size();

    vector<GLfloat> color_vector = getColorVector(color_vec, len);

    glm::mat4 T;
    T = glm::translate(T, center);
    mesh.transform(T);

    meshes.push_back(mesh);
    colors.push_back(color_vector);
}

void Scene::addMonkeyBars(glm::vec3 position, glm::vec3 color_vec, int length, int height, glm::mat4 transformation)
{
    MonkeyBars monkeybars = MonkeyBars(length, height);
    Mesh mesh = monkeybars.getMesh();
    int len = (mesh.getVertices()).size();

    vector<GLfloat> color_vector = getColorVector(color_vec, len);

    glm::mat4 T;
    T = glm::translate(T, position);
    mesh.transform(T*transformation);

    meshes.push_back(mesh);
    colors.push_back(color_vector);
}

void Scene::addSeeSaw(glm::vec3 position, glm::mat4 transformation)
{
    SeeSaw seesaw = SeeSaw();
    Mesh mesh = seesaw.getMesh();
    vector<GLfloat> color_vector = seesaw.getColors();

    glm::mat4 T;

    Mesh sandpit = Cube(8, 0.1, 3).getMesh();
    T = glm::translate(glm::mat4(1.0), glm::vec3(-4, -0.1, -1.5));
    sandpit.transform(T);
    vector<GLfloat> color_sandpit = getColorVector(glm::vec3(0.56, 0.50, 0.30), sandpit.getVertices().size());

    color_vector = joinColors(color_vector, color_sandpit);
    mesh.joinMesh(sandpit);

    T = glm::translate(glm::mat4(1.0), position);
    mesh.transform(T*transformation);

    meshes.push_back(mesh);
    colors.push_back(color_vector);
}

void Scene::addSlide(glm::vec3 position, glm::vec3 color_vec, int height, glm::mat4 transformation)
{
    Slide slide = Slide(height);
    Mesh mesh = slide.getMesh();
    // vector<GLfloat> color_vector = slide.getColors();
    int len = (mesh.getVertices()).size();
    vector<GLfloat> color_vector = getColorVector(color_vec, len);

    glm::mat4 T;
    T = glm::translate(T, position);
    mesh.transform(T*transformation);

    meshes.push_back(mesh);
    colors.push_back(color_vector);
}

void Scene::addFence(glm::vec4 bounds) //x-z bounds
{
    for (float i = bounds.x; i < bounds.y; i+=1.5)
    {
        addCylinder(glm::vec3(i, 2.5, bounds.z), (float) 5.0, (float) 0.5, glm::vec3((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX), glm::vec3(0, 1, 0));
        if (!(i < 2 && i > -2))
            addCylinder(glm::vec3(i, 2.5, bounds.w), (float) 5.0, (float) 0.5, glm::vec3((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX), glm::vec3(0, 1, 0));
    }

    for (float i = bounds.z; i < bounds.w; i+=1.5)
    {
        addCylinder(glm::vec3(bounds.x, 2.5, i), (float) 5.0, (float) 0.5, glm::vec3((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX), glm::vec3(0, 1, 0));
        addCylinder(glm::vec3(bounds.y, 2.5, i), (float) 5.0, (float) 0.5, glm::vec3((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX), glm::vec3(0, 1, 0));
    }
}

void Scene::addFloor(glm::vec4 bounds) //x-z bounds
{
    for (float i = bounds.x; i <= bounds.y; i+=1)
        addCylinder(glm::vec3(i, 0, bounds.z+bounds.w), (float) bounds.w-bounds.z, (float) 0.005, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0, 0, 1));

    for (float i = bounds.z; i <= bounds.w; i+=1)
        addCylinder(glm::vec3(bounds.x+bounds.y, 0, i), (float) bounds.x-bounds.y, (float) 0.005, glm::vec3(0.7, 0.7, 0.7), glm::vec3(1, 0, 0));
    addCube(glm::vec3(0, -0.1, 0), glm::vec3(bounds.y-bounds.x + 10, 0.1, bounds.w-bounds.z + 10), glm::vec3(0.41, 0.65, 0.45));
}

void Scene::addGrass(glm::vec2 left_bottom, glm::vec2 top_right, glm::vec3 color_vec)
{
    Grass grass = Grass(left_bottom, top_right);
    Mesh mesh = grass.getMesh();

    int len = (mesh.getVertices()).size();
    vector<GLfloat> color_vector = getColorVector(color_vec, len);

    // mesh.transform(transformation);

    meshes.push_back(mesh);
    colors.push_back(color_vector);
}

void Scene::addPath(glm::vec2 left_bottom, glm::vec2 top_right, glm::vec3 color_vec)
{
    for (int tiles = left_bottom.y; tiles < top_right.y; tiles++)
    {
        for (int hor = left_bottom.x; hor < top_right.x; hor++)
        {
            addCube(glm::vec3(hor+0.55, 0, tiles+0.5), glm::vec3(0.9, 0.1, 0.95), color_vec);
            addGrass(glm::vec2(hor+0, tiles), glm::vec2(hor+0.1, tiles+1), glm::vec3(0.1, 0.8, 0.1)); // LEFT
            addGrass(glm::vec2(hor+1, tiles), glm::vec2(hor+1.1, tiles+1), glm::vec3(0.1, 0.8, 0.1)); // RIGHT
            addGrass(glm::vec2(hor+0, tiles-0.05), glm::vec2(hor+1, tiles), glm::vec3(0.1, 0.8, 0.1)); // TOP
            addGrass(glm::vec2(hor+0, tiles+1), glm::vec2(hor+1, tiles+1.05), glm::vec3(0.1, 0.8, 0.1)); // BOTTOM
        }
    }
}

void Scene::addSculpture()
{
    Mesh s1 = Sphere(1, 3).getMesh();
    Mesh s2 = Sphere(0.5, 2).getMesh();
    Mesh s3 = Sphere(0.75, 1).getMesh();

    glm::mat4 T;

    T = glm::translate(glm::mat4(1.0), glm::vec3(0, 0.7, 1));
    s1.transform(T);

    T = glm::translate(glm::mat4(1.0), glm::vec3(0.2, 2.1, 1));
    s2.transform(T);

    T = glm::translate(glm::mat4(1.0), glm::vec3(-0.4, 3, 1));
    s3.transform(T);

    vector<GLfloat> c1 = getColorVector(glm::vec3(0.8, 0.8, 0.8), (s1.getVertices()).size());
    vector<GLfloat> c2 = getColorVector(glm::vec3(0.8, 0.0, 0.8), (s2.getVertices()).size());
    vector<GLfloat> c3 = getColorVector(glm::vec3(0.3, 0.8, 0.0), (s3.getVertices()).size());

    c1 = joinColors(c1, c2);
    c1 = joinColors(c1, c3);

    s1.joinMesh(s2);
    s1.joinMesh(s3);

    meshes.push_back(s1);
    colors.push_back(c1);

}
