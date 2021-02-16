#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <ce_math.h>
#include <ce_rendering.h>
#include <ce_event_handler.h>

namespace ce {
	class Window {
	private:
		SDL_Window* m_window;
		SDL_GLContext m_context;
		
		bool m_mouse;
	public:
		Window(const char* title);
		~Window();
		
		void
			swapBuffers(),
			setMouseVisibility(bool enabled);
		
		SDL_GLContext getContext() { return m_context;};
		bool mouseVisible(){return m_mouse;};
		glm::vec2 getWindowSize();
		float getAspectRatio();
	};
}

#endif // _WINDOW_H_
