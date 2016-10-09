#include "Snake.h"

GLfloat snakeVertices[] = { // with texture
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

GLuint snakeIndices[] {
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

Snake::Snake() {
	shader = new Shader(SNAKEVERTEXSHADERPATH, SNAKEFRAGMENTSHADERPATH);
	generateBuffer();
	interpretVertexData();
	loadTexture();
	initiateSnakeElements();
	hit = false;
	end = false;
}

Snake::~Snake() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete shader;
}

void Snake::draw(mat4* view, mat4* projection) {
	glBindTexture(GL_TEXTURE_2D, texture);
	shader->Use();
	glBindVertexArray(VAO);
	drawSnakeElements(view, projection);
	glBindVertexArray(0);
}

void Snake::move(bool* keys) {
	if (keys[GLFW_KEY_W])
		processKeyboardInput(W);
	if (keys[GLFW_KEY_S])
		processKeyboardInput(S);
	if (keys[GLFW_KEY_A])
		processKeyboardInput(A);
	if (keys[GLFW_KEY_D])
		processKeyboardInput(D);
}

void Snake::processKeyboardInput(SnakeMovement direction) {
	int head = 0;

	hit ? addElement() : moveTail();
	
	vec3 diff = vec3(0.0f, 0.0f, 0.0f);

	if (direction == W)
		diff = vec3(0.0f, 0.0f, ORIGINALSIDELENGTH);
	if (direction == S)
		diff = vec3(0.0f, 0.0f, -ORIGINALSIDELENGTH);
	if (direction == A)
		diff = vec3(ORIGINALSIDELENGTH, 0.0f, 0.0f);
	if (direction == D)
		diff = vec3(-ORIGINALSIDELENGTH, 0.0f, 0.0f);
	snakeElements[head] = translate(snakeElements[head], diff);
	snakePos[0] += diff;
	//cout << snakePos[0].x << " " << snakePos[0].z << endl;
	checkMove();
}

void Snake::moveTail() {
	for (int i = (int)snakeElements.size() - 1; i > 0; i--){
		snakeElements[i] = snakeElements[i - 1];
		snakePos[i] = snakePos[i - 1];
	}
}

void Snake::initiateSnakeElements() {
	int numberOfStartElements = 3;
	GLfloat scaleMultiplier = 0.1f;

	headPos = vec3(0.0f, scaleMultiplier, -1.0f);
	baseModel = translate(baseModel, vec3(0.0f, scaleMultiplier, -1.0f));
	baseModel = scale(baseModel, vec3(scaleMultiplier, scaleMultiplier, scaleMultiplier));
	
	for (int i = 0; i < numberOfStartElements; i++) {
		snakeElements.push_back(baseModel);
		snakeElements[i] = translate(snakeElements[i], vec3(0.0f, 0.0f, -i * ORIGINALSIDELENGTH));
		snakePos.push_back(vec3(0.0f, 0.0f, -i * ORIGINALSIDELENGTH));
	}
}

void Snake::drawSnakeElements(mat4* view, mat4* projection) {
	for (int i = 0; i < (int)snakeElements.size(); i++) {
		model = snakeElements[i];
		transformCoordinates(view, projection);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}

void Snake::transformCoordinates(mat4* view, mat4* projection) {
	modelLoc = glGetUniformLocation(shader->Program, "model");
	viewLoc = glGetUniformLocation(shader->Program, "view");
	projectionLoc = glGetUniformLocation(shader->Program, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(*projection));
}

void Snake::generateBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(snakeVertices), snakeVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(snakeIndices), snakeIndices, GL_STATIC_DRAW);
}

void Snake::interpretVertexData() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

}

void Snake::loadTexture() {
	int locWidth, locHeight;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image(SNAKEIMAGEPATH, &locWidth, &locHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, locWidth, locHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Snake::addElement(){
	int newSize = (int)snakeElements.size() + 1;
	snakeElements.resize(newSize);
	snakePos.resize(newSize);
	for (int i = newSize - 2; i > 0; i--){
		snakeElements[i] = snakeElements[i - 1];
		snakePos[i] = snakePos[i - 1];
	}
	snakeElements[newSize-1] = snakeElements[newSize - 2];
	snakePos[newSize - 1] = snakePos[newSize - 2];
	hit = false;
	return newSize;
}

vec2 Snake::getHeadPos(){
	return vec2(snakePos[0].x, snakePos[0].z);
}

void Snake::setHit(bool val){
	hit = val;
}

bool Snake::getEnd(){
	return end;
}

bool Snake::checkMove(){
	cout << snakePos[0].x << " " << snakePos[0].z <<endl;
	if ((snakePos[0].x > 32 || snakePos[0].x < -30)) { end = 1; return true; }
	if ((snakePos[0].z > 35 || snakePos[0].z < -18)) { end = 1; return true; }
	for (int i = 4; i < snakePos.size(); i++){
		if (snakePos[0] == snakePos[i]){
			end = 1;
			return true;
		}
	}
	return false;
}

bool Snake::validPos(vec2 pos){
	for (int i = 0; i < snakeElements.size(); i++){
		if (pos.x == snakePos[i].x || pos.y == snakePos[i].z){
			return false;
		}
	}
	return true;	
}