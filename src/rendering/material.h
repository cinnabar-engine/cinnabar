#pragma once

#include <glm/glm.hpp>

#include <ce_render_fundementals.h>
#include <managers/asset_manager.h>

using namespace glm;
namespace ce {
	using Color = vec4;
	class Material {
	 private:
		Shader* m_shader;
		Texture* m_texture;

	 public:
		Material(const char* name, std::map<std::string, std::string> options = {})
			: Material(new Shader(name, options)) {}
		Material(const char* vertName, const char* fragName, std::map<std::string, std::string> options = {})
			: Material(new Shader(vertName, fragName, options)) {}
		Material(const char* vertName, const char* geomName, const char* fragName, std::map<std::string, std::string> options = {})
			: Material(new Shader(vertName, geomName, fragName, options)) {}
		Material(Shader* shader);
		~Material();
		void update();

		Shader* getShader() { return m_shader; }
		void setTexture(const char* texture) { setTexture(new Texture(texture)); }
		void setTexture(Texture* texture) { m_texture = texture; }

		void bind();
		void unbind();
	};
}
