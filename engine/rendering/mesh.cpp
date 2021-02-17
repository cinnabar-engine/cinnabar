#include "mesh.h"
#include "iostream"

#include "shader.h"
#include "vertex.h"

ce::Mesh::Mesh(Vertex* vertexArray, const unsigned vertexCount,
	GLuint* indexArray, const unsigned indexCount)
	: vertexCount(vertexCount), indexCount(indexCount), VAO(0), VBO(0), EBO(0) {
	glGenVertexArrays(1, &VAO);
	std::cout << "created VAO" << VAO << std::endl;
	glBindVertexArray(VAO);
	initVAO(vertexArray, indexArray);
	glBindVertexArray(0);
}

ce::Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
/*
void ce::Mesh::bind() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void ce::Mesh::unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
*/
void ce::Mesh::sendToShader(ce::Shader* shader) {
	glBindVertexArray(VAO);
	shader->vertexAttribPointer("aPos", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	shader->vertexAttribPointer("aColor", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	shader->vertexAttribPointer("aTexCoord", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
	glBindVertexArray(0);
}

void ce::Mesh::initVAO(Vertex* vertexArray, GLuint* indexArray) {
	glGenBuffers(1, &VBO);
	std::cout << "created VBO" << VBO << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (indexCount > 0) {
		glGenBuffers(1, &EBO);
		std::cout << "created EBO" << EBO << std::endl;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}