#pragma once

#include <GL/glew.h>
#include <managers/asset_manager.h>

namespace ce {
	class Mesh {
	 private:
		unsigned m_vertexCount, m_indexCount;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO();
		void initMesh();

	 public:
		Mesh(const char* filename) : Mesh(ce::AssetManager::getMeshFile(filename)) {};
		Mesh(MeshFile file);
		~Mesh();

		void sendToShader(class Shader* shader, bool bind = true);

		unsigned GetIndexCount() { return m_indexCount; };
		void bind(), unbind();
	};
}
