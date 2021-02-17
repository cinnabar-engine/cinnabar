#pragma once

#include <ce_rendering.h>

#include "vertex.h"

namespace ce {
	class Mesh {
	 private:
		unsigned vertexCount, indexCount;
		

		void initVAO(Vertex* vertexArray, GLuint* indexArray);

	 public:
	 GLuint VAO, VBO, EBO;
		Mesh(Vertex* vertexArray, const unsigned vertexCount,
			GLuint* indexArray = NULL, const unsigned indexCount = 0);
		~Mesh();
		void sendToShader(class Shader* shader);

		unsigned GetIndexCount() { return indexCount; };
		//void bind(), unbind();
	};
}