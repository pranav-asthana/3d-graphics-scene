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
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


#include "shader.hpp"
#include "Camera.h"
#include "Constants.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
using namespace glm;
using namespace std;
typedef pair<GLuint, GLuint> VertexColorPair;
GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void cubeDraw(glm::vec3 translationCoord, GLuint matrixID, glm::mat4 proj, glm::mat4 view)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, translationCoord);
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
    glm::mat4 MVP = proj*view*model;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles
}

void planeDraw(glm::vec3 translationCoord, GLuint matrixID, glm::mat4 proj, glm::mat4 view)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, vec3(100.0f, 100.0f, 100.0f));
    // model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 MVP = proj*view*model;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 2*3);
}

void objDraw(glm::vec3 translationCoord, GLuint matrixID, glm::mat4 proj, glm::mat4 view, int size, int index)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, translationCoord);

    // model = glm::scale(model, vec3(100.0f, 100.0f, 100.0f));
    glm::mat4 MVP = proj*view*model;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    // glDrawArrays(GL_TRIANGLES, 0, 3*size); // 12*3 indices starting at 0 -> 12 triangles

    glDrawElements(GL_TRIANGLES, index, GL_UNSIGNED_INT, 0);
}

void drawGenericObject(GLuint &VAO, GLuint matrixID,
                        glm::mat4 proj,
                        glm::mat4 view,
                        int size,
                        bool elemental,
                        glm::vec3 translationVector = glm::vec3(0,0,0),
                        glm::vec3 scaleVector = glm::vec3(1,1,1),
                        GLfloat rotationAngle = 0,
                        glm::vec3 rotationAxis = glm::vec3(1,0,0))
{
    glBindVertexArray(VAO);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, translationVector);
    model = glm::scale(model, scaleVector);
    model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
    glm::mat4 MVP = proj*view*model;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    if (elemental) {
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, size*3);
    }
    glBindVertexArray(0);
}

bool loadAssImp(
	const char * path,
	std::vector<unsigned short> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec3> & normals
){

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
	if( !scene) {
		fprintf( stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}


	// Fill face indices
	indices.reserve(3*mesh->mNumFaces);
	for (unsigned int i=0; i<mesh->mNumFaces; i++){
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}

	// The "scene" pointer will be deleted automatically by "importer"
	return true;
}

void setupVAO(GLuint* VertexArrayID, vector<VertexColorPair> &VBOArray)
{
    glGenVertexArrays(2, VertexArrayID);

    glBindVertexArray(VertexArrayID[0]);

    //cube
    VertexColorPair cube;
    // GLuint vertexbuffer, colorbuffer;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &cube.first);
    glBindBuffer(GL_ARRAY_BUFFER, cube.first);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &cube.second);
    glBindBuffer(GL_ARRAY_BUFFER, cube.second);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    VBOArray.push_back(cube);
    glBindVertexArray(0);

    glBindVertexArray(VertexArrayID[1]);
    //plane
    // GLuint floorvertexbuffer, floorcolorbuffer;
    VertexColorPair plane;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &plane.first);
    glBindBuffer(GL_ARRAY_BUFFER, plane.first);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor_data), floor_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,(void*)0);

    glGenBuffers(1, &plane.second);
    glBindBuffer(GL_ARRAY_BUFFER, plane.second);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor_color_data), floor_color_data, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,(void*)0);
    glBindVertexArray(0);
    VBOArray.push_back(plane);
}

bool initOpenGL()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}

Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);

void setCallBacks(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

int main()
{
    if(!glfwInit())
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return false;
    }
    if (!initOpenGL()) {
        return -1;
    }
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cubes!", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
    setCallBacks(window);
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return false;
    }
    GLuint ModelArrayID, ModelVBO, ModelColorVBO, EBO;

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;

    int i = 0;
    if(loadAssImp("5wtf.obj", indices, vertices, normals)) {
        GLfloat ModelVertexArray[10800];
        GLfloat ModelColorArray[10800];
        unsigned int indexList[10800];
        for (auto it = vertices.begin(); it != vertices.end(); it++) {
            ModelVertexArray[i++] = it->x;
            ModelVertexArray[i++] = it->y;
            ModelVertexArray[i++] = it->z;
        }

        for (int j = 0; j < indices.size(); j++) {
            indexList[j] = indices[j];
        }
        for (int j = 0; j < i; i++) {
            ModelColorArray[j++] = 1;
        }

        glGenVertexArrays(1, &ModelArrayID);
        glBindVertexArray(ModelArrayID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &ModelVBO);
        glBindBuffer(GL_ARRAY_BUFFER, ModelVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(ModelVertexArray), ModelVertexArray, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // glGenBuffers(1, &ModelColorVBO);
        // glBindBuffer(GL_ARRAY_BUFFER, ModelColorVBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(ModelColorArray), ModelColorArray, GL_STATIC_DRAW);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexList),
                     indexList, GL_STATIC_DRAW);

        glBindVertexArray(0);
        cout << "success";
    }

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
    GLuint matrixID = glGetUniformLocation(programID, "MVP"); //finds mvp and stores it here

    GLuint VertexArrayID[2];
    vector<VertexColorPair> VBOArray;
    setupVAO(VertexArrayID, VBOArray);

    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        cout << "FPS: " << 1.0f/deltaTime << endl;
        lastFrame = currentFrame;
        camera.processInput(window, deltaTime);
        glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.2f, 10.0f);
        glm::mat4 view;
        view = camera.getCameraView();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    	glUseProgram(programID);

        int num = 100;
        for (int i = 0; i < num; i++) {
            drawGenericObject(VertexArrayID[0], matrixID, proj, view, 12, false, glm::vec3(i,i,i), glm::vec3(0.25,0.25,0.25), 45.0f, glm::vec3(1,0,0));
        }
        drawGenericObject(VertexArrayID[1], matrixID, proj, view, 2, false, glm::vec3(0,0,0), glm::vec3(100,1,100));//, optional GLfloat rotationAngle, optional glm::vec3 rotationAxis)
        drawGenericObject(ModelArrayID, matrixID, proj, view, indices.size(), true, glm::vec3(0,0,0), glm::vec3(1,1,1), (float)glfwGetTime()*45.0f, glm::vec3(0,1,0));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //write delete code
	glDeleteProgram(programID);
	glDeleteVertexArrays(2, VertexArrayID);
    glDeleteVertexArrays(1, &ModelArrayID);

	glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.scroll_callback(window, xoffset, yoffset);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.mouse_callback(window, xpos, ypos);
}
