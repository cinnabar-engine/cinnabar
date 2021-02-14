#include <iostream>

#include "stb_image.h"
#include "managers/asset_manager.h"
#include "rendering/rendering_engine.h"
#include "rendering/vertex.h"

#include "rendering/shader.h"
#include "rendering/mesh.h"
#include "rendering/texture.h"

/*
* Vertices
*/	
ce::Vertex vertices[] = {
	glm::vec3(-1.0f, -0.5f, -0.5f), glm::vec4(1.0f,0.0f,0.0f,0.0f),  glm::vec2(0.0f, 0.0f),
	glm::vec3(0.5f, -1.0f, -0.5f),glm::vec4(1.0f,1.0f,0.0f,1.0f), glm::vec2(1.0f, 0.0f),
	glm::vec3(1.0f,  0.5f, -0.5f), glm::vec4(0.0f,1.0f,0.0f,1.0f), glm::vec2(1.0f, 1.0f),
	glm::vec3(-0.5f,  1.0f, -0.5f), glm::vec4(0.0f,0.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f)
};

const unsigned vertexCount = sizeof(vertices)/sizeof(ce::Vertex);

GLuint indices [] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};
const unsigned indexCount = sizeof(indices)/sizeof(GLuint);

int main(int argc, char* argv[]) {
	std::cout << "Hello World!" << std::endl;
	/*
	 * Init SDL
	 */
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Error Intialising video\n";
		exit(1);
	}
	std::cout << "SDL has been initialized\n";
	/*
	 * Window Creation
	 */
	SDL_Window* window = SDL_CreateWindow(
		"Cinnabar",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		SDL_WINDOW_OPENGL
	);
	if(window==NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		SDL_Quit();
		return -1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext mainContext = SDL_GL_CreateContext(window);

	/*
	 * GLEW
	 */
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	
	ce::RenderingEngine* renderingEngine = new ce::RenderingEngine();

	ce::Shader* shader = new ce::Shader("basic");
	ce::Mesh* mesh = new ce::Mesh(
		vertices,vertexCount,
		indices,indexCount
	);
	ce::Texture* texture = new ce::Texture("uv-map.png");
	
	/*
	 * Game Loop
	 */
	SDL_Event event;
	int running = 1;
	while (running)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
				break;
			}
		}

		/* Render */
		renderingEngine->loadCommand({shader,mesh,texture,mesh->GetIndexCount()});
		renderingEngine->render();

		// check and call events and swap the buffers
		SDL_GL_SwapWindow(window);
	}
	delete mesh;
	delete shader;

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

