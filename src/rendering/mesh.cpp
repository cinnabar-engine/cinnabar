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

// TODO: the Mesh class shoudn't do ANY coverting, and shouldn't have to grab a Meshfile via a name. the Meshfile should just include the verts and indices.
void ce::Mesh::setMesh(Meshfile meshfile) {
	std::vector<Vertex> verts;
	std::vector<GLuint> indices;

	for (int v = 0; v < meshfile.vertices.size(); v++) {
		Vertex vertex;

		vertex.position = meshfile.vertices[v];
		vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex.uv = glm::vec2(0.0f, 0.0f);

		verts.push_back(vertex);
	}

	for (int f = 0; f < meshfile.faces.size(); f++) {
		auto face = meshfile.faces[f];
		for (int p = 0; p < face.size(); p++) {
			auto point = face[p];
			auto vertex = verts[point.index];
			indices.push_back((GLuint)point.index);

			if (meshfile.normals.size() > point.normal) {
				// TODO: normals
				meshfile.normals[point.normal];
			}
			if (meshfile.uv.size() > point.uv)
				vertex.uv = meshfile.uv[point.uv];

			verts[point.index] = vertex;
		}
	}

	setMesh(verts.data(), verts.size(), indices.data(), indices.size());
}

void ce::Mesh::setMesh(Vertex* verts, size_t vertCount, GLuint* indices, size_t indexCount) {
	m_vertArraySize = vertCount * sizeof(Vertex);
	m_indexArraySize = indexCount * sizeof(GLuint);
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	initVAO(verts, indices);
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
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO); // TODO: what cases is each bind needed? what needs to be avalible as options?
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
