#include "Snake.h"


Snake::Snake() : Model((char*)SNAKEOBJPATH) {
	scaleMultiplier = 3.8;
	baseModel = scale(baseModel, vec3(1.0, 1.0, 1.0)*scaleMultiplier);
	baseModel = translate(baseModel, vec3(0.0f, 0.0f, 0.0f));
	initiateSnakeElements();
	hit = false;
	end = false;
	
}

Snake::~Snake() {
}

void Snake::draw(mat4* view, mat4* projection) {
	initiateDrawing();
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
		snakePos.push_back(vec3(0.0f, 0.0f, -10 -i * ORIGINALSIDELENGTH));
	}
}

void Snake::drawSnakeElements(mat4* view, mat4* projection) {
	for (int i = 0; i < (int)snakeElements.size(); i++) {
		model = snakeElements[i];
		transformCoordinates(view, projection);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
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
	if ((snakePos[0].x > /*34*/35 || snakePos[0].x < /*-32*/-35)) { end = 1; return true; }
	if ((snakePos[0].z > /*36*/27 || snakePos[0].z < /*-16*/-27)) { end = 1; return true; }
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