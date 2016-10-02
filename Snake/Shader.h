#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GL\glew.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
#include "glm/glm.hpp"

using std::stringstream;

class Shader {
public:
	GLuint Program;

	Shader();
	Shader(const GLchar*, const GLchar*);
	void Use();


private:
	GLuint vertex;
	GLuint fragment;
	GLint success;
	GLchar infoLog[512];

	void createVertexShader(const GLchar*);
	void createFragmentShader(const GLchar*);
	void createShaderProgram();
	void deleteShaders();
};

#endif