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
#include "Camera.h"

#include <iostream>
#include <cmath>

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
	void manageShaders();
	void createObjects();
	void releaseResources();

	void gameLoop();

private:
	void clearBuffer();
	void generateBuffer();
	void interpretVertexData();

	void drawTriangle();

	void changeColor();
	void loadTriangleTexture();

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
	static const int HEIGHT = 860;
	static const int WIDTH = 1024;
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
	// objects
	Ground* ground;
};

#endif RENDERMANAGER_H