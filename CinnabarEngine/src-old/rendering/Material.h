#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <glm/glm.hpp>

#include "../core/CEObject.h"
#include "../managers/AssetManager.h"
#include "../ce_util.h"

using namespace glm;
namespace ce{
	using Color = vec4;
	class Material : public Object
	{
	public:
		Material(MaterialFile material);
		~Material() {};
		void update();

		Shader* getShader();


		void bind();
		void unbind();

	private:
		Color ambient;
		Color diffuse;
		Color specular;
		Texture* diffuseTex;
		Texture* specularTex;
		Shader* shader;

		// Inherited via Object
		virtual Logger* GetLogger() override;
		virtual void destroy() override;
	};
}

#endif // !_MATERIAL_H_
