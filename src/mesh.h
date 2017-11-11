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
    /// Initialize an empty Mesh object
    Mesh();

    /// Add a triangle to the mesh with given vertices
    void addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    /// Add a quadrilateral to the mesh with given vertices
    void addQuad(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4);

    /// Return a GLfloat vector of vertices of the mesh as x, y, z
    vector<GLfloat> getVertices();

    /// Return a Triangle vector of traingles of the mesh
    vector<Triangle> getTriangles();

    /// Return a vec3 vector of normals to each triangle of the mesh
    vector<glm::vec3> getNormals();

    /// Apply a transformation matrix to the mesh
    void transform(glm::mat4 transformation);

    /// Concatenate a Mesh to the calling Mesh
    void joinMesh(Mesh mesh);
};

#endif
