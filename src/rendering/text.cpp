#include "text.h"

#include <stdio.h>
#include <string.h>
#include <vector>

#include <core/tpnt_log.h>

ce::Text::Text(const char* content, const char* font, unsigned int size) {
	FT_Library library;
	FT_Face face;
	unsigned int content_len = strlen(content);

	float
		font_resolution = 100.0f,
		modal_scale = 1.f / (20.f * font_resolution);


	LOG_INFO("Creating text (%d):%s", content_len, content);

	if (FT_Init_FreeType(&library)) {
		LOG_ERROR("Error initialising FreeType.");
	}
	LOG_SUCCESS("Successfully initialised FreeType.");

	if (FT_New_Face(library, font, 0, &face)) {
		LOG_ERROR("Error obtaining font face: %s", font);
	}
	LOG_SUCCESS("Successfully obtained font face: %s", font);

	if (FT_Set_Pixel_Sizes(face, 0, size * font_resolution)) {
		LOG_ERROR("Error setting font size.");
	}
	LOG_SUCCESS("Successfully set font size.");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	float x =0,y=0;
	

	for (unsigned int i=0; i < content_len; i++) {
		char glyph = content[i];

		if (FT_Load_Char(face, glyph, FT_LOAD_RENDER)) {
			LOG_ERROR("Error loading character: %c", glyph);
			continue;
		}
		LOG_SUCCESS("Successfully loaded character: %c", glyph);
		
		glm::ivec2 size(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			bearing(face->glyph->bitmap_left, face->glyph->bitmap_top);
		unsigned int advance = face->glyph->advance.x;
		ce::Texture* fontTexture = new ce::Texture(face);
		ce::Material* material = new ce::Material("text");
		material->setTexture(fontTexture);
		material->getShader()->setUniform("material.color", glm::vec4(1.f, 1.f, 0.f, 1.f));

		ce::Transform* transform = new ce::Transform();

		glm::vec2 scale(modal_scale),
			pos(
				x+bearing.x * scale.x,
				y-(size.y-bearing.y) * scale.y),
			dimentions(
				size.x * scale.x,
				size.y * scale.y);

		ce::Mesh* mesh = new ce::Mesh(ce::Mesh::createPlane(dimentions.x, dimentions.y,glm::vec2(0)));
		transform->setPosition(pos.x,pos.y,0.0f);

		characters.push_back({
			{
				size,
				bearing,
				advance
				
			},
			transform,
			material,
			mesh});
		
		x+=(advance>>6)*scale.x;
		//x+=0.1f;
	}

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void ce::Text::render(ce::RenderEngine* renderEngine, ce::Transform* transform, ce::Camera* camera) {

	for (unsigned int i = 0; i < characters.size(); i++) {
		Character character = characters[i];

		character.transform->setParent(transform);
		renderEngine->registerCommand({character.transform, character.material, character.mesh, camera});
	}
}
