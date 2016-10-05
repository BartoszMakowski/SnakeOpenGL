#pragma once

#include <vector>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "Shader.h"

using namespace glm;
using namespace std;

static const char* VERETXSHADERPATH = ".\\Shaders\\cube.vs";
static const char* FRAGMENTSHADERPATH = ".\\Shaders\\cube.frag";
static const char* IMAGEPATH = ".\\textures\\box.png";

//GLfloat vertices[];
//GLfloat normals[];
//GLuint indices[];


class Model
{
public:
	Model();
	~Model();
	bool loadOBJ(const char*);
	void draw(mat4*, mat4*);

private:
	vector<vec4> vertices;
	vector<vec4> normals;
	vector<vec2> uvs;
	Shader* shader;
	GLuint VAO;
	GLuint VERTEX;
	GLuint UV;
	GLuint NORMAL;

	mat4 model;
	mat4 baseModel;
	GLint modelLoc;
	GLint viewLoc;
	GLint projectionLoc;
	GLfloat scaleMultiplier;

	
	void generateBuffer();
	void interpretVertexData();
	void transformCoordinates(mat4*, mat4*);

	template<typename T>
	void genBuf(GLuint*, vector<T>);
};

