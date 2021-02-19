#pragma once

#include <ce_rendering.h>

#include "vertex.h"

namespace ce {
	class Mesh {
	 private:
		unsigned m_vertexCount, m_indexCount;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* vertexArray, GLuint* indexArray);

	 public:
		Mesh(Vertex* vertexArray, const unsigned vertexCount,
			GLuint* indexArray = NULL, const unsigned cubeIndexCount = 0);
		~Mesh();
		 Mesh(const char* name);
		void sendToShader(class Shader* shader, bool bind = true);

		unsigned GetIndexCount() { return m_indexCount; };
		void bind(), unbind();
	};
}
