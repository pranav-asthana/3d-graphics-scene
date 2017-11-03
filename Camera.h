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
    glm::vec3 cameraPositionVector;
    glm::vec3 cameraDirectionVector;
    glm::vec3 cameraUpVector;

    float yaw;
    float pitch;
    float fov;
    float lastX;
    float lastY;
    const float MAX_FOV;
};
