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
	typedef struct {
		ce::Window* window;
		ce::Camera* camera;
	} WinCam;
	std::vector<WinCam> wincams = {};
	ce::RenderEngine* renderEngine = NULL;
	ce::Transform* cameraTransform = NULL;
	glm::vec3 cameraVelocity;
	double mouseSens = 0.05;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void windowSizeCallback(GLFWwindow* window, int width, int height);

void makeWindow() {
	ce::Window* window = new ce::Window(("Cinnabar " + std::to_string(demo::wincams.size())).c_str());
	window->makeCurrent();
	demo::renderEngine->vsync(0);
	demo::renderEngine->setFramebufferSize(window->getFramebufferSize());	
	double deltaTimeMin = 1.0 / 1000.0; // framerate cap

	if (glfwRawMouseMotionSupported()) // TODO: make function for all these GLFW functions and figure out for multiple windows
		window->setInputMode(GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetKeyCallback(window->getWindow(), keyCallback);
	glfwSetCursorPosCallback(window->getWindow(), cursorPositionCallback);
	glfwSetMouseButtonCallback(window->getWindow(), mouseButtonCallback);
	glfwSetWindowSizeCallback(window->getWindow(), windowSizeCallback);

	ce::Camera* camera = new ce::Camera(demo::cameraTransform);
	camera->projection = glm::perspective(glm::radians(75.0), (double)window->getWindowAspectRatio(), 0.1, 100.0);

	demo::wincams.push_back({window, camera});
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
					demo::cameraTransform->roll(cameraRollSpeed);
					break;
				case GLFW_KEY_E:
					demo::cameraTransform->roll(-cameraRollSpeed);
					break;

				case GLFW_KEY_ESCAPE:
					demo::wincams[0].window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					break;

				case GLFW_KEY_EQUAL:
					makeWindow();
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
	glfwSetCursorPos(demo::wincams[0].window->getWindow(), 0, 0);
	if (demo::wincams[0].window->getInputMode(GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
		return;
	glm::vec2 mouseDelta(xpos, ypos);
	mouseDelta *= -demo::mouseSens;
	demo::wincams[0].camera->transform->yaw(mouseDelta.x);
	demo::wincams[0].camera->transform->pitch(mouseDelta.y);
	demo::wincams[0].camera->transform->setPitch(std::clamp(demo::wincams[0].camera->transform->getPitch(), -90.0f, 90.0f));
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) { // TODO: get window class from callback instead of GLFWwindow
	if (action == GLFW_PRESS)
		if (demo::wincams[0].window->getInputMode(GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
			demo::wincams[0].window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPos(demo::wincams[0].window->getWindow(), 0, 0);
		}
}
void windowSizeCallback(GLFWwindow* window, int width, int height) { // TODO: get window class from callback instead of GLFWwindow
	demo::wincams[0].window->makeCurrent();
	demo::renderEngine->setFramebufferSize(demo::wincams[0].window->getFramebufferSize());
	demo::wincams[0].camera->projection = glm::perspective(glm::radians(75.0), (double)demo::wincams[0].window->getWindowAspectRatio(), 0.1, 100.0);
}

int main(int argc, char* argv[]) {
	demo::time = new ce::Time();

	demo::renderEngine = new ce::RenderEngine();

	double deltaTimeMin = 1.0 / 1000.0; // framerate cap

	demo::cameraTransform = new ce::Transform();
	demo::cameraTransform->setPosition(0.0f, 0.0f, 1.5f);
	demo::cameraVelocity = glm::vec3(0.0f);

	makeWindow();

	demo::wincams[0].window->makeCurrent();
	// TODO: better system for setting which window meshes go to
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


	while (true) {
		for (std::vector<demo::WinCam>::iterator i = demo::wincams.begin(); i < demo::wincams.end(); i++)
			if (i->window->shouldClose()) {
				delete i->window;
				delete i->camera;
				demo::wincams.erase(i);
			}
		if (demo::wincams.size() == 0)
			goto close_program;

		demo::time->update();
		std::cout << "fps: " << demo::time->getFPS() << std::endl;

		ce::Window::pollEvents();

		// Rotate blob
		blobPos->roll(25.0 * demo::time->getDeltaTime());
		blobPos->yaw(50.0 * demo::time->getDeltaTime());
		blobPos->pitch(100.0 * demo::time->getDeltaTime());

		// Move camera
		glm::vec3
			cameraRight = demo::cameraTransform->getRight(true, false, false),
			cameraUp = glm::vec3(0.0f, 1.0f, 0.0f),
			cameraFront = demo::cameraTransform->getForward(true, false, false);
		demo::cameraTransform->translate(
			(cameraRight * demo::cameraVelocity.x) +
			(cameraUp * demo::cameraVelocity.y) +
			(cameraFront * demo::cameraVelocity.z));

		for (demo::WinCam wincam : demo::wincams) {
			// render
			wincam.window->makeCurrent();
			demo::renderEngine->clear(ce::COLOR_BUFFER_BIT | ce::DEPTH_BUFFER_BIT);
			demo::renderEngine->render(blobMesh, blobMaterial, blobPos, wincam.camera);
			demo::renderEngine->render(environmentMesh, environmentMaterial, environmentPos, wincam.camera);
			wincam.window->swapBuffers();

			// error check
			demo::renderEngine->errorCheck();
		}

		// framerate cap
		demo::time->waitUntilDelta(deltaTimeMin);
	}

	close_program:

	delete blobMesh;
	blobMaterial->deleteContents();
	delete blobMaterial;
	delete blobPos;

	delete environmentMesh;
	environmentMaterial->deleteContents();
	delete environmentMaterial;
	delete environmentPos;

	for (demo::WinCam wincam : demo::wincams) {
		delete wincam.window;
		delete wincam.camera;
	}
	demo::wincams.clear();

	delete demo::cameraTransform;
	delete demo::renderEngine;

	delete demo::time;

	return 0;
}
