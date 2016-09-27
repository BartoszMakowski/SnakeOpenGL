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
#include "Snake.h"
#include "Camera.h"
#include "Cube.h"

#include <iostream>
#include <cmath>
#include <vector>

void key_callback(GLFWwindow*, int, int, int, int);
bool moveAllowed(int);

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
	void setMatrixes();
	void createObjects();

	void gameLoop();

private:
	void clearBuffer();
	void updateTime();
	bool nextPeriod(GLfloat);
	GLfloat countPeriod(GLfloat);

	void createCubes();

	GLFWwindow* window;
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
	// transformation
	mat4 view;
	mat4 projection;
	// objects
	Ground* ground;
	Space* space;
	Snake* snake;
	Cube* cubes;
	// camera
	Camera* camera;
	// time
	GLfloat deltaTime;
	GLfloat lastFrame;
	bool moveSnake;
};

#endif RENDERMANAGER_H