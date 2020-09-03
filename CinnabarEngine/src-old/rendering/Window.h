#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../core/Logger.h"
#include "ce_render_libs.h"
#include <GLFW/glfw3.h>

namespace ce {
	class Window {
	private:
		GLFWwindow* window;
		Logger* logger;
	public:
		Window(const char* title, int width, int height);
		~Window();

		glm::vec2 getSize();
		float getAspectRatio();
		int getKey(int key);
		bool isOpen();

		void update();
		void close();
		void forceClose();

	};
}
#endif // !_WINDOW_H_
