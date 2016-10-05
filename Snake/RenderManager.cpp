#include "RenderManager.h"

static const char* GLFWINDOWWERROR = "Failed to create GLFW window\n";
static const char* GLEWINITERROR = "Failed to initialize GLEW\n";
const char* RenderManager::TITLE = "Snek";

bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_KP_8 || key == GLFW_KEY_KP_6 || key == GLFW_KEY_KP_5 || key == GLFW_KEY_KP_4)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
	if (key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_A || key == GLFW_KEY_D) {
		if (action == GLFW_PRESS && moveAllowed(key)) {
			keys[GLFW_KEY_W] = false;
			keys[GLFW_KEY_S] = false;
			keys[GLFW_KEY_A] = false;
			keys[GLFW_KEY_D] = false;
			keys[key] = true;
		}
	}
}

bool moveAllowed(int key) {
	if (key == GLFW_KEY_W && keys[GLFW_KEY_S]) return false;
	if (key == GLFW_KEY_S && keys[GLFW_KEY_W]) return false;
	if (key == GLFW_KEY_A && keys[GLFW_KEY_D]) return false;
	if (key == GLFW_KEY_D && keys[GLFW_KEY_A]) return false;
	if (key == GLFW_KEY_S && !keys[GLFW_KEY_W] && !keys[GLFW_KEY_S] && !keys[GLFW_KEY_A] && !keys[GLFW_KEY_D]) return false;
	return true;
}

RenderManager::RenderManager() {
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	moveSnake = false;
}

RenderManager::~RenderManager() {
	delete ground;
	delete space;
	delete snake;
	delete cubes;
	delete camera;
	glfwTerminate();
}

void RenderManager::initGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// version of OpenGL: max 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// version of OpenGL: min 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// doesn't allow to use instructions not from set version of OpenGL
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

bool RenderManager::createWindowObject() {
	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
	if (window == nullptr) {
		cout << GLFWINDOWWERROR;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}

void RenderManager::setKeyCallback() {
	glfwSetKeyCallback(window, key_callback);
}

bool RenderManager::initGLEW() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cout << GLEWINITERROR;
		return false;
	}
	return true;
}

void RenderManager::setViewport() {
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void RenderManager::setDepthBuffer() {
	glEnable(GL_DEPTH_TEST);
}

void RenderManager::setMatrixes() {
	camera = new Camera();
	projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
}

void RenderManager::createObjects() {
	space = new Space();
	ground = new Ground();
	snake = new Snake();
	cubes = new Cube();
	rabbit = new Model();
	//rabbit->loadOBJ(".\\OBJ\\Rabbit.obj");
}

void RenderManager::gameLoop() {
	while (!glfwWindowShouldClose(window)) {
		updateTime();
		glfwPollEvents();
		camera->move(keys, deltaTime);
		view = camera->getViewMatrix();
		if (moveSnake)
			snake->move(keys);
		clearBuffer();
		space->draw(&view, &projection);
		//ground->draw(&view, &projection);
		//cubes->draw(&view, &projection);
		snake->draw(&view, &projection);
		rabbit->draw(&view, &projection);
		glfwSwapBuffers(window);
	}
}

void RenderManager::clearBuffer() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void RenderManager::updateTime() {
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	moveSnake = nextPeriod(currentFrame);
	lastFrame = currentFrame;
}

bool RenderManager::nextPeriod(GLfloat currentFrame) {
	GLfloat previousPeriod, currentPeriod;

	previousPeriod = countPeriod(lastFrame);
	currentPeriod = countPeriod(currentFrame);
	return previousPeriod != currentPeriod;
}

GLfloat RenderManager::countPeriod(GLfloat frameTime) {
	GLfloat period;

	// rounds to 0.5
	//period = floor(frameTime);
	//if (round(period) != period)
	//	period += 0.5;

	// rounds to 0.1
	period = floor((frameTime * 10) + 0.5) / 10;

	return period;
}

