//Debugging
#include <iostream>
#include <core/tpnt_log.h>

//Core
#include "core/window.h"
#include "core/time.h"

//Assets
#include "stb_image.h"
#include "managers/asset_manager.h"

//Maths
#include <ce_math.h>
#include "math/transform.h"

//Rendering
#include "ce_render_fundementals.h"

/*
* Vertices
*/	
ce::Vertex vertices[] = {
	glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(0.0f,0.0f,0.0f,0.0f),  glm::vec2(1.0f, 1.0f),//0
	glm::vec3(0.5f, -0.5f, -0.5f),glm::vec4(0.0f,0.0f,1.0f,1.0f), glm::vec2(1.0f, 0.0f),//1
	glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.0f,1.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f),//2
	glm::vec3(-0.5f,  0.5f, -0.5), glm::vec4(0.0f,1.0f,0.0f,1.0f), glm::vec2(0.0f, 1.0f),//3
	
	glm::vec3(0.5f,  0.5f, 0.5f), glm::vec4(1.0f,0.0f,0.0f,0.0f),  glm::vec2(1.0f, 1.0f),//4
	glm::vec3(0.5f, -0.5f, 0.5f),glm::vec4(1.0f,1.0f,0.0f,1.0f), glm::vec2(1.0f, 0.0f),//5
	glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f,0.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f),//6
	glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f)//7
};

/*  7-4
	6-5
  3-0
  2-1
*/
unsigned vertexCount = sizeof(vertices)/sizeof(ce::Vertex);
//7<=>5
GLuint indices [] = {
	//F
	0, 1, 3,
	1, 2, 3,
	//U
	4,0,7,
	0,3,7,
	//L
	3,2,7,
	2,6,7,
	//R
	4,5,0,
	5,1,0,
	//D
	1,5,2,
	5,6,2,
	//B
	7,6,4,
	6,5,4
};
unsigned indexCount = sizeof(indices)/sizeof(GLuint);

int main(int argc, char* argv[]) {
	LOG_INFO("Hello World");
	
	ce::Window* window = new ce::Window("Cinnabar");

	/*
	 * GLEW
	 */
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		LOG_ERROR((const char*)glewGetErrorString(err));
	}
	LOG_INFO("Status: Using GLEW "+ (const char*)glewGetString(GLEW_VERSION));
	
	//OpenGL Setup
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Time
	ce::Time* time = new ce::Time();
	
	ce::Transform transform;
	ce::Shader* shader = new ce::Shader("basic");
	ce::Mesh* mesh = new ce::Mesh(
		vertices,vertexCount,
		indices,indexCount
	);
	mesh->sendToShader(shader);
	ce::Texture* texture = new ce::Texture("uv-map.png");
	shader->setInt("uTex",0);
	float
		mouseSensitivity = 0.1f,
		cameraPitch = 0.0f,
		cameraYaw = -90.0f;
	
	glm::vec3
		cameraPos(0.0f, 0.0f, 3.0f),
		cameraFront(0.0f,0.0f,-1.0f),
		cameraUp(0.0f,1.0f,0.0f),
		cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	
		
	/*
	 * Game Loop
	 */
	SDL_Event event;
	int running = 1;
	while (running)
	{
		//Time
		time->update();
		
		//Events
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_MOUSEMOTION:
				{
					if(window->mouseVisible())break;
					glm::vec2 mouseDelta(event.motion.xrel,event.motion.yrel);
					mouseDelta *= mouseSensitivity;
					cameraYaw += mouseDelta.x;
					cameraPitch -= mouseDelta.y;
					if(cameraPitch>89.0f)
						cameraPitch = 89.0f;
					if(cameraPitch<-89.0f)
						cameraPitch = -89.0f;
					
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
					if(window->mouseVisible()){
						window->setMouseVisibility(false);
					}
					break;
				case SDL_KEYDOWN:
				{
					float cameraSpeed = 2.5f*time->getDeltaTime(); // adjust accordingly
					if (event.key.keysym.sym == SDLK_w)
						cameraPos += cameraFront * cameraSpeed;
					if (event.key.keysym.sym ==  SDLK_s)
						cameraPos -= cameraFront * cameraSpeed;
					if (event.key.keysym.sym == SDLK_a)
						cameraPos -= cameraRight * cameraSpeed;
					if (event.key.keysym.sym == SDLK_d)
						cameraPos += cameraRight * cameraSpeed;
					if(event.key.keysym.sym == SDLK_ESCAPE){
						window->setMouseVisibility(true);
					}
					break;
				}
				case SDL_QUIT:
				{
					running = 0;
					break;
				}
				case SDL_WINDOWEVENT:
				{
					glm::vec2 size = window->getWindowSize();
					glViewport(0, 0, size.x,size.y);
					break;
				}
			}
		}
		
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), window->getAspectRatio(), 0.1f, 100.0f);
		shader->setMat4("transform.proj",proj);
		
		// Transform
		transform.roll(25.0f*time->getDeltaTime());
		transform.yaw(50.0f*time->getDeltaTime());
		transform.pitch(100.0f*time->getDeltaTime());
		transform.saveToShader(shader);
		
		// Camera
		glm::vec3
			cameraDirection(
				cos(glm::radians(cameraYaw))*cos(glm::radians(cameraPitch)),
				sin(glm::radians(cameraPitch)),
				sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch))
			);
		cameraFront = glm::normalize(cameraDirection);
		cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
		glm::mat4 view = glm::lookAt(cameraPos,cameraPos + cameraFront,cameraUp);
		shader->setMat4("transform.view",view);
		
		/* Render */
		glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		texture->activate(0);
		shader->bind();
		mesh->bind();
		
		glDrawElements(GL_TRIANGLES,mesh->GetIndexCount(),GL_UNSIGNED_INT,0);
		
		mesh->unbind();
		shader->unbind();
		texture->unbind();

		window->swapBuffers();
	}
	delete mesh;
	delete shader;
	delete texture;
	
	delete window;
	return 0;
}

