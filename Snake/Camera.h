#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <vector>
#include <iostream>

#include "GL/glew.h"
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using std::vector;
using glm::vec3;
using glm::normalize;
using glm::mat4;
using glm::lookAt;
using glm::radians;

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat SPEED = 1.5f;
const GLfloat RADIUS = 5.0;

class Camera {
public:
	vec3 Position;
	vec3 Front;
	vec3 Up;

	Camera();
	mat4 getViewMatrix();
	void move(bool*, GLfloat);
	void processKeyboardInput(CameraMovement, GLfloat);

private:
	void rotateLeft(GLfloat);
	void rotateRight(GLfloat);
	GLfloat absolute(GLfloat);
};

#endif CAMERA_H