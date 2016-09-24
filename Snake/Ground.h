#ifndef GROUND_H
#define GROUND_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "SOIL\SOIL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"

static const char* GROUNDVERTEXSHADERPATH = ".\\Shaders\\ground.vs";
static const char* GROUNDFRAGMENTSHADERPATH = ".\\Shaders\\ground.frag";
static const char* GROUNDIMAGEPATH = ".\\textures\\sand.png";

GLfloat groundVertices[];
GLuint groundIndices[];

using glm::mat4;
using glm::vec3;

class Ground {
public:
	Ground();
	~Ground();
	void draw(mat4*, mat4*);

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
	mat4 model;
	GLint modelLoc;
	GLint viewLoc;
	GLint projectionLoc;

	void transformCoordinates(mat4*, mat4*);
	void generateBuffer();
	void interpretVertexData();
	void loadTexture();
};


#endif GROUND_H