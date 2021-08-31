#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <cinnabar-render/asset_manager.hpp>

#include <cinnabar-render/shader.hpp>
#include <cinnabar-render/texture.hpp>

namespace ce {
	class Material {
	 public:
		Material(std::string name, std::map<std::string, std::string> options = {})
			: Material(new Shader(name, options)) {}
		Material(std::string vertName, std::string fragName, std::map<std::string, std::string> options = {})
			: Material(new Shader(vertName, fragName, options)) {}
		Material(std::string vertName, std::string geomName, std::string fragName, std::map<std::string, std::string> options = {})
			: Material(new Shader(vertName, geomName, fragName, options)) {}
		Material(Shader* shader);
		~Material();
		void update();

		void bind();
		void unbind();

		static GLint MAX_TEXTURES;

		Shader* shader;
		std::vector<Texture*> textures;
	};
}
