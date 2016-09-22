#include "Camera.h"

Camera::Camera() {
	this->Position = vec3(0.0f, 0.0f, 0.0f);
	this->WorldUp = vec3(0.0f, 1.0f, 0.0f);
	this->Yaw = YAW;
	this->Pitch = PITCH;
	updateCameraVectors();
}

mat4 Camera::getViewMatrix() {
	return lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime) {
	GLfloat velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		this->Position += this->Front * velocity;
	if (direction == BACKWARD)
		this->Position -= this->Front * velocity;
	if (direction == LEFT)
		this->Position -= this->Right * velocity;
	if (direction == RIGHT)
		this->Position += this->Right * velocity;
}

void Camera::updateCameraVectors() {
	vec3 front;
	front.x = cos(radians(this->Yaw)) * cos(radians(this->Pitch));
	front.y = sin(radians(this->Pitch));
	front.z = sin(radians(this->Yaw)) * cos(radians(this->Pitch));
	this->Front = normalize(front);
	this->Right = normalize(cross(this->Front, this->WorldUp));
	this->Up = normalize(cross(this->Right, this->Front));
}