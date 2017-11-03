#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
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
#define WIDTH 1280
#define HEIGHT 720
#define BOUND_X1 -20.0
#define BOUND_X2  20.0
#define BOUND_Y1  0.0
#define BOUND_Y2  10.0
#define BOUND_Z1 -20.0
#define BOUND_Z2  20.0

const char* vertex_shader =
    "attribute vec3 aCoords;"
    "attribute vec3 aColor;"
    "uniform mat4 umvMat;"
    "uniform mat4 upMat;"
    "varying vec3 vColor;"
    "void main () {"
        "gl_Position = upMat * umvMat * vec4(aCoords, 1.0);"
        "vColor = aColor;"
    "}";

const char* fragment_shader =
    "varying vec3 vColor;"
    "void main () {"
        "gl_FragColor = vec4 (vColor, 1.0);"
    "}";

GLuint VERTEX_ATTR_COORDS = 1;
GLuint VERTEX_ATTR_COLOR = 2;

// void initShaders()
// {
//     GLuint vs = glCreateShader (GL_VERTEX_SHADER);
//     glShaderSource (vs, 1, &vertex_shader, NULL);
//     glCompileShader (vs);
//
//     GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
//     glShaderSource (fs, 1, &fragment_shader, NULL);
//     glCompileShader (fs);
//
//     auto program = glCreateProgram();
//     glAttachShader (program, fs);
//     glAttachShader (program, vs);
//
//     glBindAttribLocation(program, VERTEX_ATTR_COORDS, "aCoords");
//     glBindAttribLocation(program, VERTEX_ATTR_COLOR, "aColor");
//
//     glLinkProgram (program);
//
//     glUseProgram (program);
// }

char* filetobuf(char *file)
{
    FILE *fptr;
    long length;
    char *buf;

    fptr = fopen(file, "rb"); /* Open file for reading */
    if (!fptr) /* Return NULL on failure */
        return NULL;
    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
    fclose(fptr); /* Close the file */
    buf[length] = 0; /* Null terminator */

    return buf; /* Return the buffer */
}

int main()
{
    // GLFWwindow *window;
    // if (!glfwInit()) {
    //     return -1;
    // }
    // window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "X", NULL, NULL);
    // if (!window) {
    //     glfwTerminate();
    //     return -1;
    // }
    // glfwMakeContextCurrent(window);
    // glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    // glEnable(GL_DEPTH_TEST);
    //
    // glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100.0f);
    // glm::mat4 model;
    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // glm::mat4 view;
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // unsigned int VAO, VBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    if(glfwInit() == false) {
        fprintf(stderr, "Error initializing GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "IS F311 Computer Graphics Project", NULL, NULL);

    if(!window) {
        glfwTerminate();
        fprintf(stderr, "Error while creating a window\n");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0.0f, 0.0f, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);


    int i; /* Simple iterator */
    GLuint vao, vbo[2]; /* Create handles for our Vertex Array Object and two Vertex Buffer Objects */
    int IsCompiled_VS, IsCompiled_FS;
    int IsLinked;
    int maxLength;
    char *vertexInfoLog;
    char *fragmentInfoLog;
    char *shaderProgramInfoLog;

    /* We're going to create a simple diamond made from lines */
    const GLfloat diamond[4][2] = {
    {  0.0,  1.0  }, /* Top point */
    {  1.0,  0.0  }, /* Right point */
    {  0.0, -1.0  }, /* Bottom point */
    { -1.0,  0.0  } }; /* Left point */

    const GLfloat colors[4][3] = {
    {  1.0,  0.0,  0.0  }, /* Red */
    {  0.0,  1.0,  0.0  }, /* Green */
    {  0.0,  0.0,  1.0  }, /* Blue */
    {  1.0,  1.0,  1.0  } }; /* White */

    /* These pointers will receive the contents of our shader source code files */
    GLchar *vertexsource, *fragmentsource;

    /* These are handles used to reference the shaders */
    GLuint vertexshader, fragmentshader;

    /* This is a handle to the shader program */
    GLuint shaderprogram;

    /* Allocate and assign a Vertex Array Object to our handle */
    glGenVertexArrays(1, &vao);

    /* Bind our Vertex Array Object as the current used object */
    glBindVertexArray(vao);

    /* Allocate and assign two Vertex Buffer Objects to our handle */
    glGenBuffers(2, vbo);

    /* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    /* Copy the vertex data from diamond to our buffer */
    /* 8 * sizeof(GLfloat) is the size of the diamond array, since it contains 8 GLfloat values */
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), diamond, GL_STATIC_DRAW);

    /* Specify that our coordinate data is going into attribute index 0, and contains two floats per vertex */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    /* Enable attribute index 0 as being used */
    glEnableVertexAttribArray(0);

    /* Bind our second VBO as being the active buffer and storing vertex attributes (colors) */
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    /* Copy the color data from colors to our buffer */
    /* 12 * sizeof(GLfloat) is the size of the colors array, since it contains 12 GLfloat values */
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

    /* Specify that our color data is going into attribute index 1, and contains three floats per vertex */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /* Enable attribute index 1 as being used */
    glEnableVertexAttribArray(1);

    /* Read our shaders into the appropriate buffers */
    vertexsource = filetobuf("tutorial2.vert");
    fragmentsource = filetobuf("tutorial2.frag");

    /* Create an empty vertex shader handle */
    vertexshader = glCreateShader(GL_VERTEX_SHADER);

    /* Send the vertex shader source code to GL */
    /* Note that the source code is NULL character terminated. */
    /* GL will automatically detect that therefore the length info can be 0 in this case (the last parameter) */
    glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);

    /* Compile the vertex shader */
    glCompileShader(vertexshader);

    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);
    // if(IsCompiled_VS == FALSE)
    // {
    //    glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);
    //
    //    /* The maxLength includes the NULL character */
    //    vertexInfoLog = (char *)malloc(maxLength);
    //
    //    glGetShaderInfoLog(vertexshader, maxLength, &maxLength, vertexInfoLog);
    //
    //    /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
    //    /* In this simple program, we'll just leave */
    //    free(vertexInfoLog);
    //    return;
    // }

    /* Create an empty fragment shader handle */
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

    /* Send the fragment shader source code to GL */
    /* Note that the source code is NULL character terminated. */
    /* GL will automatically detect that therefore the length info can be 0 in this case (the last parameter) */
    glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);

    /* Compile the fragment shader */
    glCompileShader(fragmentshader);

    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &IsCompiled_FS);
    // if(IsCompiled_FS == FALSE)
    // {
    //    glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &maxLength);
    //
    //    /* The maxLength includes the NULL character */
    //    fragmentInfoLog = (char *)malloc(maxLength);
    //
    //    glGetShaderInfoLog(fragmentshader, maxLength, &maxLength, fragmentInfoLog);
    //
    //    /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
    //    /* In this simple program, we'll just leave */
    //    free(fragmentInfoLog);
    //    return;
    // }

    /* If we reached this point it means the vertex and fragment shaders compiled and are syntax error free. */
    /* We must link them together to make a GL shader program */
    /* GL shader programs are monolithic. It is a single piece made of 1 vertex shader and 1 fragment shader. */
    /* Assign our program handle a "name" */
    shaderprogram = glCreateProgram();

    /* Attach our shaders to our program */
    glAttachShader(shaderprogram, vertexshader);
    glAttachShader(shaderprogram, fragmentshader);

    /* Bind attribute index 0 (coordinates) to in_Position and attribute index 1 (color) to in_Color */
    /* Attribute locations must be setup before calling glLinkProgram. */
    glBindAttribLocation(shaderprogram, 0, "in_Position");
    glBindAttribLocation(shaderprogram, 1, "in_Color");

    /* Link our program */
    /* At this stage, the vertex and fragment programs are inspected, optimized and a binary code is generated for the shader. */
    /* The binary code is uploaded to the GPU, if there is no error. */
    glLinkProgram(shaderprogram);

    /* Again, we must check and make sure that it linked. If it fails, it would mean either there is a mismatch between the vertex */
    /* and fragment shaders. It might be that you have surpassed your GPU's abilities. Perhaps too many ALU operations or */
    /* too many texel fetch instructions or too many interpolators or dynamic loops. */

    glGetProgramiv(shaderprogram, GL_LINK_STATUS, (int *)&IsLinked);
    // if(IsLinked == FALSE)
    // {
    //    /* Noticed that glGetProgramiv is used to get the length for a shader program, not glGetShaderiv. */
    //    glGetProgramiv(shaderprogram, GL_INFO_LOG_LENGTH, &maxLength);
    //
    //    /* The maxLength includes the NULL character */
    //    shaderProgramInfoLog = (char *)malloc(maxLength);
    //
    //    /* Notice that glGetProgramInfoLog, not glGetShaderInfoLog. */
    //    glGetProgramInfoLog(shaderprogram, maxLength, &maxLength, shaderProgramInfoLog);
    //
    //    /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
    //    /* In this simple program, we'll just leave */
    //    free(shaderProgramInfoLog);
    //    return;
    // }

    /* Load the shader into the rendering pipeline */
    glUseProgram(shaderprogram);

    /* Loop our display increasing the number of shown vertexes each time.
     * Start with 2 vertexes (a line) and increase to 3 (a triangle) and 4 (a diamond) */

    /* Cleanup all the things we bound and allocated */


    // Render loop for the OpenGL window. The scene is redrawn on every refresh.

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        // glDrawArrays(GL_LINE_LOOP, 0, 4);

        sleep(0.1);
    }

    glfwDestroyWindow(window);
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDetachShader(shaderprogram, vertexshader);
    glDetachShader(shaderprogram, fragmentshader);
    glDeleteProgram(shaderprogram);
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);
    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(1, &vao);
    free(vertexsource);
    free(fragmentsource);
    glfwTerminate();
    return 0;
}
