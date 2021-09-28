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

		glm::ivec2 getWindowSize(); // TODO: make sure window/framebuffer functions are being used correctly (otherwise os scaling will break)
		glm::ivec2 getFramebufferSize();
		double getWindowAspectRatio();
		double getFramebufferAspectRatio();

		void setInputMode(int mode, int value);
		int getInputMode(int mode);

	 private:
		GLFWwindow* m_window;
	};
}
