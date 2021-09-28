/** @example */

#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cinnabar-core/time.hpp>
#include <cinnabar-core/tpnt_log.h>
#include <cinnabar-render/cinnabar-render.hpp>

namespace demo {
	ce::Time* time = NULL;
	ce::Window* window = NULL;
	ce::RenderEngine* renderEngine = NULL;
	ce::Camera* camera = NULL;
	glm::vec3 cameraVelocity;
	double mouseSens = 0.05;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // TODO: get window class from callback instead of GLFWwindow
	switch (action) {
		case GLFW_PRESS: {
			double
				cameraSpeed = 2.5 * demo::time->getDeltaTime(),
				cameraRollSpeed = 3600.0 * demo::time->getDeltaTime();
			switch (key) {
				case GLFW_KEY_W:
					demo::cameraVelocity.z = cameraSpeed;
					break;
				case GLFW_KEY_S:
					demo::cameraVelocity.z = -cameraSpeed;
					break;
				case GLFW_KEY_D:
					demo::cameraVelocity.x = cameraSpeed;
					break;
				case GLFW_KEY_A:
					demo::cameraVelocity.x = -cameraSpeed;
					break;
				case GLFW_KEY_SPACE:
					demo::cameraVelocity.y = cameraSpeed;
					break;
				case GLFW_KEY_LEFT_SHIFT:
					demo::cameraVelocity.y = -cameraSpeed;
					break;

				case GLFW_KEY_Q:
					demo::camera->transform->roll(cameraRollSpeed);
					break;
				case GLFW_KEY_E:
					demo::camera->transform->roll(-cameraRollSpeed);
					break;

				case GLFW_KEY_ESCAPE:
					demo::window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					break;
			}
			break;
		}
		case GLFW_RELEASE: {
			switch (key) { // note that this movement is terrible and should absolutely not be used in a proper engine
				case GLFW_KEY_W:
				case GLFW_KEY_S:
					demo::cameraVelocity.z = 0;
					break;
				case GLFW_KEY_A:
				case GLFW_KEY_D:
					demo::cameraVelocity.x = 0;
					break;
				case GLFW_KEY_SPACE:
				case GLFW_KEY_LEFT_SHIFT:
					demo::cameraVelocity.y = 0;
					break;
			}
			break;
		}
	}
}
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) { // TODO: get window class from callback instead of GLFWwindow
	glfwSetCursorPos(demo::window->getWindow(), 0, 0);
	if (demo::window->getInputMode(GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
		return;
	glm::vec2 mouseDelta(xpos, ypos);
	mouseDelta *= -demo::mouseSens;
	demo::camera->transform->yaw(mouseDelta.x);
	demo::camera->transform->pitch(mouseDelta.y);
	demo::camera->transform->setPitch(std::clamp(demo::camera->transform->getPitch(), -90.0f, 90.0f));
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) { // TODO: get window class from callback instead of GLFWwindow
	if (action == GLFW_PRESS)
		if (demo::window->getInputMode(GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
			demo::window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPos(demo::window->getWindow(), 0, 0);
		}
}
void windowSizeCallback(GLFWwindow* window, int width, int height) { // TODO: get window class from callback instead of GLFWwindow
	demo::renderEngine->setFramebufferSize(demo::window->getFramebufferSize());
	demo::camera->projection = glm::perspective(glm::radians(75.0), (double)demo::window->getWindowAspectRatio(), 0.1, 100.0);
}

int main(int argc, char* argv[]) {
	demo::time = new ce::Time();

	demo::window = new ce::Window("Cinnabar");
	glfwSwapInterval(0); // disable vsync // TODO: window/renderEngine function for vsync
	double deltaTimeMin = 1.0 / 1000.0; // framerate cap

	demo::renderEngine = new ce::RenderEngine();
	demo::renderEngine->setFramebufferSize(demo::window->getFramebufferSize());

	demo::camera = new ce::Camera();
	demo::camera->projection = glm::perspective(glm::radians(75.0), (double)demo::window->getWindowAspectRatio(), 0.1, 100.0);
	demo::cameraVelocity = glm::vec3(0.0f);
	demo::camera->transform->setPosition(0.0f, 0.0f, 1.5f);


	ce::Mesh* blobMesh = new ce::Mesh("blob.obj");
	ce::Material* blobMaterial = new ce::Material("matcap");
	blobMaterial->textures[0] = new ce::Texture("matcap.png");
	ce::Transform* blobPos = new ce::Transform();
	blobPos->setScale(0.5f, 0.5f, 0.5f);

	ce::Mesh* environmentMesh = new ce::Mesh("environment.obj");
	ce::Material* environmentMaterial = new ce::Material("multitexture example", {}, 2);
	environmentMaterial->textures[0] = new ce::Texture("color.png");
	environmentMaterial->textures[1] = new ce::Texture("floor.png");
	ce::Transform* environmentPos = new ce::Transform();
	environmentPos->setPosition(0.0f, -1.0f, 0.0f);

	if (glfwRawMouseMotionSupported()) // TODO: make function for all these GLFW functions and figure out for multiple windows
		demo::window->setInputMode(GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetKeyCallback(demo::window->getWindow(), keyCallback);
	glfwSetCursorPosCallback(demo::window->getWindow(), cursorPositionCallback);
	glfwSetMouseButtonCallback(demo::window->getWindow(), mouseButtonCallback);
	glfwSetWindowSizeCallback(demo::window->getWindow(), windowSizeCallback);


	while (!glfwWindowShouldClose(demo::window->getWindow())) { // TODO: make function for this and figure out multiple window demo
		demo::time->update();
		std::cout << "fps: " << demo::time->getFPS() << std::endl;

		glfwPollEvents();

		// Rotate blob
		blobPos->roll(25.0 * demo::time->getDeltaTime());
		blobPos->yaw(50.0 * demo::time->getDeltaTime());
		blobPos->pitch(100.0 * demo::time->getDeltaTime());

		// Move camera
		glm::vec3
			cameraRight = demo::camera->transform->getRight(true, false, false),
			cameraUp = glm::vec3(0.0f, 1.0f, 0.0f),
			cameraFront = demo::camera->transform->getForward(true, false, false);
		demo::camera->transform->translate(
			(cameraRight * demo::cameraVelocity.x) +
			(cameraUp * demo::cameraVelocity.y) +
			(cameraFront * demo::cameraVelocity.z));

		// Render
		demo::renderEngine->clear(ce::COLOR_BUFFER_BIT | ce::DEPTH_BUFFER_BIT);
		demo::renderEngine->render(blobMesh, blobMaterial, blobPos, demo::camera);
		demo::renderEngine->render(environmentMesh, environmentMaterial, environmentPos, demo::camera);

		demo::window->swapBuffers();

		// error check
		// TODO: make this into some function
		/*while (true) {
			GLenum tmp = glGetError();
			if (tmp == GL_NO_ERROR)
				break;
			else
				LOG_ERROR("Uncaught GL error: 0x%04x", tmp);
		}*/

		// framerate cap
		demo::time->waitUntilDelta(deltaTimeMin);
	}
	delete blobMesh;
	blobMaterial->deleteContents();
	delete blobMaterial;
	delete blobPos;

	delete environmentMesh;
	environmentMaterial->deleteContents();
	delete environmentMaterial;
	delete environmentPos;

	delete demo::camera;

	delete demo::renderEngine;
	delete demo::window;

	delete demo::time;

	return 0;
}
