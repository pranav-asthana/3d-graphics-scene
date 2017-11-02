#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "mesh.h"

Mesh::Mesh()
{
}

void Mesh::addVertex(glm::vec3 vertex)
{
    vertices.push_back(vertex.x);
    vertices.push_back(vertex.y);
    vertices.push_back(vertex.z);
}


void Mesh::addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
    triangles.push_back(Triangle(v1, v2, v3));
    addVertex(v1);
    addVertex(v2);
    addVertex(v3);
}

void Mesh::addQuad(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4)
{
    triangles.push_back(Triangle(v1, v2, v3));
    triangles.push_back(Triangle(v1, v3, v4));
    addTriangle(v1, v2, v3);
    addTriangle(v1, v3, v4);
}

vector<GLfloat> Mesh::getVertices()
{
    return vertices;
}

vector<Triangle> Mesh::getTriangles()
{
    return triangles;
}
