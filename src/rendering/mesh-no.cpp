#include "mesh-no.h"

#include "vertex.h"
#include "shader.h"

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
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void ce::Mesh::bind()
{
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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