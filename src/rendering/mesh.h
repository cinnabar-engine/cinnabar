#pragma once

#include "shader.h"
#include "vertex.h"
#include <GL/glew.h>

namespace ce {
	class Mesh {
	 public:
		Mesh();
		Mesh(Vertex* verts, size_t vertCount, GLuint* indices = NULL, size_t indexCount = 0);
		Mesh(const char* name);
		~Mesh();

		void setMesh(Vertex* verts, size_t vertCount, GLuint* indices = NULL, size_t indexCount = 0);

		void sendToShader(ce::Shader* shader, bool bind = true);

		size_t GetIndexCount() { return m_indexArraySize / sizeof(GLuint); };
		void bind(bool VBO = true, bool EBO = true), unbind(bool VBO = true, bool EBO = true);

	 private:
		GLsizeiptr m_vertArraySize, m_indexArraySize;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* verts, GLuint* indices);
	};
}
