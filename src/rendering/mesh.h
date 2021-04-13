#pragma once

#include <GL/glew.h>
#include <managers/asset_manager.h>

namespace ce {
	class Mesh {
	 public:
		Mesh();
		Mesh(const char* filename) : Mesh(ce::AssetManager::getMeshFile(filename)) {};
		Mesh(MeshFile file) { setMesh(file); };
		void setMesh(const char* filename) { setMesh(ce::AssetManager::getMeshFile(filename)); };
		void setMesh(MeshFile file);
		~Mesh();

		void sendToShader(class Shader* shader, bool bind = true);

		unsigned GetIndexCount() { return m_indexCount; };
		void bind(), unbind();

	 private:
		GLsizeiptr m_vertCount, m_indexCount;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* verts, unsigned* indices);
	};
}
