#include "mesh.h"

#include "shader.h"
#include "vertex.h"

ce::Mesh::Mesh(Vertex* vertexArray, const unsigned vertexCount,
	GLuint* indexArray, const unsigned indexCount)
	: m_vertexCount(vertexCount), m_indexCount(indexCount), m_VAO(0), m_VBO(0), m_EBO(0) {
	glGenVertexArrays(1, &m_VAO);
	bind();
	this->initVAO(vertexArray, indexArray);
	unbind();
}

ce::Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &this->m_VBO);
	glDeleteBuffers(1, &this->m_EBO);
}

void ce::Mesh::bind() {
	glBindVertexArray(m_VAO);
}

void ce::Mesh::unbind() {
	glBindVertexArray(0);
}

void ce::Mesh::sendToShader(ce::Shader* shader) {
	bind();
	shader->vertexAttribPointer("aPos", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, position));
	shader->vertexAttribPointer("aColor", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, color));
	shader->vertexAttribPointer("aTexCoord", 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
	unbind();
}

void ce::Mesh::initVAO(Vertex* vertexArray, GLuint* indexArray) {
	glGenBuffers(1, &this->m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, this->m_vertexCount * sizeof(Vertex),
		vertexArray, GL_STATIC_DRAW);

	if (m_indexCount > 0) {
		glGenBuffers(1, &this->m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indexCount * sizeof(GLuint),
			indexArray, GL_STATIC_DRAW);
	}
}
