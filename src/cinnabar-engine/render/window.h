#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

namespace ce {
	class Window {
	 public:
		Window(const char* title);
		~Window();

		void swapBuffers();

		SDL_Window* getWindow() { return m_window; };
		SDL_GLContext getContext() { return m_context; };

		glm::vec2 getWindowSize();
		float getAspectRatio();

		static bool mouseVisible() { return m_mouseVisible; };
		static void setMouseVisibility(bool enabled);

	 private:
		SDL_Window* m_window;
		SDL_GLContext m_context;

		static inline bool m_mouseVisible = true;
	};
}
