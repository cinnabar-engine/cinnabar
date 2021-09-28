#include <cinnabar-render/window.hpp>

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cinnabar-core/tpnt_log.h>

ce::Window::Window(const char* title)
	: m_window(NULL) {

	if (!glfwInit()) { // TODO: init and terminate glfw seperate from windows
		LOG_ERROR("Error intialising GLGW");
		exit(1);
	}
	LOG_SUCCESS("GLFW has been initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(1280, 720, title, NULL, NULL);
	if (m_window == NULL) {
		LOG_ERROR("Failed to create GLFW window");
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(m_window); // TODO: i think each window comes with its own context, this should probably be a seperate function
}
ce::Window::~Window() {
	glfwDestroyWindow(m_window);
}

void ce::Window::swapBuffers() {
	glfwSwapBuffers(m_window);
}

glm::ivec2 ce::Window::getWindowSize() {
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	return glm::ivec2(w, h);
}
glm::ivec2 ce::Window::getFramebufferSize() {
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);
	return glm::ivec2(w, h);
}
double ce::Window::getWindowAspectRatio() {
	glm::ivec2 size = getWindowSize();
	return size.x / size.y;
}
double ce::Window::getFramebufferAspectRatio() {
	glm::ivec2 size = getFramebufferSize();
	return size.x / size.y;
}


void ce::Window::setInputMode(int mode, int value) {
	glfwSetInputMode(m_window, mode, value);
}

int ce::Window::getInputMode(int mode) {
	return glfwGetInputMode(m_window, mode);
}
