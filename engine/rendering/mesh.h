#pragma once

#include <ce_rendering.h>

#include "vertex.h"

namespace ce {
	class Mesh {
	 private:
		unsigned vertexCount, indexCount;
		GLuint VAO, VBO, EBO;

		void initVAO(Vertex* vertexArray, GLuint* indexArray);

	 public:
		Mesh(Vertex* vertexArray, const unsigned vertexCount,
			GLuint* indexArray = NULL, const unsigned indexCount = 0);
		~Mesh();
		void sendToShader(class Shader* shader, bool bind = true);

		unsigned GetIndexCount() { return indexCount; };
		void bind(), unbind();
	};
}