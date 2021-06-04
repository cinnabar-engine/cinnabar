#pragma once

#include <SDL.h>
#include <ce_event_handler.h>
#include <ce_math.h>

namespace ce {
	class Window {
	 public:
		Window(const char* title);
		~Window();

		void swapBuffers(), setMouseVisibility(bool enabled);

		SDL_GLContext getContext() { return m_context; };
		bool mouseVisible() { return m_mouse; };
		glm::vec2 getWindowSize();
		float getAspectRatio();

	 private:
		SDL_Window* m_window;
		SDL_GLContext m_context;

		bool m_mouse;
	};
}
