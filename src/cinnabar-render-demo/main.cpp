/** @example */

#include <iostream>
#include <unordered_map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cinnabar-core/time.hpp>
#include <cinnabar-core/tpnt_log.h>
#include <cinnabar-render/cinnabar-render.hpp>

namespace demo {
	ce::Time* time = NULL;
	std::unordered_map<ce::Window*, ce::Camera*> wincams = {};
	ce::RenderEngine* renderEngine = NULL;
	ce::Transform* cameraTransform = NULL;
	glm::vec3 cameraVelocity;
	double mouseSens = 0.05;
}

void keyCallback(ce::Window* window, int key, int scancode, int action, int mods);
void cursorPosCallback(ce::Window* window, double xpos, double ypos);
void mouseButtonCallback(ce::Window* window, int button, int action, int mods);
void windowSizeCallback(ce::Window* window, int width, int height);

std::unordered_map<ce::Window*, ce::Camera*>::iterator makeWincam() {
	ce::Window* window = new ce::Window(("Cinnabar " + std::to_string(demo::wincams.size())).c_str());
	window->makeCurrent();
	demo::renderEngine->vsync(0);
	demo::renderEngine->setFramebufferSize(window->getFramebufferSize());	
	double deltaTimeMin = 1.0 / 1000.0; // framerate cap

	if (glfwRawMouseMotionSupported()) // TODO: make Window function for this
		window->setInputMode(GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	window->setKeyCallback(keyCallback);
	window->setCursorPosCallback(cursorPosCallback);
	window->setMouseButtonCallback(mouseButtonCallback);
	window->setWindowSizeCallback(windowSizeCallback);

	ce::Camera* camera = new ce::Camera(demo::cameraTransform);
	camera->projection = glm::perspective(glm::radians(75.0), (double)window->getWindowAspectRatio(), 0.1, 100.0);

	return demo::wincams.insert({window, camera}).first;
}

void keyCallback(ce::Window* window, int key, int scancode, int action, int mods) {
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
					window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					break;

				case GLFW_KEY_EQUAL:
					makeWincam();
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
void cursorPosCallback(ce::Window* window, double xpos, double ypos) {
	if (window->getInputMode(GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
		return;
	glfwSetCursorPos(window->getWindow(), 0, 0);
	glm::vec2 mouseDelta(xpos, ypos);
	mouseDelta *= -demo::mouseSens;
	demo::cameraTransform->yaw(mouseDelta.x);
	demo::cameraTransform->pitch(mouseDelta.y);
	demo::cameraTransform->setPitch(std::clamp(demo::cameraTransform->getPitch(), -90.0f, 90.0f));
}
void mouseButtonCallback(ce::Window* window, int button, int action, int mods) {
	if (action == GLFW_PRESS)
		if (window->getInputMode(GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
			window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPos(window->getWindow(), 0, 0);
		}
}
void windowSizeCallback(ce::Window* window, int width, int height) {
	window->makeCurrent();
	demo::renderEngine->setFramebufferSize(window->getFramebufferSize());
	demo::wincams.find(window)->second->projection = glm::perspective(glm::radians(75.0), (double)window->getWindowAspectRatio(), 0.1, 100.0);
}

int main(int argc, char* argv[]) {
	demo::time = new ce::Time();

	demo::renderEngine = new ce::RenderEngine();

	double deltaTimeMin = 1.0 / 1000.0; // framerate cap

	demo::cameraTransform = new ce::Transform();
	demo::cameraTransform->setPosition(0.0f, 0.0f, 1.5f);
	demo::cameraVelocity = glm::vec3(0.0f);


	makeWincam()->first->makeCurrent();
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
		for (std::unordered_map<ce::Window*, ce::Camera*>::iterator it = demo::wincams.begin(); it != demo::wincams.end();)
			if (it->first->shouldClose()) {
				delete it->first;
				delete it->second;
				it = demo::wincams.erase(it);
			} else
				it++;
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

		for (std::pair<ce::Window*, ce::Camera*> wincam : demo::wincams) {
			// render
			wincam.first->makeCurrent();
			demo::renderEngine->clear(ce::COLOR_BUFFER_BIT | ce::DEPTH_BUFFER_BIT);
			demo::renderEngine->render(blobMesh, blobMaterial, blobPos, wincam.second);
			demo::renderEngine->render(environmentMesh, environmentMaterial, environmentPos, wincam.second);
			wincam.first->swapBuffers();

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

	for (std::pair<ce::Window*, ce::Camera*> wincam : demo::wincams) {
		delete wincam.first;
		delete wincam.second;
	}
	demo::wincams.clear();

	delete demo::cameraTransform;
	delete demo::renderEngine;

	delete demo::time;

	return 0;
}
