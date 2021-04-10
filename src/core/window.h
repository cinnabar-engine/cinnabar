#pragma once

#include <ce_event_handler.h>
#include <ce_math.h>
#include <SDL.h>

namespace ce {
	class Window {
	 private:
		SDL_Window* m_window;
		SDL_GLContext m_context;

		bool m_mouse;

	 public:
		Window(const char* title);
		~Window();

		void swapBuffers(), setMouseVisibility(bool enabled);

		SDL_GLContext getContext() { return m_context; };
		bool mouseVisible() { return m_mouse; };
		glm::vec2 getWindowSize();
		float getAspectRatio();
	};
}