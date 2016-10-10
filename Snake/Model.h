#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include <vector>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SOIL\SOIL.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Shader.h"

using namespace glm;
using namespace std;

static const char* VERETXSHADERPATH = ".\\Shaders\\cube.vs";
static const char* FRAGMENTSHADERPATH = ".\\Shaders\\cube.frag";
static const char* IMAGEPATH = ".\\textures\\rabbit.png";

//GLfloat vertices[];
//GLfloat normals[];
//GLuint indices[];


class Model
{
public:
	Model();
	~Model();
	void draw(mat4*, mat4*);
protected:
	mat4 model;
	mat4 baseModel;
	GLfloat scaleMultiplier;
	void initiateDrawing();
	void transformCoordinates(mat4*, mat4*);

private:
	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec2> uvs;
	
	GLuint VAO;
	GLuint VERTEX;
	GLuint UV;
	GLuint NORMAL;
	Shader* shader;

	GLuint texture;
	unsigned char* image;

	GLint modelLoc;
	GLint viewLoc;
	GLint projectionLoc;
	
	void generateBuffer();
	void interpretVertexData();
	bool loadOBJ(const char*);
	template<typename T>
	void genBuf(GLuint*, vector<T>);
	void loadTexture();
};

