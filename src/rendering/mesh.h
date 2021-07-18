#pragma once

#include "shader.h"
#include "vertex.h"
#include <GL/glew.h>

namespace ce {
	class Mesh {
	 public:
		Mesh();
		Mesh(std::string filename)
			: Mesh() { setMesh(filename); };
		Mesh(Meshfile meshfile)
			: Mesh() { setMesh(meshfile); };
		Mesh(Vertex* verts, size_t vertCount, GLuint* indices = NULL, size_t indexCount = 0)
			: Mesh() { setMesh(verts, vertCount, indices, indexCount); }

		~Mesh();

		void
			setMesh(std::string filename),
			setMesh(ce::Meshfile meshfile),
			setMesh(Vertex*verts, size_t vertCount, GLuint*indices = NULL, size_t indexCount = 0);

		void sendToShader(ce::Shader* shader, bool bind = true);

		size_t GetIndexCount() { return m_indexArraySize / sizeof(GLuint); };
		void bind(bool VBO = true, bool EBO = true), unbind(bool VBO = true, bool EBO = true);

	 private:
		GLsizeiptr m_vertArraySize, m_indexArraySize;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* verts, GLuint* indices);
	};
}
