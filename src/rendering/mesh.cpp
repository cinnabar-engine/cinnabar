#include "mesh.h"

#include "shader.h"
#include <managers/asset_manager.h>\

ce::Mesh::Mesh() : m_VAO(0), m_VBO(0), m_EBO(0), m_vertNormalStart(0), m_vertUvStart(0), m_vertColorStart(0) {}

ce::Mesh::Mesh(ce::MeshFile mesh) {
	// all this is hardcoded and bad, find some way to make this not that
	m_vertNormalStart = (GLvoid*)(mesh.positions.size() * sizeof(glm::vec3));
	m_vertUvStart = (GLvoid*)(m_vertNormalStart + mesh.normals.size() * sizeof(glm::vec3));
	m_vertColorStart = (GLvoid*)(m_vertUvStart + mesh.uvs.size() * sizeof(glm::vec2));

	std::vector<void> vertData;
	std::move(mesh.positions.begin(), mesh.positions.end(), std::back_inserter(vertData));
	std::move(mesh.normals.begin(), mesh.normals.end(), std::back_inserter(vertData));
	std::move(mesh.uvs.begin(), mesh.uvs.end(), std::back_inserter(vertData));
	std::move(mesh.colors.begin(), mesh.colors.end(), std::back_inserter(vertData));

	m_vertDataLength = vertData.size();
	m_indexCount = mesh.indices.size();

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	initVAO(vertData.data(), mesh.indices.data());
	glBindVertexArray(0);
}

void ce::Mesh::initVAO(void* vertData, Vertex* indices) {
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertDataLength, vertData, GL_STATIC_DRAW);
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
	shader->vertexAttribPointer("aPos", 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	shader->vertexAttribPointer("aNormal", 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), m_vertNormalStart);
	shader->vertexAttribPointer("aUV", 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), m_vertUvStart);
	shader->vertexAttribPointer("aColor", 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), m_vertColorStart);
	if (bind) {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}