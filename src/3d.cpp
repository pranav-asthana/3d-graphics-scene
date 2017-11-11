#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <tuple>
#include <unistd.h>
#include <math.h>
#include "scene.h"
#include "grass.h"

#define PI 3.14159265
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BOUND_X1 -20.0
#define BOUND_X2  20.0
#define BOUND_Y1  0.0
#define BOUND_Y2  10.0
#define BOUND_Z1 -20.0
#define BOUND_Z2  20.0

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

glm::vec3 cameraPos   = glm::vec3(0.0f, 1.0f,  6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    if (cameraPos.y < 0.5)
        cameraPos.y = 0.5;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cameraPos.y += (yoffset/2);
    // cameraPos = glm::normalize(cameraPos);
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    if (cameraPos.x < BOUND_X1)
        cameraPos.x = BOUND_X1;
    if (cameraPos.x > BOUND_X2)
        cameraPos.x = BOUND_X2;
    if (cameraPos.y < BOUND_Y1)
        cameraPos.y = BOUND_Y1;
    if (cameraPos.y > BOUND_Y2)
        cameraPos.y = BOUND_Y2;
    if (cameraPos.z < BOUND_Z1)
        cameraPos.z = BOUND_Z1;
    if (cameraPos.z > BOUND_Z2)
        cameraPos.z = BOUND_Z2;
}

void renderMesh(Mesh * mesh, GLfloat * color_vector)
{
    vector<GLfloat> v = mesh -> getVertices();

    int len = v.size();
    GLfloat * vertices = &v[0];

    glColorPointer(3, GL_FLOAT, 0, color_vector);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, len/3);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

glm::mat4 updateView()
{
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}

int main()
{
    GLFWwindow *window;
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "IS F311 Computer Graphics Assignment", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context
    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective((float)fov, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    glm::mat4 view;
    Scene scene = Scene();

    glm::mat4 T;
    T = glm::rotate(glm::mat4(1.0), (float)glm::radians(150.0), glm::vec3(0, 1, 0));

    scene.addMonkeyBars(glm::vec3(-10, 0, 0), glm::vec3(0.5, 1, 0.5), 7, 3);
    scene.addSeeSaw(glm::vec3(10, 0, 0), glm::vec3(0.2, 0.2, 0.7));
    scene.addSlide(glm::vec3(-4, 0, -10), glm::vec3(0.7, 0, 0), 3, T);
    scene.addFence(glm::vec4(BOUND_X1, BOUND_X2, BOUND_Z1, BOUND_Z2));
    scene.addFloor(glm::vec4(BOUND_X1, BOUND_X2, BOUND_Z1, BOUND_Z2));

    scene.addPath(glm::vec2(-1, 0), glm::vec2(1, 19), glm::vec3(0.2, 0.2, 0.2));
    scene.addPath(glm::vec2(-19, 0), glm::vec2(19, 2), glm::vec3(0.2, 0.2, 0.2));


    // for (int tiles = 0; tiles < 10; tiles++)
    // {
    //     scene.addCube(glm::vec3(0.55, 0, tiles+0.5), glm::vec3(0.9, 0.1, 0.95), glm::vec3(0.2, 0.2, 0.2));
    //     scene.addGrass(glm::vec2(0, tiles), glm::vec2(0.1, tiles+1), glm::vec3(0, 1, 0)); // LEFT
    //     scene.addGrass(glm::vec2(1, tiles), glm::vec2(1.1, tiles+1), glm::vec3(0, 1, 0)); // RIGHT
    //     scene.addGrass(glm::vec2(0, tiles-0.05), glm::vec2(1, tiles), glm::vec3(0, 1, 0)); // TOP
    //     // scene.addGrass(glm::vec2(1, tiles), glm::vec2(1.1, tiles+1), glm::vec3(0, 1, 0)); // BOTTOM
    // }

    vector<Mesh> mesh_group = scene.getMesh();
    vector<vector<GLfloat>> color_vector_group = scene.getColors();

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        cout << "FPS: " << 1.0f/deltaTime << endl;

        view = updateView();

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the scene
        for (int i = 0; i < mesh_group.size(); i++)
        {
            Mesh mesh = mesh_group.at(i);
            GLfloat * color_vector = &color_vector_group.at(i)[0];
            mesh.transform(view);
            renderMesh(&mesh, color_vector);
        }

        // Grass grass = Grass(glm::vec2(0, 0), glm::vec2(1, 1));
        // Mesh grassMesh = grass.getMesh();
        // vector<GLfloat> grass_color_vector = getColorVector(glm::vec3(0, 1, 0), grassMesh.getVertices().size());
        // grassMesh.transform(view);
        // renderMesh(&grassMesh, &grass_color_vector[0]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
