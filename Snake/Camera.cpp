#include "Camera.h"

Camera::Camera() {
	Position = vec3(0.0f, 4.0f, -RADIUS);
	Front = vec3(0.0f, 0.0f, 0.0f);
	Up = vec3(0.0f, 1.0f, 0.0f);
}

mat4 Camera::getViewMatrix() {
	return lookAt(Position, Front, Up);
}

void Camera::move(bool* keys, GLfloat deltaTime) {
	if (keys[GLFW_KEY_KP_8])
		processKeyboardInput(FORWARD, deltaTime);
	if (keys[GLFW_KEY_KP_5])
		processKeyboardInput(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_KP_4])
		processKeyboardInput(LEFT, deltaTime);
	if (keys[GLFW_KEY_KP_6])
		processKeyboardInput(RIGHT, deltaTime);
}

void Camera::processKeyboardInput(CameraMovement direction, GLfloat deltaTime) {
	GLfloat velocity = CAMERASPEED * deltaTime;

	if (direction == FORWARD && Position.y > 0.7)
		Position -= (Position * velocity);
	if (direction == BACKWARD && Position.y < 7.0)
		Position += (Position * velocity);
	if (direction == LEFT)
		rotateLeft(velocity);
	if (direction == RIGHT)
		rotateRight(velocity);
}

void Camera::rotateLeft(GLfloat velocity) {
	GLfloat camX = Position.x;
	GLfloat camZ = Position.z;
	GLfloat radius = sqrt(camZ*camZ + camX*camX);

	velocity *= radius / 2;

	if (camX < 0 && camZ > -radius && camX >= -radius && camZ <= 0) {
		camX += velocity;
		Position.x = camX;
		Position.z = -sqrt(absolute(radius*radius - camX*camX));
		if (Position.z <= -radius) {
			Position.x = 0;
			Position.z = -radius;
		}
	}
	else if (camX > -radius && camZ > 0 && camX <= 0 && camZ <= radius) {
		camX -= velocity;
		Position.x = camX;
		Position.z = sqrt(absolute(radius*radius - camX*camX));
		if (Position.x <= -radius) {
			Position.x = -radius;
			Position.z = 0;
		}
	}
	else if (camX > 0 && camZ < radius && camX <= radius && camZ >= 0) {
		camX -= velocity;
		Position.x = camX;
		Position.z = sqrt(absolute(radius*radius - camX*camX));
		if (Position.z >= radius) {
			Position.x = 0;
			Position.z = radius;
		}
	}
	else if (camX < radius && camZ < 0 && camX >= 0 && camZ >= -radius) {
		camX += velocity;
		Position.x = camX;
		Position.z = -sqrt(absolute(radius*radius - camX*camX));
		if (Position.x >= radius) {
			Position.x = radius;
			Position.z = 0;
		}
	}
}

void Camera::rotateRight(GLfloat velocity) {
	GLfloat camX = Position.x;
	GLfloat camZ = Position.z;
	GLfloat radius = sqrt(camZ*camZ + camX*camX);

	velocity *= radius / 2;

	if (camX <= 0 && camZ >= -radius && camX > -radius && camZ < 0) {
		camX -= velocity;
		Position.x = camX;
		Position.z = -sqrt(absolute(radius*radius - camX*camX));
		if (Position.x <= -radius) {
			Position.x = -radius;
			Position.z = 0;
		}
	}
	else if (camX >= -radius && camZ >= 0 && camX < 0 && camZ < radius) {
		camX += velocity;
		Position.x = camX;
		Position.z = sqrt(absolute(radius*radius - camX*camX));
		if (Position.z >= radius) {
			Position.x = 0;
			Position.z = radius;
		}
	}
	else if (camX >= 0 && camZ <= radius && camX < radius && camZ > 0) {
		camX += velocity;
		Position.x = camX;
		Position.z = sqrt(absolute(radius*radius - camX*camX));
		if (Position.x >= radius) {
			Position.x = radius;
			Position.z = 0;
		}
	}
	else if (camX <= radius && camZ <= 0 && camX > 0 && camZ > -radius) {
		camX -= velocity;
		Position.x = camX;
		Position.z = -sqrt(absolute(radius*radius - camX*camX));
		if (Position.z <= -radius) {
			Position.x = 0;
			Position.z = -radius;
		}
	}
}

GLfloat Camera::absolute(GLfloat a) {
	if (a < 0.0f)
		return -a;
	return a;
}