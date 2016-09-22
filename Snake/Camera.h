#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using std::vector;
using glm::vec3;
using glm::normalize;
using glm::cross;
using glm::mat4;
using glm::lookAt;
using glm::radians;

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
public:
	vec3 Position;
	vec3 Front;
	vec3 Up;
	vec3 Right;
	vec3 WorldUp;

	GLfloat Yaw;
	GLfloat Pitch;

	GLfloat MovementSpeed;

	Camera();
	mat4 getViewMatrix();
	void processKeyboard(CameraMovement, GLfloat);

private:
	void updateCameraVectors();
};

#endif CAMERA_H