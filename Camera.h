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

    GLfloat x_min;
    GLfloat x_max;
    GLfloat y_min;
    GLfloat y_max;
    GLfloat z_min;
    GLfloat z_max;

    bool firstMouse;

public:
    Camera(int screenHeight, int screenWidth);
    Camera(int screenHeight, int screenWidth, GLfloat x_min, GLfloat x_max, GLfloat y_min,
            GLfloat y_max, GLfloat z_min, GLfloat z_max);
    glm::mat4 getCameraView();
    glm::vec3 getCameraPosition();
    float getFOV();
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void processInput(GLFWwindow *window, float deltaTime);
};
#endif
