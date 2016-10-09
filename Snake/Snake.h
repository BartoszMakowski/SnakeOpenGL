#ifndef SNAKE_H
#define SNAKE_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "SOIL\SOIL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"

#include <vector>

static const char* SNAKEVERTEXSHADERPATH = ".\\Shaders\\snake.vs";
static const char* SNAKEFRAGMENTSHADERPATH = ".\\Shaders\\snake.frag";
static const char* SNAKEIMAGEPATH = ".\\textures\\snake.png";

enum SnakeMovement {
	W,
	S,
	A,
	D
};

static const GLfloat ORIGINALSIDELENGTH = 2.0f;
const GLfloat SNAKESPEED = 1.5f;

GLfloat snakeVertices[];
GLuint snakeIndices[];

using std::vector;
using glm::mat4;
using glm::vec3;
using glm::vec2;
using glm::scale;
using glm::rotate;
using glm::translate;

class Snake {
public:
	Snake();
	~Snake();
	void draw(mat4*, mat4*);
	void move(bool*);
	vec2 getHeadPos();
	void setHit(bool val);
	bool getEnd();
	bool validPos(vec2);

private:
	// shaders
	Shader* shader;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	// texture
	GLuint texture;
	unsigned char* image;
	// transformation
	vector <mat4> snakeElements;
	mat4 baseModel;
	mat4 model;
	vec3 headPos;
	vector <vec3> snakePos;
	GLint modelLoc;
	GLint viewLoc;
	GLint projectionLoc;
	bool hit;
	bool end;

	void processKeyboardInput(SnakeMovement);
	void moveTail();
	void initiateSnakeElements();
	void drawSnakeElements(mat4*, mat4*);
	void transformCoordinates(mat4*, mat4*);
	void generateBuffer();
	void interpretVertexData();
	void loadTexture();
	int addElement();
	bool checkMove();
};


#endif SNAKE_H