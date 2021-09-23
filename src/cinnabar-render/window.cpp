#include <cinnabar-render/window.hpp>

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cinnabar-core/tpnt_log.h>

ce::Window::Window(const char* title)
	: m_window(NULL) {

	if (!glfwInit()) {
		LOG_ERROR("Error intialising GLEW");
		exit(1);
	}
	LOG_SUCCESS("SDL has been initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(1280, 720, title, NULL, NULL);
	if (!m_window) {
		LOG_ERROR("Failed to create GLFW window");
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(m_window); // TODO: i think each window comes with its own context, this should probably be a seperate function

	// TODO: this somewhere
	//glfwWindowShouldClose(m_window);
}
ce::Window::~Window() {
	glfwDestroyWindow(m_window);
}

void ce::Window::swapBuffers() {
	glfwSwapBuffers(m_window);
}

glm::vec2 ce::Window::getWindowSize() {
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);
	return glm::vec2(w, h);
}
float ce::Window::getAspectRatio() {
	glm::vec2 size = getWindowSize();
	return size.x / size.y;
}


void ce::Window::setInputMode(int mode, int value) {
	glfwSetInputMode(m_window, mode, value);
}

int ce::Window::getInputMode(int mode) {
	return glfwGetInputMode(m_window, mode);
}
