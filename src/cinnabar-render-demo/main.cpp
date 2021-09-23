/** @example */

#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cinnabar-core/time.hpp>
#include <cinnabar-core/tpnt_log.h>
#include <cinnabar-render/cinnabar-render.hpp>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // TODO: get window class from callback instead of GLFWwindow
	switch (action) {
		case GLFW_PRESS: {
			double
				cameraSpeed = 2.5 * time->getDeltaTime(),
				cameraRollSpeed = 3600.0 * time->getDeltaTime();
			switch (key) {
				case GLFW_KEY_W:
					cameraVelocity.z = cameraSpeed;
					break;
				case GLFW_KEY_S:
					cameraVelocity.z = -cameraSpeed;
					break;
				case GLFW_KEY_A:
					cameraVelocity.x = cameraSpeed;
					break;
				case GLFW_KEY_D:
					cameraVelocity.x = -cameraSpeed;
					break;
				case GLFW_KEY_SPACE:
					cameraVelocity.y = cameraSpeed;
					break;
				case GLFW_KEY_LEFT_SHIFT:
					cameraVelocity.y = -cameraSpeed;
					break;

				case GLFW_KEY_Q:
					camera->transform->roll(cameraRollSpeed);
					break;
				case GLFW_KEY_E:
					camera->transform->roll(-cameraRollSpeed);
					break;

				case GLFW_KEY_ESCAPE:
					window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					break;
			}
			break;
		}
		case GLFW_RELEASE: {
			switch (key) { // note that this movement is terrible and should absolutely not be used in a proper engine
				case GLFW_KEY_W:
				case GLFW_KEY_S:
					cameraVelocity.z = 0;
					break;
				case GLFW_KEY_A:
				case GLFW_KEY_D:
					cameraVelocity.x = 0;
					break;
				case GLFW_KEY_SPACE:
				case GLFW_KEY_LEFT_SHIFT:
					cameraVelocity.y = 0;
					break;
			}
			break;
		}
	}
}
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) { // TODO: get window class from callback instead of GLFWwindow
	if (window->getInputMode(GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
		return;
	glm::vec2 mouseDelta(xpos, ypos);
	mouseDelta *= -mouseSens;
	camera->transform->yaw(mouseDelta.x);
	camera->transform->pitch(mouseDelta.y);
	camera->transform->setPitch(std::clamp(camera->transform->getPitch(), -90.0f, 90.0f));
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) { // TODO: get window class from callback instead of GLFWwindow
	if (action == GLFW_PRESS)
		if (window->getInputMode(GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
			window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void windowSizeCallback(GLFWwindow* window, int width, int height) { // TODO: get window class from callback instead of GLFWwindow
	//renderEngine->setSize(window->getWindowSize());
	{
		int w, h;
		glfwGetFramebufferSize(m_window, &w, &h);
		renderEngine->setSize(w, h);
	}
	camera->projection = glm::perspective(glm::radians(75.0), (double)window->getAspectRatio(), 0.1, 100.0);
}

int main(int argc, char* argv[]) {
	ce::Time* time = new ce::Time();

	ce::Window* window = new ce::Window("Cinnabar");
	glfwSwapInterval(0); // disable vsync // TODO: static window function for vsync
	double deltaTimeMin = 1.0 / 1000.0; // framerate cap

	ce::RenderEngine* renderEngine = new ce::RenderEngine();
	renderEngine->setSize(window->getWindowSize());


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

	double mouseSens = 0.05;
	ce::Camera* camera = new ce::Camera();
	camera->projection = glm::perspective(glm::radians(75.0), (double)window->getAspectRatio(), 0.1, 100.0);
	glm::vec3 cameraVelocity(0.0f);
	camera->transform->setPosition(0.0f, 0.0f, 1.5f);

	if (glfwRawMouseMotionSupported()) // TODO: make function for all these GLFW functions and figure out for multiple windows
		window->setInputMode(GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetKeyCallback(window->getWindow(), keyCallback);
	glfwSetCursorPosCallback(window->getWindow(), cursorPositionCallback);
	glfwSetMouseButtonCallback(window->getWindow(), mouseButtonCallback);
	glfwSetWindowSizeCallback(window->getWindow(), windowSizeCallback);


	while (!glfwWindowShouldClose(window->getWindow())) { // TODO: make function for this and figure out multiple window demo
		time->update();
		std::cout << "fps: " << time->getFPS() << std::endl;

		glfwPollEvents();

		// Rotate blob
		blobPos->roll(25.0 * time->getDeltaTime());
		blobPos->yaw(50.0 * time->getDeltaTime());
		blobPos->pitch(100.0 * time->getDeltaTime());

		// Move camera
		glm::vec3
			cameraRight = camera->transform->getRight(true, false, false),
			cameraUp = glm::vec3(0.0f, 1.0f, 0.0f),
			cameraFront = camera->transform->getForward(true, false, false);
		camera->transform->translate(
			(cameraRight * cameraVelocity.x) +
			(cameraUp * cameraVelocity.y) +
			(cameraFront * cameraVelocity.z));

		// Render
		renderEngine->clear();
		renderEngine->render(blobMesh, blobMaterial, blobPos, camera);
		renderEngine->render(environmentMesh, environmentMaterial, environmentPos, camera);

		window->swapBuffers();

		// error check
		// TODO: make this into some function
		while (true) {
			GLenum tmp = glGetError();
			if (tmp == GL_NO_ERROR)
				break;
			else
				LOG_ERROR("Uncaught GL error: 0x%04x", tmp);
		}

		// framerate cap
		time->waitUntilDelta(deltaTimeMin);
	}
	delete blobMesh;
	blobMaterial->deleteContents();
	delete blobMaterial;
	delete blobPos;

	delete environmentMesh;
	environmentMaterial->deleteContents();
	delete environmentMaterial;
	delete environmentPos;

	delete camera;

	delete renderEngine;
	delete window;

	return 0;
}
