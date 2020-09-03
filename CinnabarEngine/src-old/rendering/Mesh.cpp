#include "Mesh.h"
#include <glad/glad.h>
#include "Vertex.h"
#include "Shader.h"
#include "../managers/ObjectManager.h"

ce::Mesh::Mesh(
	Vertex* vertexArray, const unsigned vertexCount,
	GLuint* indexArray, const unsigned indexCount
) :
	vertexCount(vertexCount),
	indexCount(indexCount),
	VAO(0),
	VBO(0),
	EBO(0)
{
	glGenVertexArrays(1, &VAO);
	bind();
	this->initVAO(vertexArray, indexArray);
	unbind();
}

ce::Mesh::~Mesh()
{
	destroy();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

ce::Logger* ce::Mesh::GetLogger()
{
	return Object::GetLogger("mesh");
}

void ce::Mesh::destroy()
{
}

void ce::Mesh::bind()
{
	glBindVertexArray(VAO);
}

void ce::Mesh::unbind()
{
	glBindVertexArray(0);
}

void ce::Mesh::sendToShader(ce::Shader* shader)
{
	shader->vertexAttribPointer("aPos", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	shader->vertexAttribPointer("aColor", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	shader->vertexAttribPointer("aTexCoord", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
}

void ce::Mesh::initVAO(Vertex* vertexArray, GLuint* indexArray)
{
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

	if (indexCount > 0) {
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexCount * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
	}
}