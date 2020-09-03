#include "rendering/Window.h"
#include "rendering/Vertex.h"
#include "managers/AssetManager.h"

#include "rendering/Shader.h"
#include "rendering/Mesh.h"
#include "rendering/Texture.h"

ce::Vertex vertices[] = {
	//Position						//Color							//TexCoord
	glm::vec3(-1.0f,1.0f,0.0f),		glm::vec4(1.0f,0.0f,0.0f,1.0f),	glm::vec2(0.0f,0.0f),
	glm::vec3(-1.0f,-1.0f,0.0f),	glm::vec4(0.0f,1.0f,0.0f,1.0f),	glm::vec2(0.0f,1.0f),
	glm::vec3(1.0f,-1.0f,0.0f),		glm::vec4(0.0f,0.0f,1.0f,1.0f),	glm::vec2(1.0f,1.0f),
	glm::vec3(1.0f,1.0f,0.0f),		glm::vec4(1.0f,1.0f,0.0f,1.0f),	glm::vec2(1.0f,0.0f)
};
unsigned vertexCount = sizeof(vertices) / sizeof(ce::Vertex);

GLuint indices[] = {
	0,1,2,
	0,2,3
};
unsigned indexCount = sizeof(indices) / sizeof(GLuint);

int main() {
	ce::Logger logger("main");

	logger.Log("Hello World");

	ce::Window* window = new ce::Window("Cinnabar Engine Alpha Created by Tumble", 640, 480);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ce::Shader* shader = new ce::Shader(ASSETMAN->getShaderFile("basic"));
	ce::Texture* texture = new ce::Texture(ASSETMAN->getTextureFile("wall.png"), GL_TEXTURE_2D);
	ce::Mesh* mesh = new ce::Mesh(vertices, vertexCount, indices, indexCount);

	while (window->isOpen()) {

		if (window->getKey(GLFW_KEY_ESCAPE)==GLFW_PRESS) {
			window->close();
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//shader->setInt("material.diffuseTex", 1);
		mesh->sendToShader(shader);
		shader->bind();
		texture->activate(1);
		mesh->bind();

		glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, 0);

		shader->unbind();
		texture->unbind();
		mesh->unbind();
		window->update();
	}
	delete window;
}