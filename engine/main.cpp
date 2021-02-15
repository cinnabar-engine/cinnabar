//Debugging
#include <iostream>

//Assets
#include "stb_image.h"
#include "managers/asset_manager.h"

//Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Rendering
#include <GL/glew.h>
#include "rendering/vertex.h"
#include "rendering/shader.h"
#include "rendering/mesh.h"
#include "rendering/texture.h"

glm::vec2 WINDOW(1280.0f,720.0f);


/*
* Vertices
*/	
ce::Vertex vertices[] = {
	glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(1.0f,0.0f,0.0f,0.0f),  glm::vec2(1.0f, 1.0f),
	glm::vec3(0.5f, -0.5f, -0.5f),glm::vec4(1.0f,1.0f,0.0f,1.0f), glm::vec2(1.0f, 0.0f),
	glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.0f,1.0f,0.0f,1.0f), glm::vec2(0.0f, 0.0f),
	glm::vec3(-0.5f,  0.5f, -0.5), glm::vec4(0.0f,0.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f),
	
	/*glm::vec3(0.5f,  0.5f, 0.5f), glm::vec4(1.0f,0.0f,0.0f,0.0f),  glm::vec2(1.0f, 1.0f),
	glm::vec3(0.5f, -0.5f, 0.5f),glm::vec4(1.0f,1.0f,0.0f,1.0f), glm::vec2(1.0f, 0.0f),
	glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(0.0f,1.0f,0.0f,1.0f), glm::vec2(0.0f, 0.0f),
	glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec4(0.0f,0.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f)*/
};

/*  7-4
	9-8
  3-0
  2-1
*/
unsigned vertexCount = sizeof(vertices)/sizeof(ce::Vertex);

GLuint indices [] = {
	//F
	0, 1, 3,
	1, 2, 3,
	/*//U
	4,0,7,
	0,3,7,
	//L
	3,2,7,
	2,9,7,
	//R
	4,8,0,
	8,1,0,
	//D
	1,8,2,
	6,9,2,
	//B
	7,9,4,
	9,8,4*/
};
unsigned indexCount = sizeof(indices)/sizeof(GLuint);

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
		WINDOW.x,
		WINDOW.y,
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

	ce::Shader* shader = new ce::Shader("basic");
	
	ce::Mesh* mesh = new ce::Mesh(
		vertices,vertexCount,
		indices,indexCount
	);
	mesh->sendToShader(shader);
	ce::Texture* texture = new ce::Texture("uv-map.png");
	shader->setInt("fText",0);
	
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);  
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	
	
	glm::vec3
		up = glm::vec3(0.0f, 1.0f, 0.0f),
		cameraRight = glm::normalize(glm::cross(up, cameraDirection)),
		cameraUp = glm::cross(cameraDirection, cameraRight);
	
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		
	/*
	 * Game Loop
	 */
	SDL_Event event;
	int running = 1;
	while (running)
	{
		//Events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
				break;
			}
		}
		
		
		/* Render */
		glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		
		const float radius = 10.0f;
		float camX = sin(SDL_GetTicks()/1000) * radius;
		float camZ = cos(SDL_GetTicks()/1000) * radius;
		
		
		glm::mat4 model(1.0f);
		model = glm::rotate(model, glm::radians(10.0f)*SDL_GetTicks()/1000, glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));  
		shader->setMat4("uModel",model);
		shader->setMat4("uView",view);
		shader->setMat4("uProj",proj);
	
		
		texture->activate(0);
		shader->bind();
		mesh->bind();
		
		glDrawElements(GL_TRIANGLES,mesh->GetIndexCount(),GL_UNSIGNED_INT,0);
		
		mesh->unbind();
		shader->unbind();
		texture->unbind();

		// check and call events and swap the buffers
		SDL_GL_SwapWindow(window);
	}
	delete mesh;
	delete shader;
	delete texture;

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

