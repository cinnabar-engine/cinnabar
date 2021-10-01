#include <cinnabar-render/window.hpp>

#include <unordered_map>

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cinnabar-core/tpnt_log.h>

std::unordered_map<GLFWwindow*, ce::Window*> s_windows;

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);

ce::Window::Window(const char* title, int width, int height, GLFWmonitor* monitor, ce::Window* share)
	: m_window(NULL) {

	m_window = glfwCreateWindow(width, height, title, monitor, share == NULL ? NULL : share->getWindow());
	if (m_window == NULL) {
		LOG_ERROR("Failed to create GLFW window");
		glfwTerminate();
		exit(1);
	}

	s_windows.insert({m_window, this});

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

void ce::Window::setKeyCallback(KeyCallback keyCallback) {
	m_keyCallback = keyCallback;
	glfwSetKeyCallback(m_window, (keyCallback ? glfwKeyCallback : NULL));
}
void ce::Window::setCursorPosCallback(CursorPosCallback cursorPosCallback) {
	m_cursorPosCallback = cursorPosCallback;
	glfwSetCursorPosCallback(m_window, cursorPosCallback ? glfwCursorPosCallback : NULL);
}
void ce::Window::setMouseButtonCallback(MouseButtonCallback mouseButtonCallback) {
	m_mouseButtonCallback = mouseButtonCallback;
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback ? glfwMouseButtonCallback : NULL);
}
void ce::Window::setWindowSizeCallback(WindowSizeCallback windowSizeCallback) {
	m_windowSizeCallback = windowSizeCallback;
	glfwSetWindowSizeCallback(m_window, windowSizeCallback ? glfwWindowSizeCallback : NULL);
}



void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	s_windows.find(window)->second->callKeyCallback(key, scancode, action, mods);
};
void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	s_windows.find(window)->second->callCursorPosCallback(xpos, ypos);
};
void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	s_windows.find(window)->second->callMouseButtonCallback(button, action, mods);
};
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height) {
	s_windows.find(window)->second->callWindowSizeCallback(width, height);
};