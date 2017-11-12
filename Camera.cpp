#include "Camera.h"

Camera::Camera(int screenHeight, int screenWidth)
{
    lastX = screenWidth/2.0f;
    lastY = screenHeight/2.0f;
    firstMouse = true;
    yaw = -90.0f;
    pitch =  0.0f;
    MAX_FOV = 90;
    fov = MAX_FOV;
    cameraPos = glm::vec3(0.0f, 2.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    this->x_min = -100;
    this->x_max = 100;
    this->y_min = -100;
    this->y_max = 100;
    this->z_min = -100;
    this->z_max = 100;
}

Camera::Camera(int screenHeight, int screenWidth, GLfloat x_min, GLfloat x_max, GLfloat y_min, GLfloat y_max, GLfloat z_min, GLfloat z_max)
{
    lastX = screenWidth/2.0f;
    lastY = screenHeight/2.0f;
    firstMouse = true;
    yaw = -90.0f;
    pitch =  0.0f;
    MAX_FOV = 90;
    fov = MAX_FOV;
    cameraPos = glm::vec3(x_min, y_max, z_min);
    cameraPos = glm::vec3(0, y_min+3, z_max+5);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    this->x_min = x_min;
    this->x_max = x_max;
    this->y_min = y_min;
    this->y_max = y_max;
    this->z_min = z_min;
    this->z_max = z_max;
}

glm::mat4 Camera::getCameraView()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::vec3 Camera::getCameraPosition()
{
    return cameraPos;
}

float Camera::getFOV()
{
    return fov;
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= MAX_FOV)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= MAX_FOV)
        fov = MAX_FOV;
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void Camera::processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 5.0 * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    // if (cameraPos.x < x_min)
    //     cameraPos.x = x_min;
    // if (cameraPos.x > x_max)
    //     cameraPos.x = x_max;
    if (cameraPos.y < y_min)
        cameraPos.y = y_min;
    if (cameraPos.y > y_max)
        cameraPos.y = y_max;
    // if (cameraPos.z < z_min)
    //     cameraPos.z = z_min;
    // if (cameraPos.z > z_max)
    //     cameraPos.z = z_max;
}
