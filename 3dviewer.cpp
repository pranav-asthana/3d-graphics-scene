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

#include "shader.hpp"
#include "Camera.h"
#include "Constants.h"
#include "src/scene.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SQUARE_SIDE 15.0f
#define MIN_ALT 0.5f
#define MAX_ALT 10.0f

using namespace glm;
using namespace std;

const GLfloat x_min = -SQUARE_SIDE;
const GLfloat x_max = SQUARE_SIDE;
const GLfloat y_min = MIN_ALT;
const GLfloat y_max = MAX_ALT;
const GLfloat z_min = -SQUARE_SIDE;
const GLfloat z_max = SQUARE_SIDE;

typedef pair<GLuint, GLuint> VertexColorPair;
GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

struct ObjectData {
    GLuint ModelArrayID, ModelVBO, ModelColorVBO, ModelNormalVBO, EBO, indexSize;
};

void drawGenericObject(GLuint &VAO, GLuint matrixID, GLuint modelID,
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
    glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
    if (elemental) {
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, size*3);
    }
    glBindVertexArray(0);
}

bool loadAssImp(const char * path, std::vector<unsigned short> &indices,
                std::vector<glm::vec3> &vertices,
                std::vector<glm::vec3> &normals) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 0);
	if( !scene) {
		fprintf( stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0];
	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

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

void setupMeshVAO(Mesh mesh, GLfloat* color_vector, vector<ObjectData> &objectVector)
{
    ObjectData object;

    vector<GLfloat> v = mesh.getVertices();
    GLfloat* vertices = &v[0];
    object.indexSize = v.size()/3; //# of vertices = arraysize/3 (x,y,z)
    int size = v.size()*sizeof(GLfloat);

    glGenVertexArrays(1, &(object.ModelArrayID));
    glBindVertexArray(object.ModelArrayID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &(object.ModelVBO));
    glBindBuffer(GL_ARRAY_BUFFER, object.ModelVBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &(object.ModelColorVBO));
    glBindBuffer(GL_ARRAY_BUFFER, object.ModelColorVBO);
    glBufferData(GL_ARRAY_BUFFER, size, color_vector, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindVertexArray(0);

    objectVector.push_back(object);
    // int len = v.size();
}

// Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);
Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, x_min, x_max, y_min, y_max, z_min, z_max);

void setCallBacks(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void generateModelVAO(string path, ObjectData &object)
{
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;

    int i = 0;
    if(loadAssImp(path.c_str(), indices, vertices, normals)) {
        GLfloat ModelVertexArray[vertices.size()*3];
        GLfloat ModelColorArray[vertices.size()*3];
        GLfloat ModelNormalArray[normals.size()*3];
        unsigned int indexList[indices.size()];

        for (auto it = vertices.begin(); it != vertices.end(); it++) {
            ModelVertexArray[i++] = it->x;
            ModelVertexArray[i++] = it->y;
            ModelVertexArray[i++] = it->z;
        }
        i = 0;
        for (auto it = normals.begin(); it != normals.end(); it++) {
            ModelNormalArray[i++] = it->x;
            ModelNormalArray[i++] = it->y;
            ModelNormalArray[i++] = it->z;
            cout << it->x << ' ' << it->y << ' ' << it->z << '\n';
        }

        for (int j = 0; j < indices.size(); j++) {
            indexList[j] = indices[j];
        }

        cout << path << i;
        for (int j = 0; j < i; j+=9) {
            ModelColorArray[j] = 1.0;
            ModelColorArray[j+1] = 1.0;
            ModelColorArray[j+2] = 0.0;

            ModelColorArray[j+3] = 0.7;
            ModelColorArray[j+4] = 0.7;
            ModelColorArray[j+5] = 0.2;

            ModelColorArray[j+6] = 0.7;
            ModelColorArray[j+7] = 0.7;
            ModelColorArray[j+8] = 0.2;
        }

        object.indexSize = indices.size();

        glGenVertexArrays(1, &(object.ModelArrayID));
        glBindVertexArray(object.ModelArrayID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);


        glGenBuffers(1, &(object.ModelVBO));
        glBindBuffer(GL_ARRAY_BUFFER, object.ModelVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(ModelVertexArray), ModelVertexArray, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glGenBuffers(1, &(object.ModelColorVBO));
        glBindBuffer(GL_ARRAY_BUFFER, object.ModelColorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(ModelColorArray), ModelColorArray, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glGenBuffers(1, &(object.ModelNormalVBO));
        glBindBuffer(GL_ARRAY_BUFFER, object.ModelNormalVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(ModelNormalArray), ModelNormalArray, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glGenBuffers(1, &(object.EBO));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexList),
                     indexList, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }
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

    GLuint ModelArrayID, ModelVBO, ModelColorVBO, EBO, indexSize;
    ObjectData swing, carousel, swingChair;
    generateModelVAO("swing_seat.obj", swingChair);
    generateModelVAO("swing_frame.obj", swing);
    generateModelVAO("1simple_round.obj", carousel);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
    GLuint matrixID = glGetUniformLocation(programID, "MVP"); //finds mvp and stores it here
    GLuint modelID = glGetUniformLocation(programID, "model");

    GLuint VertexArrayID[2];
    vector<VertexColorPair> VBOArray;
    setupVAO(VertexArrayID, VBOArray);

    glm::mat4 proj;
    glm::mat4 view;

    Scene scene = Scene();
    scene.addMonkeyBars(glm::vec3(-10, 0, 0), glm::vec3(0.5, 1, 0.5), 7, 3);
    scene.addSeeSaw(glm::vec3(10, 0, 0), glm::vec3(0.2, 0.2, 0.7));
    scene.addSlide(glm::vec3(-4, 0, -10), glm::vec3(0.7, 0, 0), 3,
                    glm::rotate(glm::mat4(1.0), (float)glm::radians(150.0),
                    glm::vec3(0, 1, 0)));
    scene.addFence(glm::vec4(x_min, x_max, z_min, z_max));
    scene.addFloor(glm::vec4(x_min, x_max, z_min, z_max));

    vector<Mesh> mesh_group = scene.getMesh();
    vector<vector<GLfloat>> color_vector_group = scene.getColors();

    vector<ObjectData> sceneMesh;

    for (int i = 0; i < mesh_group.size(); i++) {
        setupMeshVAO(mesh_group.at(i), &color_vector_group.at(i)[0], sceneMesh);
    }


    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        // cout << "FPS: " << 1.0f/deltaTime << endl;
        lastFrame = currentFrame;
        camera.processInput(window, deltaTime);
        proj = glm::perspective(glm::radians(camera.getFOV()), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.2f, 100.0f);
        view = camera.getCameraView();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glUseProgram(programID);
        // int num = 100;
        // for (int i = 0; i < num; i++) {
        //     drawGenericObject(VertexArrayID[0], matrixID, proj, view, 12, false, glm::vec3(i,i,i), glm::vec3(0.25,0.25,0.25), 45.0f, glm::vec3(1,0,0));
        // }
        // drawGenericObject(VertexArrayID[1], matrixID, proj, view, 2, false, glm::vec3(0,0,0), glm::vec3(100,1,100));//, optional GLfloat rotationAngle, optional glm::vec3 rotationAxis)
        drawGenericObject(carousel.ModelArrayID, matrixID, modelID, proj, view, carousel.indexSize, true, glm::vec3(0,0.2,0), glm::vec3(1,1,1), (float)glfwGetTime()*45.0f, glm::vec3(0,1,0));
        drawGenericObject(swing.ModelArrayID, matrixID, modelID, proj, view, swing.indexSize, true, glm::vec3(5,0,3));
        drawGenericObject(swingChair.ModelArrayID, matrixID, modelID, proj, view, swingChair.indexSize, true, glm::vec3(5,0,3), glm::vec3(1,1,1), (float)glfwGetTime()*180.0f, glm::vec3(10,5,1));
        // drawGenericObject(GLuint &VAO, GLuint matrixID, glm::mat4 proj, glm::mat4 view, int size, bool elemental, optional glm::vec3 translationVector, optional glm::vec3 scaleVector, optional GLfloat rotationAngle, optional glm::vec3 rotationAxis)

        for (auto it = sceneMesh.begin(); it != sceneMesh.end(); it++) {
            drawGenericObject(it->ModelArrayID, matrixID, modelID, proj, view, it->indexSize, false);
        }
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
