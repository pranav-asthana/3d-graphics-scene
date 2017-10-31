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

void updateVertices(GLfloat vertices[], glm::mat4 M, int size)
{
    for (int i = 0; i < size; i += 3)
    {
        glm::vec4 myVec(vertices[i], vertices[i+1], vertices[i+2], 1.0f);
        glm::vec4 newVec = M * myVec;
        vertices[i] = newVec[0];
        vertices[i+1] = newVec[1];
        vertices[i+2] = newVec[2];
        // printf("%f %f %f\n", vertices[i], vertices[i+1], vertices[i+2]);
    }
    // printf("-----------\n");
}

void drawCube(glm::vec3 center, glm::vec3 dimensions, glm::vec3 color_vec, glm::mat4 transformation = glm::mat4(1.0f)) // pass vertices as quads
{

    GLfloat vertices[6*4*3];
    glm::vec3 vertices2[] = {
        center,
        center + glm::vec3(dimensions.x, 0, 0),
        center + glm::vec3(dimensions.x, dimensions.y, 0),
        center + glm::vec3(0, dimensions.y, 0),

        center,
        center + glm::vec3(0, 0, dimensions.z),
        center + glm::vec3(0, dimensions.y, dimensions.z),
        center + glm::vec3(0, dimensions.y, 0),

        center + glm::vec3(dimensions.x, 0, 0),
        center + glm::vec3(dimensions.x, 0, dimensions.z),
        center + glm::vec3(dimensions.x, dimensions.y, dimensions.z),
        center + glm::vec3(dimensions.x, dimensions.y, 0),

        center,
        center + glm::vec3(dimensions.x, 0, 0),
        center + glm::vec3(dimensions.x, 0, dimensions.z),
        center + glm::vec3(0, 0, dimensions.z),

        center + glm::vec3(0, dimensions.y, 0),
        center + glm::vec3(dimensions.x, dimensions.y, 0),
        center + glm::vec3(dimensions.x, dimensions.y, dimensions.z),
        center + glm::vec3(0, dimensions.y, dimensions.z),

        center + glm::vec3(0, 0, dimensions.z),
        center + glm::vec3(dimensions.x, 0, dimensions.z),
        center + glm::vec3(dimensions.x, dimensions.y, dimensions.z),
        center + glm::vec3(0, dimensions.y, dimensions.z)
    };

    for (int i = 0; i<6*4*3; i+=3)
    {
        int j = (int) i/3;
        vertices[i+0] = vertices2[j].x;
        vertices[i+1] = vertices2[j].y;
        vertices[i+2] = vertices2[j].z;
    }

    glm::mat4 T;
    T = glm::translate(T, glm::vec3(-dimensions.x/2, -dimensions.y/2, -dimensions.z/2));
    updateVertices(vertices, transformation*T, 6*4*3);

    GLfloat color[] = {color_vec.x, color_vec.y, color_vec.z};
    GLfloat color_vector[32*3];
    for (int i = 0; i < 32*3;)
    {
        for (int j = 0; j < 3; j++)
        {
            color_vector[i++] = color[j];
        }
    }

    glColorPointer(3, GL_FLOAT, 0, color_vector);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4*6);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawCylinder()
{}

void drawSphere(glm::mat4 transformation)
{
    GLfloat t = (1.0 + sqrt(5.0)) / 2.0;
    GLfloat vdata[12][3] = {
        {-1, t, 0}, {1, t, 0}, {-1, -t, 0}, {1, -t, 0},
        {0, -1, t}, {0, 1, t}, {0, -1, -t}, {0, 1, -t},
        {t, 0, -1}, {t, 0, 1}, {-t, 0, -1}, {-t, 0, 1}
    };

    int num_triangles = 20;

    GLuint tindices[num_triangles][3] = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };

    glm::vec3 faces[num_triangles][3];
    for (int i = 0; i < num_triangles; i++)
    {
         glm::vec3 a = glm::vec3(vdata[tindices[i][0]][0], vdata[tindices[i][0]][1], vdata[tindices[i][0]][2]);
         glm::vec3 b = glm::vec3(vdata[tindices[i][1]][0], vdata[tindices[i][1]][1], vdata[tindices[i][1]][2]);
         glm::vec3 c = glm::vec3(vdata[tindices[i][2]][0], vdata[tindices[i][2]][1], vdata[tindices[i][2]][2]);
         faces[i][0] = a;
         faces[i][1] = b;
         faces[i][2] = c;
    }

    int max_depth = 1;
    int new_num_triangles = num_triangles * (int) pow(4, max_depth);
    glm::vec3 new_faces[new_num_triangles][3];
    for (int depth = 0; depth < max_depth; depth++)
    {
        for (int face = 0; face < new_num_triangles; face+=4)
        {
            glm::vec3 v1 = faces[face/4][0];//glm::vec3(vdata[tindices[face][0]][0], vdata[tindices[face][0]][1], vdata[tindices[face][0]][2]);
            glm::vec3 v2 = faces[face/4][1];//glm::vec3(vdata[tindices[face][1]][0], vdata[tindices[face][1]][1], vdata[tindices[face][1]][2]);
            glm::vec3 v3 = faces[face/4][2];//glm::vec3(vdata[tindices[face][2]][0], vdata[tindices[face][2]][1], vdata[tindices[face][2]][2]);

            glm::vec3 a = (v2 + v1) * 0.5f;
            glm::vec3 b = (v3 + v2) * 0.5f;
            glm::vec3 c = (v1 + v3) * 0.5f;

            glm::vec3 vertex_data[4][3] = {
                {v1, a, c}, {v2, b, a}, {v3, c, b}, {a, b, c}
            };

            for(int j = 0; j < 4; j++)
            {
                printf("Adding face %d\n", face+j);
                new_faces[face+j][0] = vertex_data[j][0];
                new_faces[face+j][1] = vertex_data[j][1];
                new_faces[face+j][2] = vertex_data[j][2];
            }
        }
    }
    num_triangles = new_num_triangles;
    GLfloat vertices[num_triangles*3*3];

    for (int i = 0, j = 0; j < num_triangles; j++)
    {
        printf("getting triangle %d(%d, %d, %d)\n", j, tindices[j][0], tindices[j][1], tindices[j][2]);
        vertices[i++] = new_faces[j][0].x;
        vertices[i++] = new_faces[j][0].y;
        vertices[i++] = new_faces[j][0].z;

        vertices[i++] = new_faces[j][1].x;
        vertices[i++] = new_faces[j][1].y;
        vertices[i++] = new_faces[j][1].z;

        vertices[i++] = new_faces[j][2].x;
        vertices[i++] = new_faces[j][2].y;
        vertices[i++] = new_faces[j][2].z;
    }

    updateVertices(vertices, transformation, num_triangles*3*3);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    GLfloat color_vector[] = {1, 0, 0};
    glColorPointer(3, GL_FLOAT, 0, color_vector);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, num_triangles*3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

}


glm::mat4 updateView()
{
    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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

    glEnable(GL_DEPTH_TEST);
    gluPerspective((float)fov, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100.0f);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glm::vec3 cubePositions[] = {
        glm::vec3( 2.0f,  0.0f, -0.0f),
        glm::vec3( 2.0f,  0.0f, -5.0f),
        glm::vec3( 2.0f,  0.0f, -10.0f),
        glm::vec3( 2.0f,  0.0f, -15.0f),
        glm::vec3( 2.0f,  0.0f, -20.0f),
        glm::vec3(-2.0f,  0.0f, 0.0f),
        glm::vec3(-2.0f,  0.0f, -5.0f),
        glm::vec3(-2.0f,  0.0f, -10.0f),
        glm::vec3(-2.0f,  0.0f, -15.0f),
        glm::vec3(-2.0f,  0.0f, -20.0f),
    };

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::mat4 view = updateView();
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // DRAW WALLS
        // Left
        drawCube(glm::vec3(BOUND_X1-1, 0, 0), glm::vec3(1, (BOUND_Y2+BOUND_Y1+1)*2, (BOUND_Z2-BOUND_Z1+2)), glm::vec3(0, 0, 1), view);
        // Right
        drawCube(glm::vec3(BOUND_X2+1, 0, 0), glm::vec3(1, (BOUND_Y2+BOUND_Y1+1)*2, (BOUND_Z2-BOUND_Z1+2)), glm::vec3(0, 1, 0), view);
        // Bottom
        drawCube(glm::vec3(0, BOUND_Y1-1, 0), glm::vec3((BOUND_X2-BOUND_X1+2), 1, (BOUND_Z2-BOUND_Z1+2)), glm::vec3(0, 1, 1), view);
        // Top
        drawCube(glm::vec3(0, BOUND_Y2+1, 0), glm::vec3((BOUND_X2-BOUND_X1+2), 1, (BOUND_Z2-BOUND_Z1+2)), glm::vec3(1, 0, 1), view);
        // Back
        drawCube(glm::vec3(0, 0, BOUND_Z1-1), glm::vec3((BOUND_X2-BOUND_X1+2), (BOUND_Y2+BOUND_Y1+1)*2, 1), glm::vec3(0.5, 0.5, 1), view);
        //Front
        drawCube(glm::vec3(0, 0, BOUND_Z2+1), glm::vec3((BOUND_X2-BOUND_X1+2), (BOUND_Y2+BOUND_Y1+1)*2, 1), glm::vec3(0, 0, 0.5), view);

        // drawSphere(view);

        for (unsigned int i = 0; i < 10; i++)
        {
            drawCube(cubePositions[i], glm::vec3(2 ,2, 1), glm::vec3(1, 0, 0), view);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
