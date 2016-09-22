#include "Ground.h"

GLfloat groundVertices[] = { // with texture
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f,  // Top Right

	1.0f, -1.0f, 0.0f,
	1.0f, 0.0f,  // Bottom Right

	-1.0f, -1.0f, 0.0f,
	0.0f, 0.0f,  // Bottom Left

	-1.0f, 1.0f, 0.0f,
	0.0f, 1.0f   // Top Left 
};

GLuint groundIndices[] = {
	0, 1, 3,   // First Triangle
	1, 2, 3    // Second Triangle
};

Ground::Ground() {
	shader = new Shader(GROUNDVERTEXSHADERPATH, GROUNDFRAGMENTSHADERPATH);
	generateBuffer();
	interpretVertexData();
	transformCoordinates();
}

Ground::~Ground() {
	delete shader;
	delete image;
}

void Ground::draw() {
	glBindTexture(GL_TEXTURE_2D, texture);
	shader->Use();
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Ground::transformCoordinates() {
	transform = glm::rotate(transform, glm::radians(45.0f), vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, vec3(0.5f, 0.5f, 0.5f));
	transformLoc = glGetUniformLocation(shader->Program, "transform");
}

void Ground::generateBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundIndices), groundIndices, GL_STATIC_DRAW);
}

void Ground::interpretVertexData() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	loadTexture();
}

void Ground::loadTexture() {
	int locWidth, locHeight;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image(GROUNDIMAGEPATH, &locWidth, &locHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, locWidth, locHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}