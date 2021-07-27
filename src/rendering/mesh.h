#pragma once

#include "shader.h"
#include "vertex.h"
#include <GL/glew.h>
#include <managers/asset_manager.h>

namespace ce {
	class Mesh {
	 public:
		Mesh();
		Mesh(std::string filename)
			: Mesh(ce::AssetManager::getMeshfile(filename)){};
		Mesh(Meshfile meshfile) { setMesh(meshfile); };

		~Mesh();

		void setMesh(std::string filename) { setMesh(ce::AssetManager::getMeshfile(filename)); };
		void setMesh(Meshfile meshfile);

		void sendToShader(ce::Shader* shader, bool bind = true);

		size_t GetIndexCount() { return m_indexArraySize / sizeof(GLuint); };
		void bind(bool VBO = true, bool EBO = true), unbind(bool VBO = true, bool EBO = true);
		
		static ce::Meshfile createPlane(float width = 1.0f, float height = 1.0f, glm::vec2 origin = glm::vec2(.5f,.5f));

	 private:
		GLsizeiptr m_vertArraySize, m_indexArraySize;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* verts, GLuint* indices);
	};
}
