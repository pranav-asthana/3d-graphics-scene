/** @file */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;

/// Generate a GLfloat vector of specified color and size
vector<GLfloat> getColorVector(glm::vec3 color, int size);

/// Join (concatenate) 2 color vectors and return the result
vector<GLfloat> joinColors(vector<GLfloat> c1, vector<GLfloat> c2);

#endif
