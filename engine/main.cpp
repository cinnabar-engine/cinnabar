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

/*
 * Vertices
 */
// clang-format off
ce::Vertex cubeVerts[] = {
	// Position                     Color                              Texture coord
	glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),// 0
	glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f),// 1
	glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f),// 2
	glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),// 3
	
	glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f),// 4
	glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),// 5
	glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),// 6
	glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f),// 7
};
ce::Vertex planeVerts[] = {
	// Position                     Color                              Texture coord
	glm::vec3(-1.0f,  0.0f, -1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),// 0
	glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),// 1
	glm::vec3( 1.0f,  0.0f, -1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),// 2
	glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f),// 3
};


/*
 * this is a cube
	  /1-3
	 / 0-2
	5-7 /
	4-6/
	viewed from the front, bottom face here is front
*/
// clang-format on
unsigned cubeVertCount = sizeof(cubeVerts) / sizeof(ce::Vertex);
unsigned planeVertCount = sizeof(planeVerts) / sizeof(ce::Vertex);
// 7<=>5
// clang-format off
GLuint cubeIndices[] = {
	0, 1, 2, 3, // back, right, front
	6, 7,
	4, 5,
	5, 7, // reset
	7, 3, 5, 1, // top, left, bottom
	4, 0,
	6, 2,
};

GLuint planeIndices[] = {
	0, 1, 2, 3,
};
// clang-format on
unsigned cubeIndexCount = sizeof(cubeIndices) / sizeof(GLuint);
unsigned planeIndexCount = sizeof(planeIndices) / sizeof(GLuint);

int main(int argc, char* argv[]) {
	LOG_INFO("Hello World");

	ce::ModuleManger* moduleManager = new ce::ModuleManger();

	ce::Time* time = new ce::Time();

	ce::Window* window = new ce::Window("Cinnabar");

	ce::RenderEngine* renderEngine = new ce::RenderEngine();
	renderEngine->setFOV(75.0f);
	renderEngine->setSize(window->getWindowSize());
	renderEngine->setClipRange(0.1f, 100.0f);

	// Cube
	ce::Mesh* cubeMesh = new ce::Mesh(cubeVerts, cubeVertCount, cubeIndices, cubeIndexCount);
	ce::Transform* cubePos = new ce::Transform();
	ce::Material* cubeMaterial = new ce::Material("basic");
	cubeMaterial->setTexture("uv-map.png");

	// Plane
	ce::Mesh* planeMesh = new ce::Mesh(planeVerts, planeIndexCount, planeIndices, planeVertCount);
	ce::Transform* planePos = new ce::Transform();
	ce::Material* planeMaterial = new ce::Material("vertColor");
	planePos->setPosition(0.0f, -1.0f, 0.0f);
	planePos->scale(10.0f, 1.0f, 10.0f);

	float mouseSens = 0.1f;
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
	int running = 1;
	while (running) {
		time->update();

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
					float cameraSpeed = 2.5f * time->getDeltaTime();
					if (event.key.keysym.sym == SDLK_w)
						cameraVelocity.z = cameraSpeed;
					else if (event.key.keysym.sym == SDLK_s)
						cameraVelocity.z = -cameraSpeed;
					if (event.key.keysym.sym == SDLK_a)
						cameraVelocity.x = -cameraSpeed;
					else if (event.key.keysym.sym == SDLK_d)
						cameraVelocity.x = cameraSpeed;
					if (event.key.keysym.sym == SDLK_SPACE)
						cameraVelocity.y = cameraSpeed;
					else if (event.key.keysym.sym == SDLK_LSHIFT)
						cameraVelocity.y = -cameraSpeed;
					if (event.key.keysym.sym == SDLK_ESCAPE)
						window->setMouseVisibility(true);
					break;
				}
				case SDL_KEYUP: {
					if ((event.key.keysym.sym == SDLK_w && cameraVelocity.z > 0) ||
						 (event.key.keysym.sym == SDLK_s && cameraVelocity.z < 0))
						cameraVelocity.z = 0;
					if ((event.key.keysym.sym == SDLK_a && cameraVelocity.x < 0) ||
						 (event.key.keysym.sym == SDLK_d && cameraVelocity.x > 0))
						cameraVelocity.x = 0;
					if ((event.key.keysym.sym == SDLK_SPACE && cameraVelocity.y > 0) ||
						 (event.key.keysym.sym == SDLK_LSHIFT && cameraVelocity.y < 0))
						cameraVelocity.y = 0;
					break;
				}
				case SDL_QUIT: {
					running = 0;
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
		cubePos->roll(25.0f * time->getDeltaTime());
		cubePos->yaw(50.0f * time->getDeltaTime());
		cubePos->pitch(100.0f * time->getDeltaTime());

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
		renderEngine->render();

		window->swapBuffers();
	}
	delete cubeMesh;
	delete cubeMaterial;
	delete cubePos;

	delete renderEngine;
	delete window;
	return 0;
}
