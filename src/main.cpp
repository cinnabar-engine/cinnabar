#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>

#include "rendering/ce_gl.h"
#include <SDL_log.h>

#include "stb_image.h"
#include "managers/asset_manager.h"
#include "rendering/vertex.h"

#include "rendering/shader.h"


int main(int argc, char* argv[]) {
	std::cout << "Learning OpenGL" << std::endl;
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
		1366,
		768,
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
	 * Load GLAD
	 */
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* OpenGL State */
	glEnable(GL_DEPTH_TEST);

	SDL_LogWarn(SDL_LOG_CATEGORY_ERROR,"test");

	/*
	 * Shaders
	 */
	ce::Shader* shader = new ce::Shader("basic");

	/*
	 * Vertices
	 */
	float vertices[] = {
	-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f
	};
	
	ce::Vertex v_vertices[] = {
	glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f,0.0f,0.0f,0.0f),  glm::vec2(0.0f, 0.0f),
	glm::vec3(0.5f, -0.5f, -0.5f),glm::vec4(1.0f,1.0f,0.0f,1.0f), glm::vec2(1.0f, 0.0f),
	glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(0.0f,1.0f,0.0f,1.0f), glm::vec2(1.0f, 1.0f),
	glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.0f,0.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f)
	};

	GLuint indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	std::cout << sizeof(v_vertices)/sizeof(ce::Vertex) <<"\n";



	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_vertices), v_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	///shader->vertexAttribPointer("aPos",3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	shader->vertexAttribPointer("aPos",3,GL_FLOAT,GL_FALSE,sizeof(ce::Vertex),(void*)(offsetof(ce::Vertex,position)));
	shader->vertexAttribPointer("aColor",4,GL_FLOAT,GL_FALSE,sizeof(ce::Vertex),(void*)(offsetof(ce::Vertex,color)));
	shader->vertexAttribPointer("aTexCoord",2, GL_FLOAT, GL_FALSE, sizeof(ce::Vertex), (void*)(offsetof(ce::Vertex,texCoord)));
	/*
	 * Textures
	 */
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//texture wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	// Load and generate texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("textures/wall.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//TextureBinding
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		//Shader
		shader->bind();

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// check and call events and swap the buffers
		SDL_GL_SwapWindow(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete shader;

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

