#include "mesh.h"

#include "shader.h"
#include "vertex.h"
#include <managers/asset_manager.h>

void ce::Mesh::initMesh(Vertex* vertexArray, const unsigned vertexCount,
	GLuint* indexArray, const unsigned indexCount) {
	m_vertexCount = vertexCount;
	m_indexCount = indexCount;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	initVAO(vertexArray, indexArray);
	glBindVertexArray(0);
}

ce::Mesh::Mesh()
	: m_VAO(0), m_VBO(0), m_EBO(0) {}

ce::Mesh::Mesh(Vertex* vertexArray, const unsigned vertexCount, GLuint* indexArray, const unsigned indexCount)
	: Mesh() {
	initMesh(vertexArray, vertexCount, indexArray, indexCount);
}

ce::Mesh::Mesh(const char* name) {
	MeshFile file = ce::AssetManager::getMeshFile(name);

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	for (int v = 0; v < file.vertices.size(); v++) {
		Vertex vertex;

		vertex.position = file.vertices[v];
		vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex.uv = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (int f = 0; f < file.faces.size(); f++) {
		auto face = file.faces[f];
		for (int p = 0; p < face.size(); p++) {
			auto point = face[p];
			auto vertex = vertices[point.index];
			indices.push_back((GLuint)point.index);

			if (file.normals.size() > point.normal) {
				//TODO: normals
				file.normals[point.normal];
			}
			if (file.uv.size() > point.uv)
				vertex.uv = file.uv[point.uv];

			vertices[point.index] = vertex;
		}
	}

	initMesh(&vertices[0], vertices.size(), &indices[0], indices.size());
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
	shader->vertexAttribPointer("aPos", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	shader->vertexAttribPointer("aColor", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	shader->vertexAttribPointer("aTexCoord", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	if (bind) {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void ce::Mesh::initVAO(Vertex* vertexArray, GLuint* indexArray) {
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (m_indexCount > 0) {
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
