#include "mesh.h"

#include "shader.h"
#include <managers/asset_manager.h>

ce::Mesh::Mesh() : m_VAO(0), m_VBO(0), m_EBO(0) {}

ce::Mesh::Mesh(ce::Meshfile mesh) {
	m_vertDataLength = mesh..size();
	m_indexCount = mesh.indices.size();
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	initVAO(&mesh.[0], &mesh.indices[0]);
	glBindVertexArray(0);
}

void ce::Mesh::initVAO(Vertex* verts, GLuint* indices) {
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertDataLength * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (m_indexCount > 0) {
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(Vertex), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

ce::Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void ce::Mesh::bind() {
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}
void ce::Mesh::unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ce::Mesh::sendToShader(ce::Shader* shader, bool bind) {
	if (bind) {
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	}
	shader->vertexAttribPointer("aPos", 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)offsetof(glm::vec3, position));
	shader->vertexAttribPointer("aNormal", 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)offsetof(Vertex, normal));
	shader->vertexAttribPointer("aUV", 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)offsetof(Vertex, uv));
	shader->vertexAttribPointer("aColor", 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)offsetof(Vertex, color));
	if (bind) {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}