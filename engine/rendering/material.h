#ifndef _MATERIAL_H_
#define _MATERIAL_H_

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
		Material(const char* shader):Material(new Shader(shader)){}
		Material(Shader* shader);
		~Material();
		void update();

		Shader* getShader() { return m_shader; }
		void setTexture(const char* texture) {setTexture(new Texture(texture));}
		void setTexture(Texture* texture) { m_texture = texture; }

		void bind();
		void unbind();
	};
}

#endif // !_MATERIAL_H_
