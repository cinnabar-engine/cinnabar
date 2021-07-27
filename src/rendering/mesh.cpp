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
	shader->vertexAttribPointer(ce::Shader::Attribute::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	shader->vertexAttribPointer(ce::Shader::Attribute::NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	shader->vertexAttribPointer(ce::Shader::Attribute::UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	shader->vertexAttribPointer(ce::Shader::Attribute::COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
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

ce::Meshfile ce::Mesh::createPlane(float width, float height, glm::vec2 origin) {
	float left = -width*origin.x,
	right = width+left,
	up = -height*origin.y,
	down = height+up;
  return {
    {
      
      {glm::vec3(left, up,0), glm::vec3(0, 1.f, 0), glm::vec2(0, 1.f)},
      {glm::vec3(right, up,0), glm::vec3(0, 1.f, 0), glm::vec2(1.f, 1.f)},
      {glm::vec3(left, down,0), glm::vec3(0, 1.f, 0), glm::vec2(0, 0)},
      {glm::vec3(right, down,0), glm::vec3(0, 1.f, 0), glm::vec2(1.f, 0)},
    },
    {
      0, 1, 2,
      2, 1, 3,
    },
  };
}
