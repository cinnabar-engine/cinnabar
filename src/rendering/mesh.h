#pragma once

#include <GL/glew.h>
#include <managers/asset_manager.h>
#include "shader.h"

namespace ce {
	class Mesh {
	 public:
		Mesh();
		Mesh(std::string filename) : Mesh(ce::AssetManager::getMeshFile(filename)) {};
		Mesh(MeshFile file) { setMesh(file); };
		void setMesh(std::string filename) { setMesh(ce::AssetManager::getMeshFile(filename)); };
		void setMesh(MeshFile file);
		~Mesh();

		void sendToShader(ce::Shader* shader, bool bind = true);

		unsigned GetIndexCount() { return m_indexCount; };
		void bind(bool VBO = true, bool EBO = true), unbind(bool VBO = true, bool EBO = true);

	 private:
		GLsizeiptr m_vertCount, m_indexCount;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* verts, unsigned* indices);
	};
}
