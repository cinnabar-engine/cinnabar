#include <cinnabar-render/window.hpp>

#include <SDL.h>
#include <glm/glm.hpp>

#include <cinnabar-core/tpnt_log.h>

ce::Window::Window(const char* title)
	: m_window(NULL), m_context(NULL) {

	if (SDL_Init(SDL_INIT_VIDEO)) {
		LOG_ERROR("Error intialising SDL");
		exit(1);
	}
	LOG_SUCCESS("SDL has been initialized");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	m_window = SDL_CreateWindow(
		title, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 1280, 720,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (m_window == NULL) {
		LOG_ERROR("Failed to create SDL window");
		SDL_Quit();
		exit(1);
	}

	m_context = SDL_GL_CreateContext(m_window);
}
ce::Window::~Window() {
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
}

void ce::Window::swapBuffers() {
	SDL_GL_SwapWindow(m_window);
}

glm::vec2 ce::Window::getWindowSize() {
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	return glm::vec2(w, h);
}
float ce::Window::getAspectRatio() {
	glm::vec2 size = getWindowSize();
	return size.x / size.y;
}


void ce::Window::setMouseVisibility(bool enabled) {
	m_mouseVisible = enabled;
	SDL_SetRelativeMouseMode(enabled ? SDL_FALSE : SDL_TRUE);
}
