#pragma once


#include <ft2build.h>
#include FT_FREETYPE_H


#include <ce_render_fundementals.h>
#include "material.h"

#include "render_engine.h"
#include <math/transform.h>
#include "camera.h"

namespace ce {
	class Text {
		
		struct Character {
			glm::vec2 size;
			Material* material;
			Mesh* mesh;
		};
	public:
		Text(const char* content,const char* font, unsigned int size);
		~Text(){}
		
		void render(RenderEngine* renderEngine,Transform* transform, ce::Camera* camera);
		
	private:		
		std::vector<Character> characters;
		
	};
}
