#include "Cube.h"

GLfloat cubeVertices[] = { // with texture
	// Front, Top, Right (0)
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,
	// Front, Bottom, Right (1)
	1.0f, -1.0f, 1.0f,
	1.0f, 0.0f,
	// Front, Bottom, Left (2)
	-1.0f, -1.0f, 1.0f,
	0.0f, 0.0f,
	// Front, Top, Left (3)
	-1.0f, 1.0f, 1.0f,
	0.0f, 1.0f,
	// Right, Top, Back (4)
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f,
	// Right, Bottom, Back (5)
	1.0f, -1.0f, -1.0f,
	1.0f, 0.0f,
	// Right, Bottom, Front (6)
	1.0f, -1.0f, 1.0f,
	0.0f, 0.0f,
	// Right, Top, Front (7)
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f,
	// Back, Top, Left (8)
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f,
	// Back, Bottom, Left (9)
	-1.0f, -1.0f, -1.0f,
	1.0f, 0.0f,
	// Back, Bottom, Right (10)
	1.0f, -1.0f, -1.0f,
	0.0f, 0.0f,
	// Back, Top, Right (11)
	1.0f, 1.0f, -1.0f,
	0.0f, 1.0f,
	// Left, Top, Front (12)
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,
	// Left, Bottom, Front (13)
	-1.0f, -1.0f, 1.0f,
	1.0f, 0.0f,
	// Left, Bottom, Back (14)
	-1.0f, -1.0f, -1.0f,
	0.0f, 0.0f,
	// Left, Top, Back (15)
	-1.0f, 1.0f, -1.0f,
	0.0f, 1.0f,
	// Top, Back, Right (16)
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f,
	// Top, Front, Right (17)
	1.0f, 1.0f, 1.0f,
	1.0f, 0.0f,
	// Top, Front, Left (18)
	-1.0f, 1.0f, 1.0f,
	0.0f, 0.0f,
	// Top, Back, Left (19)
	-1.0f, 1.0f, -1.0f,
	0.0f, 1.0f,
	// Bottom, Front, Left (20)
	-1.0f, -1.0f, 1.0f,
	1.0f, 1.0f,
	// Bottom, Back, Left (21)
	-1.0f, -1.0f, -1.0f,
	1.0f, 0.0f,
	// Bottom, Back, Right (22)
	1.0f, -1.0f, -1.0f,
	0.0f, 0.0f,
	// Bottom, Front, Right (23)
	1.0f, -1.0f, 1.0f,
	0.0f, 1.0f
};

GLfloat cubeNormals[] = {
	0.0f, 0.0f, 1.0f,	// Front, Top, Right half
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	
	0.0f, 0.0f, 1.0f,    // Front, Bottom, Left half
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 0.0f,  0.0f,	// Right, Top, Right half
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,	// Right, Bottom, Left half
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 0.0f, -1.0f,	// Back, Top, Right half
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, -1.0f,	// Back, Bottom, Left half
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	-1.0f, 0.0f, 0.0f,	// Left, Top, Right half
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	-1.0f, 0.0f, 0.0f,	// Left, Bottom, Left half
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f,	// Top, Back, Right half
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	0.0f, 1.0f, 0.0f,	// Top, Front, Left half
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	0.0f, -1.0f, 0.0f,	// Bottom, Back, Right half
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, -1.0f, 0.0f,	// Bottom, Front, Left half
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f
};

GLuint cubeIndices[] {
	0, 1, 3,	// Front, Top, Right half
	2, 3, 1,    // Front, Bottom, Left half
	4, 5, 7,	// Right, Top, Right half
	6, 7, 5,	// Right, Bottom, Left half
	8, 9, 11,	// Back, Top, Right half
	10, 11, 9,	// Back, Bottom, Left half
	12, 13, 15,	// Left, Top, Right half
	14, 15, 13,	// Left, Bottom, Left half
	16, 17, 19,	// Top, Back, Right half
	18, 19, 17,	// Top, Front, Left half
	20, 21, 23,	// Bottom, Back, Right half
	22, 23, 21	// Bottom, Front, Left half
};

Cube::Cube() {
	shader = new Shader(CUBEVERETXSHADERPATH, CUBEFRAGMENTSHADERPATH);
	generateBuffer();
	interpretVertexData();
	loadTexture();
	scaleMultiplier = 0.15f;
	baseModel = translate(baseModel, vec3(0.0f, scaleMultiplier, 0.0f));
	baseModel = scale(baseModel, vec3(scaleMultiplier, scaleMultiplier, scaleMultiplier));
}

Cube::~Cube() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete shader;
}

void Cube::draw(mat4* view, mat4* projection) {
	glBindTexture(GL_TEXTURE_2D, texture);
	shader->Use();
	glBindVertexArray(VAO);
	drawCubes(view, projection);
	glBindVertexArray(0);
}

void Cube::drawCubes(mat4* view, mat4* projection) {
	GLfloat translateMultiplier = scaleMultiplier * 13;
	GLfloat zAxisFrontTranslate = 18.5f;
	GLfloat xAxisLeftTranslate = -24.0f;
	int numberOfBoxesInRow = 24;
	int numberOfBoxesInColumn = 18;

	for (int i = 1; i <= numberOfBoxesInRow; i++) {
		model = baseModel;
		model = translate(model, vec3(xAxisLeftTranslate + i*translateMultiplier, 0.0f, zAxisFrontTranslate));
		transformCoordinates(view, projection);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 1; i <= numberOfBoxesInColumn; i++) {
		model = baseModel;
		model = translate(model, vec3(xAxisLeftTranslate + translateMultiplier, 0.0f, zAxisFrontTranslate - i*translateMultiplier));
		transformCoordinates(view, projection);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 1; i <= numberOfBoxesInRow; i++) {
		model = baseModel;
		model = translate(model, vec3(xAxisLeftTranslate + i*translateMultiplier, 0.0f, zAxisFrontTranslate - (numberOfBoxesInColumn+1) * translateMultiplier));
		transformCoordinates(view, projection);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 1; i <= numberOfBoxesInColumn; i++) {
		model = baseModel;
		model = translate(model, vec3(xAxisLeftTranslate + numberOfBoxesInRow * translateMultiplier, 0.0f, zAxisFrontTranslate - i*translateMultiplier));
		transformCoordinates(view, projection);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}

void Cube::transformCoordinates(mat4* view, mat4* projection) {
	modelLoc = glGetUniformLocation(shader->Program, "model");
	viewLoc = glGetUniformLocation(shader->Program, "view");
	projectionLoc = glGetUniformLocation(shader->Program, "projection");
	GLint lightColorLoc = glGetUniformLocation(shader->Program, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(shader->Program, "lightPos");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(*projection));
	glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f);
	glUniform3f(lightPosLoc, 1.2f, 1.0f, 2.0f);
}

void Cube::generateBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &NORMALS);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NORMALS);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);

}

void Cube::interpretVertexData() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, NORMALS);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
}

void Cube::loadTexture() {
	int locWidth, locHeight;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image(CUBEIMAGEPATH, &locWidth, &locHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, locWidth, locHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}