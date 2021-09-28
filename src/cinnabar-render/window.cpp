#include <cinnabar-render/window.hpp>

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cinnabar-core/tpnt_log.h>

ce::Window::Window(const char* title, int width, int height)
	: m_window(NULL) {

	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (m_window == NULL) {
		LOG_ERROR("Failed to create GLFW window");
		glfwTerminate();
		exit(1);
	}

	makeCurrent();

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		LOG_ERROR("GLEW error: %s", (const char*)glewGetErrorString(err));
	}
	LOG_INFO("GLEW version: %s", (const char*)glewGetString(GLEW_VERSION));

	// OpenGL Setup
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
ce::Window::~Window() {
	glfwDestroyWindow(m_window);
}

void ce::Window::makeCurrent() {
	glfwMakeContextCurrent(m_window);
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
	return (double)size.x / (double)size.y;
}
double ce::Window::getFramebufferAspectRatio() {
	glm::ivec2 size = getFramebufferSize();
	return (double)size.x / (double)size.y;
}


void ce::Window::setInputMode(int mode, int value) {
	glfwSetInputMode(m_window, mode, value);
}

int ce::Window::getInputMode(int mode) {
	return glfwGetInputMode(m_window, mode);
}
