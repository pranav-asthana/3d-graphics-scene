#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;

vector<GLfloat> getColorVector(glm::vec3 color, int size);
vector<GLfloat> joinColors(vector<GLfloat> c1, vector<GLfloat> c2);

#endif
