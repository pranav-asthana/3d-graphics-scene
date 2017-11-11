/** @file */
#ifndef CAMERA_H
#define CAMERA_H

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

class Camera {
private:
    /// We store the camera's position and direction vectors in vec3, this defines
    /// the camera's location in the scene. Camera up is used for computing the cross
    /// product to find all its vectors.

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float yaw;
    float pitch;
    float fov;
    float lastX;
    float lastY;
    float MAX_FOV;
    float cameraSpeed;

    /// Bounds for the scene so we can specify how far the camera can move.

    GLfloat x_min;
    GLfloat x_max;
    GLfloat y_min;
    GLfloat y_max;
    GLfloat z_min;
    GLfloat z_max;

    bool firstMouse;

public:
    /// Default constructor, intiliasing with default values for the camera's bounds
    Camera(int screenHeight, int screenWidth);

    Camera(int screenHeight, int screenWidth, GLfloat x_min, GLfloat x_max, GLfloat y_min,
            GLfloat y_max, GLfloat z_min, GLfloat z_max);

    /// Some functions in the 3dviewer code require the view from the camera's FOV to
    /// decide how much to render.

    glm::mat4 getCameraView();
    glm::vec3 getCameraPosition();
    float getFOV();

    /// Callbacks are triggered through OpenGL and call the camera's callback functions
    /// to reposition the camera and redraw the scene.

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void processInput(GLFWwindow *window, float deltaTime);
};
#endif
