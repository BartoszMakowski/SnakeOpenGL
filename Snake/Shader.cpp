#include "Shader.h"

static const char* FILEREADINGERROR = "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
static const char* VERTEXSHADERCOMPILEERROR = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
static const char* FRAGMENTSHADERCOMPILEERROR = "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
static const char* SHADERPROGRAMLINKERROR = "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";

Shader::Shader() {

}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	vShaderFile.exceptions(ifstream::badbit);
	fShaderFile.exceptions(ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e) {
		cout << FILEREADINGERROR;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	cout << vertexPath << endl << fragmentPath << endl;

	createVertexShader(vShaderCode);
	createFragmentShader(fShaderCode);
	createShaderProgram();
	deleteShaders();
}

void Shader::Use() {
	glUseProgram(Program);
}

void Shader::createVertexShader(const GLchar* vShaderCode) {
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << VERTEXSHADERCOMPILEERROR << infoLog << endl;
	}
}

void Shader::createFragmentShader(const GLchar* fShaderCode) {
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << FRAGMENTSHADERCOMPILEERROR << infoLog << endl;
	}
}

void Shader::createShaderProgram() {
	Program = glCreateProgram();
	glAttachShader(Program, vertex);
	glAttachShader(Program, fragment);
	glLinkProgram(Program);
	glGetProgramiv(Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(Program, 512, NULL, infoLog);
		cout << SHADERPROGRAMLINKERROR << infoLog << endl;
	}
}

void Shader::deleteShaders() {
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}