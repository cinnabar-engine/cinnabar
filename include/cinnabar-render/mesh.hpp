#pragma once

#include <cinnabar-render/asset_manager.hpp>
#include <cinnabar-render/shader.hpp>
#include <cinnabar-render/vertex.hpp>

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

		size_t GetIndexCount() { return m_indexArraySize / sizeof(glm::uint32); };
		void bind(), unbind();

		MeshFormat format;

	 private:
		size_t m_vertArraySize, m_indexArraySize;
		glm::uint32 m_VAO, m_VBO, m_EBO;

		void initVAO(Vertex* verts, glm::uint32_t* indices);
	};
}
