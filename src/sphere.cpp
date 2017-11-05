#include "icosahedron.h"
#include "sphere.h"

Sphere::Sphere(float radius, int detail_level)
{
    Icosahedron i = Icosahedron(radius);
    sphereMesh = fromIcosahedron(i, radius, detail_level);
}

Mesh Sphere::getMesh()
{
    return sphereMesh;
}

Mesh Sphere::fromIcosahedron(Icosahedron i, float radius, int detail_level)
{
    Mesh mesh = i.getMesh();
    Mesh sphereMesh = mesh;
    vector<Triangle> triangles;
    while (detail_level--)
    {
        triangles = sphereMesh.getTriangles();
        sphereMesh = Mesh();
        int num_triangles = triangles.size();
        for (int i = 0; i < num_triangles; i++)
        {
            Triangle t = triangles.back();
            triangles.pop_back();

            glm::vec3 v1 = glm::normalize((t.A + t.B) * 0.5f) * radius;
            glm::vec3 v2 = glm::normalize((t.B + t.C) * 0.5f) * radius;
            glm::vec3 v3 = glm::normalize((t.C + t.A) * 0.5f) * radius;

            sphereMesh.addTriangle(t.A, v1, v3);
            sphereMesh.addTriangle(t.B, v2, v1);
            sphereMesh.addTriangle(t.C, v3, v2);
            sphereMesh.addTriangle(v1, v2, v3);
        }
    }
    return sphereMesh;
}
