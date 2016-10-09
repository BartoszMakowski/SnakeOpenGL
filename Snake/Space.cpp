#include "Space.h"

GLfloat spaceVertices[] = { // with texture
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f,  // Top Right

	1.0f, -1.0f, 0.0f,
	1.0f, 0.0f,  // Bottom Right

	-1.0f, -1.0f, 0.0f,
	0.0f, 0.0f,  // Bottom Left

	-1.0f, 1.0f, 0.0f,
	0.0f, 1.0f   // Top Left 
};

GLuint spaceIndices[] = {
	0, 1, 3,   // First Triangle
	1, 2, 3    // Second Triangle
};

Space::Space() {
	shader = new Shader(SPACEVERTEXSHADERPATH, SPACEFRAGMENTSHADERPATH);
	generateBuffer();
	interpretVertexData();
	loadTexture();
	transformModelMatrixes();
}

Space::~Space() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete shader;
}

void Space::draw(mat4* view, mat4* projection) {
	glBindTexture(GL_TEXTURE_2D, texture);
	shader->Use();
	glBindVertexArray(VAO);
	drawSpaces(view, projection);
	glBindVertexArray(0);
}

void Space::transformCoordinates(mat4* view, mat4* projection) {
	modelLoc = glGetUniformLocation(shader->Program, "model");
	viewLoc = glGetUniformLocation(shader->Program, "view");
	projectionLoc = glGetUniformLocation(shader->Program, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(*projection));
}

void Space::generateBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(spaceVertices), spaceVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(spaceIndices), spaceIndices, GL_STATIC_DRAW);
}

void Space::interpretVertexData() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

}

void Space::loadTexture() {
	int locWidth, locHeight;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image(SPACEIMAGEPATH, &locWidth, &locHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, locWidth, locHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Space::drawSpaces(mat4* view, mat4* projection) {
	for (int i = 0; i < (int)modelMatrixes.size(); i++) {
		model = modelMatrixes[i];;
		transformCoordinates(view, projection);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Space::transformModelMatrixes() {
	mat4 tmpModel;
	int numberOfSpacePlanes = 4;

	for (int i = 0; i < numberOfSpacePlanes; i++)
		modelMatrixes.push_back(tmpModel);

	modelMatrixes[0] = translate(modelMatrixes[0], vec3(0.0f, 0.0f, 5.0f));
	modelMatrixes[0] = rotate(modelMatrixes[0], glm::radians(45.0f), vec3(1.0f, 0.0f, 0.0f));

	modelMatrixes[1] = translate(modelMatrixes[1], vec3(0.0f, 0.0f, -5.0f));
	modelMatrixes[1] = rotate(modelMatrixes[1], glm::radians(45.0f), vec3(-1.0f, 0.0f, 0.0f));

	modelMatrixes[2] = translate(modelMatrixes[2], vec3(7.0f, 0.0f, 0.0f));
	modelMatrixes[2] = rotate(modelMatrixes[2], glm::radians(90.0f), vec3(0.0f, 1.0f, -0.5f));

	modelMatrixes[3] = translate(modelMatrixes[3], vec3(-7.0f, 0.0f, 0.0f));
	modelMatrixes[3] = rotate(modelMatrixes[3], glm::radians(90.0f), vec3(0.0f, -1.0f, 0.5f));

	for (int i = 0; i < numberOfSpacePlanes; i++)
		modelMatrixes[i] = scale(modelMatrixes[i], vec3(10.0f, 10.0f, 0.0f));

}