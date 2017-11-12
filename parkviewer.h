#ifndef PARK_VIEWER_H
#define PARK_VIEWER_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "src/shader.h"
#include "src/scene.h"
#include "src/Camera.h"
#include "Constants.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SQUARE_SIDE 20
#define MIN_ALT 0.5f
#define MAX_ALT 100.0f
#define SHOW_FPS false

typedef unsigned long long ulong64_t;

using namespace glm;
using namespace std;

/// Bounds for the park in the world space of OpenGL. The fence is placed around this.

const GLfloat x_min = -SQUARE_SIDE;
const GLfloat x_max = SQUARE_SIDE;
const GLfloat y_min = MIN_ALT;
const GLfloat y_max = MAX_ALT;
const GLfloat z_min = -SQUARE_SIDE;
const GLfloat z_max = SQUARE_SIDE;

typedef pair<GLuint, GLuint> VertexColorPair;
GLFWwindow* window;

/// Callback functions used for moving the camera in the scene.

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

struct ObjectData {
    GLuint ModelArrayID, ModelVBO, ModelColorVBO, ModelNormalVBO, EBO, indexSize;
};

/// Draw an object from its VertexArrayObject (VAO) and its modification vectors.
/// Vectors for modifying the scale, translation, rotation of the object can be passed.

void drawGenericObject(GLuint &VAO, GLuint programID,
                        glm::mat4 proj,
                        glm::mat4 view,
                        int size,
                        bool elemental,
                        glm::vec3 translationVector = glm::vec3(0,0,0),
                        glm::vec3 scaleVector = glm::vec3(1,1,1),
                        GLfloat rotationAngle = 0,
                        glm::vec3 rotationAxis = glm::vec3(1,0,0));

/// Load Wavefront .obj generated in Blender. Take vectors for storing vertices,
/// indices (for EBO), and normals of the Wavefront obj

bool loadAssImp(const char * path, std::vector<unsigned short> &indices,
                std::vector<glm::vec3> &vertices,
                std::vector<glm::vec3> &normals);

/// Call intialisation functions for OpenGL to render the scene.

bool initOpenGL();

/// Sets up the VertexArrayObject for a given Mesh. As a Mesh can contain several primitives,
/// they are stored in the objectVector vector for passing on to the render loop.

void setupMeshVAO(Mesh mesh, GLfloat* color_vector, vector<ObjectData> &objectVector);

/// Attach Camera's functions to the callbacks defined previously.

void setCallBacks(GLFWwindow* window);

/// Take the path of the Wavefront .obj file and load it into the ObjectData structure.
/// This is passed on to the render loop for drawing the 3D object.

void generateModelVAO(string path, ObjectData &object, const GLfloat* color_array);

#endif
