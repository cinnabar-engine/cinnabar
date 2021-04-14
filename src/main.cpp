// Debugging
#include "core/tpnt_log.h"
#include <iostream>

// Core
#include "core/time.h"
#include "core/window.h"

// Assets
#include "managers/asset_manager.h"
#include "managers/module_manager.h"
#include "stb_image.h"

// Maths
#include "ce_math.h"
#include "math/transform.h"

// Rendering
#include "ce_render_fundementals.h"
#include "rendering/camera.h"
#include "rendering/material.h"
#include "rendering/render_engine.h"

int main(int argc, char* argv[]) {
	LOG_INFO("Hello World");

	ce::ModuleManager* moduleManager = new ce::ModuleManager();

	ce::Time* time = new ce::Time();

	ce::Window* window = new ce::Window("Cinnabar");
	SDL_GL_SetSwapInterval(0); // disable vsync
	double deltaTimeMin = 1.0 /*/ 1000.0*/; // framerate cap

	ce::RenderEngine* renderEngine = new ce::RenderEngine();
	renderEngine->setFOV(75.0f);
	renderEngine->setSize(window->getWindowSize());
	renderEngine->setClipRange(0.1f, 100.0f);

	// Cube
	ce::Mesh* cubeMesh = new ce::Mesh("missing.obj"); // TODO
	ce::Transform* cubePos = new ce::Transform();
	ce::Material* cubeMaterial = new ce::Material("null");
	cubeMaterial->setTexture("uv-map.png");

	// Plane
	ce::Mesh* planeMesh = new ce::Mesh(); // TODO
	ce::Transform* planePos = new ce::Transform();
	ce::Material* planeMaterial = new ce::Material("vertColor");
	planePos->setPosition(0.0f, -1.0f, 0.0f);
	planePos->scale(10.0f, 1.0f, 10.0f);
	
	ce::Mesh* blenderMesh = new ce::Mesh("hello.obj");
	ce::Transform* blenderPos = new ce::Transform();
	ce::Material* blenderMaterial = new ce::Material("vertColor");
	blenderPos->setPosition(0.0f, 5.0f, 0.0f);
	//blenderPos->scale(1.0f, 1.0f, 1.0f);

	double mouseSens = 0.05;
	ce::Camera* camera = new ce::Camera();
	// TODO: Seperate so i can put in a player class later
	glm::vec3 cameraVelocity(0.0f);
	camera->getTransform()->setPosition(0.0f, 0.0f, 1.5f);
	camera->getTransform()->setYaw(-90.0f);
	renderEngine->setCamera(camera);
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
					if (window->mouseVisible())
						break;
					glm::vec2 mouseDelta(event.motion.xrel, event.motion.yrel);
					mouseDelta *= mouseSens;
					camera->getTransform()->yaw(mouseDelta.x);
					camera->getTransform()->pitch(-mouseDelta.y);
					break;
				}
				case SDL_MOUSEBUTTONDOWN: {
					if (window->mouseVisible())
						window->setMouseVisibility(false);
					break;
				}
				case SDL_KEYDOWN: {
					double cameraSpeed = 2.5 * time->getDeltaTime();
					switch (event.key.keysym.sym) {
						case SDLK_w: cameraVelocity.z = cameraSpeed; break;
						case SDLK_s: cameraVelocity.z = -cameraSpeed; break;
						case SDLK_d: cameraVelocity.x = cameraSpeed; break;
						case SDLK_a: cameraVelocity.x = -cameraSpeed; break;
						case SDLK_SPACE: cameraVelocity.y = cameraSpeed; break;
						case SDLK_LSHIFT: cameraVelocity.y = -cameraSpeed; break;

						case SDLK_ESCAPE: window->setMouseVisibility(true); break;
					}
					break;
				}
				case SDL_KEYUP: {
					switch (event.key.keysym.sym) { // note that this movement is terrible and should absolutely not be used in a proper engine
						case SDLK_w: case SDLK_s: cameraVelocity.z = 0; break;
						case SDLK_d: case SDLK_a: cameraVelocity.x = 0; break;
						case SDLK_SPACE: case SDLK_LSHIFT: cameraVelocity.y = 0; break;
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

		moduleManager->tickModules(time->getDeltaTime());

		// Rotate cube
		cubePos->roll(25.0 * time->getDeltaTime());
		cubePos->yaw(50.0 * time->getDeltaTime());
		cubePos->pitch(100.0 * time->getDeltaTime());

		// Move camera
		glm::vec3
			cameraFront = camera->getTransform()->getForward(),
			cameraRight = camera->getRight(),
			cameraUp = ce::Transform::GetGlobalUp();
		camera->getTransform()->translate(
			(cameraFront * cameraVelocity.z) +
			(cameraRight * cameraVelocity.x) +
			(cameraUp * cameraVelocity.y));

		// Render
		renderEngine->registerCommand({cubePos, cubeMaterial, cubeMesh, cubeMesh->GetIndexCount()});
		renderEngine->registerCommand({planePos, planeMaterial, planeMesh, planeMesh->GetIndexCount()});
		renderEngine->registerCommand({blenderPos, blenderMaterial, blenderMesh, blenderMesh->GetIndexCount()});
		renderEngine->render();

		window->swapBuffers();

		// framerate cap
		time->waitUntilDelta(deltaTimeMin);
	}
	delete cubeMesh;
	delete cubeMaterial;
	delete cubePos;

	delete renderEngine;
	delete window;
	return 0;
}
