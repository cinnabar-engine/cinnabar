#include "mesh.h"
#include "shader.h"
#include "vertex.h"

ce::Mesh::Mesh()
	: m_VAO(0), m_VBO(0), m_EBO(0), m_vertArraySize(0), m_indexArraySize(0) {}

ce::Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void ce::Mesh::setMesh(ce::Meshfile meshfile) {
	m_vertArraySize = meshfile.verts.size() * sizeof(Vertex);
	m_indexArraySize = meshfile.indices.size() * sizeof(GLuint);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	initVAO(meshfile.verts.data(), meshfile.indices.data());
	glBindVertexArray(0);
}

void ce::Mesh::sendToShader(ce::Shader* shader, bool bind) {
	if (bind)
		this->bind(true, false);
	shader->vertexAttribPointer("aPosition", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	shader->vertexAttribPointer("aNormal", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	shader->vertexAttribPointer("aUV", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	shader->vertexAttribPointer("aColor", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	if (bind)
		this->unbind(true, false);
}

void ce::Mesh::bind(bool VBO, bool EBO) {
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	if (EBO)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}
void ce::Mesh::unbind(bool VBO, bool EBO) {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (EBO)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ce::Mesh::initVAO(Vertex* verts, GLuint* indices) {
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertArraySize, verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (m_indexArraySize > 0) {
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexArraySize, indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
