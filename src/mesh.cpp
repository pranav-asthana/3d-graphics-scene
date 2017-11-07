#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "mesh.h"
#include <stdio.h>

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

    normals.push_back(glm::cross(v1-v2, v3-v2));
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

vector<glm::vec3> Mesh::getNormals()
{
    return normals;
}

void Mesh::transform(glm::mat4 transformation)
{
    // vector<GLfloat> vertices = this->vertices;
    vector<Triangle> triangles = this->triangles;
    Mesh mesh = Mesh();
    for (int i=0; i < triangles.size(); i++)
    {
        Triangle T = triangles.at(i);
        glm::vec4 A1 = transformation * glm::vec4(T.A, 1);
        glm::vec4 B1 = transformation * glm::vec4(T.B, 1);
        glm::vec4 C1 = transformation * glm::vec4(T.C, 1);
        mesh.addTriangle(glm::vec3(A1), glm::vec3(B1), glm::vec3(C1));
    }
    this->vertices = mesh.getVertices();
    this->triangles = mesh.getTriangles();
    this->normals = mesh.getNormals();
    // Mesh mesh = Mesh();
    // Mesh mesh2 = Mesh();
    // vector<glm::vec3> v;
    // for (int i = 0, j = 1; i < vertices.size(); i+=3)
    // {
    //     glm::vec4 vertex = glm::vec4(vertices[i+0], vertices[i+1], vertices[i+2], 1.0f);
    //     vertex = transformation * vertex;
    //     mesh.addVertex(glm::vec3(vertex));
    //     v.push_back(glm::vec3(vertex));
    //     if (j++%3 == 0){
    //         mesh2.addTriangle(v.at(2), v.at(1), v.at(0));
    //         v.pop_back();
    //         v.pop_back();
    //         v.pop_back();
    //     }
    // }
    // this->triangles = mesh2.getTriangles();
    // this->vertices = mesh.getVertices();
}

void Mesh::joinMesh(Mesh mesh)
{
    vector<GLfloat> vertices2 = mesh.getVertices();
    vector<Triangle> triangles2 = mesh.getTriangles();

    vector<GLfloat> new_vertices;
    new_vertices.reserve(vertices.size() + vertices2.size());
    new_vertices.insert(new_vertices.end(), vertices.begin(), vertices.end());
    new_vertices.insert(new_vertices.end(), vertices2.begin(), vertices2.end());

    vector<Triangle> new_triangles;
    new_triangles.reserve(triangles.size() + triangles2.size());
    new_triangles.insert(new_triangles.end(), triangles.begin(), triangles.end());
    new_triangles.insert(new_triangles.end(), triangles2.begin(), triangles2.end());

    vertices = new_vertices;
    triangles = new_triangles;
}
