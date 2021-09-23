#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace ce {
	class Window {
	 public:
		Window(const char* title);
		~Window();

		void swapBuffers();

		GLFWwindow* getWindow() { return m_window; };

		glm::vec2 getWindowSize();
		float getAspectRatio();

		void setInputMode(int mode, int value);
		int getInputMode(int mode);

	 private:
		GLFWwindow* m_window;
	};
}
