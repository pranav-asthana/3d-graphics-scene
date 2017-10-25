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

#define PI 3.14159265
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void drawCube(GLfloat vertices[])
{
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat red = 1;
    GLfloat green = 1;
    GLfloat blue = 1;
    GLfloat color_vector[] = {red, green, blue, 1};

    glColorPointer(4, GL_FLOAT, 0, color_vector);


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4*6);
    glDisableClientState(GL_COLOR_ARRAY);
    // glVertexPointer(3, GL_FLOAT, 0, vertices_points);
    // glDrawArrays(GL_LINES, 0, 8*6);
    glDisableClientState(GL_VERTEX_ARRAY);
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
        printf("%f %f %f\n", vertices[i], vertices[i+1], vertices[i+2]);
    }
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

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat vertices_triangles[] = {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
        };

    GLfloat vertices_points[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
       -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };


    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

    int i = 0;
    while (!glfwWindowShouldClose(window)) {

        GLfloat vertices[] = {
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

        glm::mat4 view;
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));

        // updateVertices(vertices, projection, 4*6*3);
        // updateVertices(vertices, view, 4*6*3);
        //
        // for (unsigned int i = 0; i < 10; i++)
        // {
        //     // calculate the model matrix for each object and pass it to shader before drawing
        //     glm::mat4 model;
        //     model = glm::translate(model, cubePositions[i]);
        //     float angle = 20.0f * i;
        //     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //     updateVertices(vertices, model, 4*6*3);
        //     drawCube(vertices);
        // }

        glm::mat4 t;
        i += 1;
        t = glm::rotate(t, (float)((3.1415+i)/180), glm::vec3(1.f, 0.5f, 0.0f));
        updateVertices(vertices, t, 4*6*3);
        drawCube(vertices);
        usleep(1e4);
        // sleep(1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
