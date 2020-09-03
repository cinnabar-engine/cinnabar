#include "Window.h"

void updateSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

ce::Window::Window(const char* title, int width, int height):
logger(new Logger("window"))
{
	if (!glfwInit())
	{
		logger->Error("failed to load GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	logger->Info("Loaded GLFW");
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwSetErrorCallback(error_callback);

	//Create Window and Context
	this->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!this->window) {
		logger->Error("failed to create window");
	}
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	/*
	 * Load GLAD
	 */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		logger->Error("Failed to initialize GLAD");
		exit(-1);
	}
	glViewport(0, 0, width, height);
	logger->Info("Created Window");

	glfwSetFramebufferSizeCallback(window, updateSizeCallback);

	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

ce::Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	delete this->logger;
}

void ce::Window::update()
{
	glfwSwapBuffers(this->window);
	glFlush();
	glfwPollEvents();
}

glm::vec2 ce::Window::getSize()
{
	glm::ivec2 size;
	glfwGetFramebufferSize(this->window, &size.x, &size.y);
	return size;
}

float ce::Window::getAspectRatio()
{
	return getSize().x / getSize().y;
}

bool ce::Window::isOpen()
{
	return !glfwWindowShouldClose(this->window);
}

void ce::Window::close() {
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int ce::Window::getKey(int key) {
	return glfwGetKey(window, key);
}

void ce::Window::forceClose()
{
	if (this->window) glfwDestroyWindow(this->window);
	glfwTerminate();
}
