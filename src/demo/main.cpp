#include <iostream>

#include <glm/glm.hpp>

#include "render/cinnabar-render.hpp"
#include "core/time.hpp"
#include "core/tpnt_log.h"

int main(int argc, char* argv[]) {
	ce::Time* time = new ce::Time();

	ce::Window* window = new ce::Window("Cinnabar");
	SDL_GL_SetSwapInterval(0); // disable vsync
	double deltaTimeMin = 1.0 / 1000.0; // framerate cap

	ce::RenderEngine* renderEngine = new ce::RenderEngine();
	renderEngine->setSize(window->getWindowSize());


	ce::Mesh* blobMesh = new ce::Mesh("blob.obj");
	ce::Material* blobMaterial = new ce::Material("matcap");
	ce::Transform* blobPos = new ce::Transform();
	blobPos->setScale(0.5f, 0.5f, 0.5f);
	blobMaterial->setTexture("matcap.png");

	ce::Mesh* environmentMesh = new ce::Mesh("environment.obj");
	ce::Material* environmentGroundMaterial = new ce::Material("basic");
	ce::Material* environmentBuildingsMaterial = new ce::Material("basic");
	ce::Transform* environmentPos = new ce::Transform();
	environmentGroundMaterial->setTexture("floor.png");
	environmentBuildingsMaterial->setTexture("color.png");
	environmentPos->setPosition(0.0f, -1.0f, 0.0f);

	double mouseSens = 0.05;
	ce::Camera* camera = new ce::Camera();
	// TODO: Seperate so i can put in a player class later
	glm::vec3 cameraVelocity(0.0f);
	camera->transform->setPosition(0.0f, 0.0f, 1.5f);
	/*
	 * Game Loop
	 */
	SDL_Event event;
	bool running = true;
	while (running) {
		time->update();
		std::cout << "fps: " << time->getFPS() << std::endl;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_MOUSEMOTION: {
					if (ce::Window::mouseVisible())
						break;
					glm::vec2 mouseDelta(event.motion.xrel, event.motion.yrel);
					mouseDelta *= -mouseSens;
					camera->transform->yaw(mouseDelta.x);
					camera->transform->pitch(mouseDelta.y);
					camera->limitPitch();
					break;
				}
				case SDL_MOUSEBUTTONDOWN: {
					if (ce::Window::mouseVisible())
						ce::Window::setMouseVisibility(false);
					break;
				}
				case SDL_KEYDOWN: {
					double
						cameraSpeed = 2.5 * time->getDeltaTime(),
						cameraRollSpeed = 3600.0 * time->getDeltaTime();
					switch (event.key.keysym.sym) {
						case SDLK_w:
							cameraVelocity.z = cameraSpeed;
							break;
						case SDLK_s:
							cameraVelocity.z = -cameraSpeed;
							break;
						case SDLK_d:
							cameraVelocity.x = cameraSpeed;
							break;
						case SDLK_a:
							cameraVelocity.x = -cameraSpeed;
							break;
						case SDLK_SPACE:
							cameraVelocity.y = cameraSpeed;
							break;
						case SDLK_LSHIFT:
							cameraVelocity.y = -cameraSpeed;
							break;

						case SDLK_q:
							camera->transform->roll(cameraRollSpeed);
							break;
						case SDLK_e:
							camera->transform->roll(-cameraRollSpeed);
							break;

						case SDLK_ESCAPE:
							ce::Window::setMouseVisibility(true);
							break;
					}
					break;
				}
				case SDL_KEYUP: {
					switch (event.key.keysym.sym) { // note that this movement is terrible and should absolutely not be used in a proper engine
						case SDLK_w:
						case SDLK_s:
							cameraVelocity.z = 0;
							break;
						case SDLK_d:
						case SDLK_a:
							cameraVelocity.x = 0;
							break;
						case SDLK_SPACE:
						case SDLK_LSHIFT:
							cameraVelocity.y = 0;
							break;
					}
					break;
				}
				case SDL_QUIT: {
					running = false;
					break;
				}
				case SDL_WINDOWEVENT: {
					renderEngine->setSize(window->getWindowSize());
					break;
				}
			}
		}

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
		renderEngine->render(environmentMesh, environmentGroundMaterial, environmentPos, camera);

		window->swapBuffers();

		// framerate cap
		time->waitUntilDelta(deltaTimeMin);
	}
	delete blobMesh;
	delete blobMaterial;
	delete blobPos;

	delete environmentMesh;
	delete environmentGroundMaterial;
	delete environmentBuildingsMaterial;
	delete environmentPos;

	delete camera;

	delete renderEngine;
	delete window;

	return 0;
}
