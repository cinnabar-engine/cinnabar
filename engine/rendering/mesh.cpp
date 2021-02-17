#include "mesh.h"

#include "shader.h"
#include "vertex.h"

ce::Mesh::Mesh(Vertex* vertexArray, const unsigned vertexCount,
	GLuint* indexArray, const unsigned indexCount)
<<<<<<< HEAD
	: m_vertexCount(vertexCount), m_indexCount(indexCount), m_VAO(0), m_VBO(0), m_EBO(0) {
	glGenVertexArrays(1, &m_VAO);
	bind();
	this->initVAO(vertexArray, indexArray);
	unbind();
=======
	: vertexCount(vertexCount), indexCount(indexCount), VAO(0), VBO(0), EBO(0) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	initVAO(vertexArray, indexArray);
	glBindVertexArray(0);
>>>>>>> 569c3cf679420af32babc9d733f4d03bb18f0b8e
}
ce::Mesh::~Mesh() {
<<<<<<< HEAD
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &this->m_VBO);
	glDeleteBuffers(1, &this->m_EBO);
}

void ce::Mesh::bind() {
	glBindVertexArray(m_VAO);
=======
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void ce::Mesh::bind() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
>>>>>>> 569c3cf679420af32babc9d733f4d03bb18f0b8e
}
void ce::Mesh::unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ce::Mesh::sendToShader(ce::Shader* shader, bool bind) {
	if (bind) {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}
	shader->vertexAttribPointer("aPos", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	shader->vertexAttribPointer("aColor", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	shader->vertexAttribPointer("aTexCoord", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
	if (bind) {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void ce::Mesh::initVAO(Vertex* vertexArray, GLuint* indexArray) {
<<<<<<< HEAD
	glGenBuffers(1, &this->m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, this->m_vertexCount * sizeof(Vertex),
		vertexArray, GL_STATIC_DRAW);

	if (m_indexCount > 0) {
		glGenBuffers(1, &this->m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indexCount * sizeof(GLuint),
			indexArray, GL_STATIC_DRAW);
=======
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (indexCount > 0) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
>>>>>>> 569c3cf679420af32babc9d733f4d03bb18f0b8e
	}
}