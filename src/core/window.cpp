#include "window.h"

#include "tpnt_log.h"

ce::Window::Window(const char* title)
	: m_window(NULL), m_context(NULL), m_mouse(true) {

	/*
	 * Init SDL
	 */
	if (SDL_Init(SDL_INIT_VIDEO)) {
		LOG_ERROR("Error Intialising video");
		exit(1);
	}
	LOG_SUCCESS("SDL has been initialized");
	/*
	 * Window Creation
	 */
	m_window = SDL_CreateWindow("Cinnabar", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 1280, 720,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (m_window == NULL) {
		LOG_ERROR("Failed to create GLFW window");
		SDL_Quit();
		exit(-1);
	}
	// SDL_MaximizeWindow(window);
	/*int w,h;
	SDL_GetWindowSize(window,&w, &h);
	WINDOW = glm::vec2(w,h);*/
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	setMouseVisibility(true);

	m_context = SDL_GL_CreateContext(m_window);
}
ce::Window::~Window() {
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
void ce::Window::swapBuffers() {
	SDL_GL_SwapWindow(m_window);
}

glm::vec2 ce::Window::getWindowSize() {
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	return glm::vec2((float)w, (float)h);
}
float ce::Window::getAspectRatio() {
	glm::vec2 size = getWindowSize();
	return size.x / size.y;
}
void ce::Window::setMouseVisibility(bool enabled) {
	m_mouse = enabled;
	SDL_SetRelativeMouseMode(enabled ? SDL_FALSE : SDL_TRUE);
}
