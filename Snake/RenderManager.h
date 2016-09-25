#ifndef RENDERMANAGER_H
#define RENDER_MANAGER_H
#define GLEW_STATIC

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "SOIL\SOIL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "Ground.h"
#include "Space.h"
#include "Camera.h"
#include "Cube.h"

#include <iostream>
#include <cmath>
#include <vector>

GLfloat vertices[];

void key_callback(GLFWwindow*, int, int, int, int);

using std::cout;
using std::endl;
using glm::mat4;
using glm::translate;
using glm::rotate;
using glm::scale;
using glm::radians;

class RenderManager {
public:
	RenderManager();
	~RenderManager();

	void initGLFW();
	bool createWindowObject();
	void setKeyCallback();
	bool initGLEW();
	void setViewport();
	void setDepthBuffer();
	void manageShaders();
	void setMatrixes();
	void createObjects();
	void releaseResources();

	void gameLoop();

private:
	void clearBuffer();
	void generateBuffer();
	void interpretVertexData();
	void updateTime();

	void drawTriangle();

	void changeColor();
	void loadTriangleTexture();

	void createCubes();

	GLFWwindow* window;
	// shaders
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Shader groundShader;
	// compile error management
	GLint success;
	GLchar infoLog[512];
	// attributes of window
	static const int HEIGHT = 1000;
	static const int WIDTH = 1600;
	static const char* TITLE;
	// view port variables
	int width;
	int height;
	// changing colors
	GLfloat timeValue;
	GLfloat redValue;
	GLint vertexColorLocation;
	// texture
	GLuint triangleTexture;
	unsigned char* image;
	// transformation
	GLint transformLoc;
	GLint viewLoc;
	GLint projectionLoc;
	mat4 view;
	mat4 projection;
	// objects
	Ground* ground;
	Space* space;
	Cube* cubes;
	// camera
	Camera* camera;
	// time
	GLfloat deltaTime;
	GLfloat lastFrame;
};

#endif RENDERMANAGER_H