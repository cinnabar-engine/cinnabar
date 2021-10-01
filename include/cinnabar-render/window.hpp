#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace ce {
	class Window {
	 public:
		typedef void (*KeyCallback)(Window* window, int key, int scancode, int action, int mods);
		typedef void (*CursorPosCallback)(Window* window, double xpos, double ypos);
		typedef void (*MouseButtonCallback)(Window* window, int button, int action, int mods);
		typedef void (*WindowSizeCallback)(Window* window, int width, int height);

		Window(const char* title, int width = 640, int height = 480);
		~Window();

		void makeCurrent();

		void swapBuffers();

		GLFWwindow* getWindow() { return m_window; };

		glm::ivec2 getWindowSize();
		glm::ivec2 getFramebufferSize();
		double getWindowAspectRatio();
		double getFramebufferAspectRatio();

		bool shouldClose() { return glfwWindowShouldClose(getWindow()); }

		static void pollEvents() { glfwPollEvents(); };

		void setInputMode(int mode, int value);
		int getInputMode(int mode);

		void setKeyCallback(KeyCallback keyCallback);
		void setCursorPosCallback(CursorPosCallback cursorPosCallback);
		void setMouseButtonCallback(MouseButtonCallback mouseButtonCallback);
		void setWindowSizeCallback(WindowSizeCallback windowSizeCallback);

		void callKeyCallback(int key, int scancode, int action, int mods) { m_keyCallback(this, key, scancode, action, mods); };
		void callCursorPosCallback(double xpos, double ypos) { m_cursorPosCallback(this, xpos, ypos); };
		void callMouseButtonCallback(int button, int action, int mods) { m_mouseButtonCallback(this, button, action, mods); };
		void callWindowSizeCallback(int width, int height) { m_windowSizeCallback(this, width, height); };

	 private:
		GLFWwindow* m_window;

		KeyCallback m_keyCallback;
		CursorPosCallback m_cursorPosCallback;
		MouseButtonCallback m_mouseButtonCallback;
		WindowSizeCallback m_windowSizeCallback;
	};
}
