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
	loadTexture();
	model = rotate(model, glm::radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	model = scale(model, vec3(3.3f, 2.8f, 0.0f));
}

Ground::~Ground() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete shader;
}

void Ground::draw(mat4* view, mat4* projection) {
	glBindTexture(GL_TEXTURE_2D, texture);
	shader->Use();
	transformCoordinates(view, projection);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Ground::transformCoordinates(mat4* view, mat4* projection) {
	modelLoc = glGetUniformLocation(shader->Program, "model");
	viewLoc = glGetUniformLocation(shader->Program, "view");
	projectionLoc = glGetUniformLocation(shader->Program, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(*projection));
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

vec2 Ground::randomPos(){
	int x, y;
	x = rand() % 10 - 5;
	y = rand() % 10 - 5;
	return vec2(x, y);
}