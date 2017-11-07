#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "triangle.h"

using namespace std;

class Mesh
{
private:
    vector<GLfloat> vertices;
    vector<Triangle> triangles;
    vector<glm::vec3> normals;

    void addVertex(glm::vec3 vertex);

public:
    Mesh();


    void addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    void addQuad(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4);

    vector<GLfloat> getVertices();

    vector<Triangle> getTriangles();

    vector<glm::vec3> getNormals();

    void transform(glm::mat4 transformation);

    void joinMesh(Mesh mesh);
};

#endif
