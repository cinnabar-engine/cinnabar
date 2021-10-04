#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <cinnabar-render/asset_manager.hpp>
#include <cinnabar-render/shader.hpp>
#include <cinnabar-render/texture.hpp>

namespace ce {
	class Material {
	 public:
		Material(std::string name, std::map<std::string, std::string> options = {}, size_t textureCount = 1)
			: Material(new Shader(name, options), textureCount) {}
		Material(std::string vertName, std::string fragName, std::map<std::string, std::string> options = {}, size_t textureCount = 1)
			: Material(new Shader(vertName, fragName, options), textureCount) {}
		Material(std::string vertName, std::string geomName, std::string fragName, std::map<std::string, std::string> options = {}, size_t textureCount = 1)
			: Material(new Shader(vertName, geomName, fragName, options), textureCount) {}
		Material(Shader* shader, size_t textureCount = 1);
		void deleteContents();
		void deleteTextures();
		void update();

		void bind();
		void unbind();

		Shader* shader;
		std::vector<Texture*> textures;
	};
}
