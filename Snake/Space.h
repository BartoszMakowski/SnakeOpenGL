#ifndef SPACE_H
#define SPACE_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "SOIL\SOIL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"

static const char* SPACEVERTEXSHADERPATH = ".\\Shaders\\ground.vs";
static const char* SPACEFRAGMENTSHADERPATH = ".\\Shaders\\ground.frag";
static const char* SPACEIMAGEPATH = ".\\textures\\space.png";

GLfloat spaceVertices[];
GLuint spaceIndices[];

using glm::mat4;
using glm::vec3;
using glm::scale;
using glm::rotate;
using glm::translate;

class Space {
public:
	Space();
	~Space();
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
	mat4 model1;
	mat4 model2;
	mat4 model3;
	mat4 model4;
	GLint modelLoc;
	GLint viewLoc;
	GLint projectionLoc;

	void transformCoordinates(mat4*, mat4*);
	void generateBuffer();
	void interpretVertexData();
	void loadTexture();
	void drawSpaces(mat4*, mat4*);
};


#endif SPACE_H