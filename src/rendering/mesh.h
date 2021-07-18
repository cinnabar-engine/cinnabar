#pragma once

#include <GL/glew.h>

#include "vertex.h"

namespace ce {
	class Mesh {
	 public:
		Mesh(Vertex* vertexArray, const unsigned vertexCount,
			GLuint* indexArray = NULL, const unsigned cubeIndexCount = 0);
		~Mesh();
		Mesh(const char* name);
		void sendToShader(class Shader* shader, bool bind = true);

		unsigned GetIndexCount() { return m_indexCount; };
		void bind(), unbind();

	 private:
		unsigned m_vertexCount, m_indexCount;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* vertexArray, GLuint* indexArray);
		void initMesh(Vertex* vertexArray, const unsigned vertexCount,
			GLuint* indexArray, const unsigned indexCount);

		Mesh();
	};
}
