#pragma once

#include <GL/glew.h>
#include <managers/asset_manager.h>

namespace ce {
	class Mesh {
	 private:
		unsigned m_vertDataLength, m_indexCount;
		GLuint m_VAO, m_VBO, m_EBO;
		GLvoid *m_vertNormalStart, *m_vertUvStart, *m_vertColorStart;

		void initVAO(void* vertData, Vertex* indices);

	 public:
		Mesh();
		Mesh(const char* filename) : Mesh(ce::AssetManager::getMeshFile(filename)) {};
		Mesh(MeshFile file);
		~Mesh();

		void sendToShader(class Shader* shader, bool bind = true);

		unsigned GetIndexCount() { return m_indexCount; };
		void bind(), unbind();
	};
}
