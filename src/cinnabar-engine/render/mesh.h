#pragma once

#include "shader.h"
#include "vertex.h"
#include <GL/glew.h>
#include "asset_manager.h"

namespace ce {
	class Mesh {
	 public:
		Mesh();
		Mesh(std::string filename)
			: Mesh(ce::assetManager::getMeshFile(filename)){};
		Mesh(MeshFile meshfile) { setMesh(meshfile); };

		~Mesh();

		void setMesh(std::string filename) { setMesh(ce::assetManager::getMeshFile(filename)); };
		void setMesh(MeshFile meshfile);

		void sendToShader(ce::Shader* shader, bool bind = true);

		size_t GetIndexCount() { return m_indexArraySize / sizeof(GLuint); };
		void bind(bool VBO = true, bool EBO = true), unbind(bool VBO = true, bool EBO = true);

	 private:
		GLsizeiptr m_vertArraySize, m_indexArraySize;
		GLuint m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* verts, GLuint* indices);
	};
}
