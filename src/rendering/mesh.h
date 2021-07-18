#pragma once

#include "shader.h"
#include <GL/glew.h>
#include <managers/asset_manager.h>

namespace ce {
	class Mesh {
	 public:
		Mesh();
		Mesh(std::string filename)
			: Mesh(ce::AssetManager::getMeshfile(filename)){};
		Mesh(Meshfile file) { setMesh(file); };

		~Mesh();

		void setMesh(std::string filename) { setMesh(ce::AssetManager::getMeshfile(filename)); };
		void setMesh(Meshfile file);

		void sendToShader(ce::Shader* shader, bool bind = true);

		unsigned GetIndexCount() { return m_indexCount; };
		void bind(bool VBO = true, bool EBO = true), unbind(bool VBO = true, bool EBO = true);

	 private:
		GLsizeiptr m_vertCount, m_indexCount;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* verts, unsigned* indices);
	};
}
