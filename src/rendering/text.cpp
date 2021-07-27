#include "text.h"

#include <stdio.h>
#include <string.h>
#include <vector>

#include <core/tpnt_log.h>

ce::Text::Text(const char* content,const char* font, unsigned int size){
	FT_Library library;
	FT_Face face;
	unsigned int content_len = strlen(content);
	
	LOG_INFO("Creating text (%d):%s",content_len,content);
	
	if (FT_Init_FreeType(&library)) {
		LOG_ERROR("Error initialising FreeType.");
	}
	LOG_SUCCESS("Successfully initialised FreeType.");

	if (FT_New_Face(library, font, 0, &face)) {
		LOG_ERROR("Error obtaining font face: %s", font);
	}
	LOG_SUCCESS("Successfully obtained font face: %s", font);

	if (FT_Set_Pixel_Sizes(face, 0, size)) {
		LOG_ERROR("Error setting font size.");
	}
	LOG_SUCCESS("Successfully set font size.");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	for(unsigned int i;i<content_len;i++) {
		char glyph = content[i];

		if (FT_Load_Char(face, glyph, FT_LOAD_RENDER)) {
			LOG_ERROR("Error loading character: %c",glyph);
			continue;
		}
		LOG_SUCCESS("Successfully loaded character: %c",glyph);
		
		glm::vec2 size(
			face->glyph->bitmap.width/2000.0f,
			face->glyph->bitmap.rows/2000.0f
		);
		
		ce::Mesh* mesh = new ce::Mesh(ce::Mesh::createPlane(size.x,size.y));
		ce::Texture* fontTexture = new ce::Texture(face);
		ce::Material* material = new ce::Material("text");
		material->setTexture(fontTexture);
		material->getShader()->setUniform("material.color", glm::vec4(1.f,1.f,0.f,1.f));
		
		//size.x = face->glyph->advance.x/2000.0f;
		//size.x = size.y;
		
		
		ce::Text::Character character = {
			size,
			material,
			mesh
		};
		
		characters.push_back(character);
	}

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}
		
void ce::Text::render(ce::RenderEngine* renderEngine,ce::Transform* transform, ce::Camera* camera){
	
	glm::vec3 progress;
	
	for(unsigned int i = 0; i<characters.size();i++) {
		
		ce::Transform* t = new Transform();
		*t = *transform;
		t->translate(progress);
		
		Character character = characters[i];
		renderEngine->registerCommand({t, character.material, character.mesh, camera});
		progress.x+=character.size.x;
	}
}
