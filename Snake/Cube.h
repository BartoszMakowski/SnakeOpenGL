#ifndef CUBE_H
#define CUBE_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "SOIL\SOIL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"

static const char* CUBEVERETXSHADERPATH = ".\\Shaders\\cube.vs";
static const char* CUBEFRAGMENTSHADERPATH = ".\\Shaders\\cube.frag";
static const char* CUBEIMAGEPATH = ".\\textures\\box.png";

GLfloat cubeVertices[];
GLfloat cubeNormals[];
GLuint cubeIndices[];

using glm::mat4;
using glm::vec3;
using glm::radians;
using glm::rotate;
using glm::scale;
using glm::translate;

class Cube {
public:
	Cube();
	~Cube();
	void draw(mat4*, mat4*);

private:
	// shaders
	Shader* shader;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint lightVAO;
	GLuint NORMALS;
	// texture
	GLuint texture;
	unsigned char* image;
	// transformation
	mat4 model;
	mat4 baseModel;
	GLint modelLoc;
	GLint viewLoc;
	GLint projectionLoc;
	GLfloat scaleMultiplier;

	void drawCubes(mat4*, mat4*);
	void transformCoordinates(mat4*, mat4*);
	void generateBuffer();
	void interpretVertexData();
	void loadTexture();
};

#endif CUBE_H