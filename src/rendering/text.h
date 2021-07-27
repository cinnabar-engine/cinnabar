#pragma once


#include <ft2build.h>
#include FT_FREETYPE_H


#include "material.h"
#include <ce_render_fundementals.h>

#include "camera.h"
#include "render_engine.h"
#include <math/transform.h>

namespace ce {
	class Text {

		struct Character {
			struct CharacterPositioning {
				glm::ivec2 size, bearing;
				unsigned int advance;
			} positioning;
			Transform* transform;
			Material* material;
			Mesh* mesh;
		};

	 public:
		Text(const char* content, const char* font, unsigned int size);
		~Text() {}

		void render(RenderEngine* renderEngine, Transform* transform, ce::Camera* camera);

	 private:
		std::vector<Character> characters;
	};
}
