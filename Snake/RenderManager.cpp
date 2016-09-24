#include "RenderManager.h"

static const char* GLFWINDOWWERROR = "Failed to create GLFW window\n";
static const char* GLEWINITERROR = "Failed to initialize GLEW\n";
static const char* TRIANGLEVERTEXSHADERPATH = ".\\Shaders\\triangle.vs";
static const char* TRIANGLEFRAGMENTSHADERPATH = ".\\Shaders\\triangle.frag";
static const char* IMAGEPATH = ".\\textures\\ground.png";
const char* RenderManager::TITLE = "Wonsz";


GLfloat Mainvertices[] = { // with texture
	0.5f, 0.5f, 0.0f,
	1.0f, 1.0f,  // Top Right

	0.5f, -0.5f, 0.0f,
	1.0f, 0.0f,  // Bottom Right

	-0.5f, -0.5f, 0.0f,
	0.0f, 0.0f,  // Bottom Left

	-0.5f, 0.5f, 0.0f,
	0.0f, 1.0f   // Top Left 
};

GLuint Mainindices[] = {  // Note that we start from 0!
	0, 1, 3,   // First Triangle
	1, 2, 3    // Second Triangle
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

RenderManager::RenderManager() {

}
RenderManager::~RenderManager() {
	delete ground;
	delete cubes;
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

void RenderManager::manageShaders() {
	//groundShader = Shader(TRIANGLEVERTEXSHADERPATH, TRIANGLEFRAGMENTSHADERPATH);
	//generateBuffer();
	//interpretVertexData();
}

void RenderManager::setMatrixes() {
	view = translate(view, vec3(0.0f, 0.0f, -5.0f));
	view = rotate(view, glm::radians(45.0f), vec3(1.0f, 0.0f, 0.0f));
	projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
}

void RenderManager::createObjects() {
	ground = new Ground();
	cubes = new Cube();
}

void RenderManager::releaseResources() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}

void RenderManager::gameLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		clearBuffer();
		ground->draw(&view, &projection);
		cubes->draw(&view, &projection);
		glfwSwapBuffers(window);
	}
}

void RenderManager::clearBuffer() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::generateBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Mainvertices), Mainvertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Mainindices), Mainindices, GL_STATIC_DRAW);
}

void RenderManager::interpretVertexData() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	loadTriangleTexture();
	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void RenderManager::drawTriangle() {
	glBindTexture(GL_TEXTURE_2D, triangleTexture);
	groundShader.Use();
	changeColor();
	mat4 transform;
	//transform = translate(transform, vec3(0.5f, -0.5f, 0.0f));
	//transform = rotate(transform, radians(95.0f), vec3(1.0f, 0.0f, 0.0f));
	//transform = rotate(transform, (GLfloat)glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
	//transform = scale(transform, vec3(2.0f, 2.0f, 2.0f));
	transformLoc = glGetUniformLocation(groundShader.Program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void RenderManager::changeColor() {
	timeValue = glfwGetTime();
	redValue = (sin(timeValue) / 2) + 0.5;
	vertexColorLocation = glGetUniformLocation(groundShader.Program, "ourColor");
	glUniform4f(vertexColorLocation, redValue, 0.0f, 0.2f, 1.0f);
}

void RenderManager::loadTriangleTexture() {
	int locWidth, locHeight;

	glGenTextures(1, &triangleTexture);
	glBindTexture(GL_TEXTURE_2D, triangleTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	image = SOIL_load_image(IMAGEPATH, &locWidth, &locHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, locWidth, locHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
