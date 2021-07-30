#include "text.h"

#include <stdio.h>
#include <string.h>
#include <vector>

#include <core/tpnt_log.h>

float
	font_resolution = 100.0f,
	modal_scale = 1.f / (20.f * font_resolution);

ce::Text::Text(std::string content, const char* font_path, unsigned int size, bool make_3d)
	: m_font(new ce::Font), m_cursor(0), m_font_path(font_path), m_make_3d(make_3d) {
	setSize(size);
	setColor(glm::vec4(1.f, 1.f, 0, 1.f));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	setText(content);
}

ce::Text::~Text() {
	delete m_font;
}

void ce::Text::setText(std::string content) {
	unsigned int content_len = content.length();
	m_content = content;
	LOG_INFO("Setting text (%d):%s", content_len, content.c_str());
	clearChars();
	bind();
	for (unsigned int i = 0; i < content_len; i++) {
		pushChar(content[i]);
	}
	unbind();
}

void ce::Text::render(ce::RenderEngine* renderEngine, ce::Transform* transform, ce::Camera* camera, ce::Material* material) {

	for (unsigned int i = 0; i < m_characters.size(); i++) {
		Character character = m_characters[i];

		character.transform->setParent(transform);
		if (character.character->material)
			setCharColor(character.character, m_color);
		if (character.points.size()) {
			for (int i = 0; i <character.points.size();i++) {
				renderEngine->registerCommand({&character.points[i],
					m_make_3d ? material : character.character->material,
					character.character->mesh,
					camera});
			}
		} else {
			renderEngine->registerCommand({character.transform,
				m_make_3d ? material : character.character->material,
				character.character->mesh,
				camera});
		}
	}
}

void ce::Text::pushChar(char c) {
	ce::Transform* transform = new ce::Transform();
	ce::Font::Character* character = m_make_3d ? getCharacter3D(m_font, c) : getCharacter(m_font, c);
	if (!character)
		return;
	glm::vec2 pos(
		m_cursor.x + character->bearing.x * character->scale.x,
		m_cursor.y - (character->size.y - character->bearing.y) * character->scale.y);
	transform->setPosition(pos.x, pos.y, 0.0f);
	
	std::vector<ce::Transform> points;
	if(character->points.size()) {
		for (int i = 0; i <character->points.size();i++) {
			/*Transform point_transform;
			point_transform.setParent(transform);
			
			points.push_back(point_transform);*/
		}
	}
	m_characters.push_back({character, transform,points});

	m_cursor.x += (character->advance >> 6) * character->scale.x;
}


void ce::Text::clearChars() {
	m_characters.clear();
	m_cursor = glm::vec2(0);
}


void ce::Text::setCharColor(ce::Font::Character* character, glm::vec4 color) {
	character->material->getShader()->setUniform("material.color", color);
}

int ce::Text::bindChar(ce::Font* font, char c) {
	if (FT_Load_Char(font->face, c, FT_LOAD_RENDER)) {
		LOG_ERROR("Error loading character: %c", c);
		return 1;
	}
	LOG_SUCCESS("Successfully loaded character: %c", c);
	return 0;
}


ce::Font::Character* ce::Text::getCharacter(Font* font, char c) {
	ce::Font::Character* character = &font->characters[c];
	if (character->c != c) {
		if (bindChar(font, c))
			return NULL;

		glm::ivec2 size(font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows),
			bearing(font->face->glyph->bitmap_left, font->face->glyph->bitmap_top);
		unsigned int advance = font->face->glyph->advance.x;
		ce::Texture* fontTexture = new ce::Texture(font->face);
		ce::Material* material = new ce::Material("texture-tint");
		material->setTexture(fontTexture);

		glm::vec2 scale(modal_scale),
			dimensions(
				size.x * scale.x,
				size.y * scale.y);

		ce::Mesh* mesh = new ce::Mesh(ce::Mesh::createPlane(dimensions.x, dimensions.y, glm::vec2(0)));

		*character = {
			c,
			size,
			bearing,
			advance,
			scale,
			material,
			mesh};
	}
	return character;
}


ce::Font::Character* ce::Text::getCharacter3D(Font* font, char c) {
	ce::Font::Character* character = &font->characters[c];
	if (character->c != c) {
		if (bindChar(font, c))
			return NULL;

		glm::ivec2 size(font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows),
			bearing(font->face->glyph->bitmap_left, font->face->glyph->bitmap_top);
		unsigned int advance = font->face->glyph->advance.x;

		glm::vec2 scale(modal_scale),
			dimensions(
				size.x * scale.x,
				size.y * scale.y);


		//Create mesh of character

		/*
			typedef struct  FT_Outline_
			{
				short       n_contours;       number of contours in glyph        
				short       n_points;         number of points in the glyph      
				FT_Vector*  points;           the outline's points               
				char*       tags;             the points flags                   
				short*      contours;         the contour end points             
				int         flags;            outline masks                      
			} */
		FT_Outline outline = font->face->glyph->outline;
		std::vector<glm::vec2> points;
		for (unsigned int i = 0; i < outline.n_points; i++) {
			FT_Vector p = outline.points[i];
			glm::vec2 point(p.x, p.y);
			points.push_back(point);
		}


		ce::Mesh* mesh = new ce::Mesh(ce::Mesh::createPlane(.01f, .01f, glm::vec2(0)));

		*character = {
			c,
			size,
			bearing,
			advance,
			scale,
			NULL,
			mesh,
			points};
	}
	return character;
}

void ce::Text::bind() {
	ce::AssetManager::getFont(m_font_path, *m_font);

	if (FT_Set_Pixel_Sizes(m_font->face, 0, m_font_size * font_resolution)) {
		LOG_ERROR("Error setting font size.");
	}
	LOG_SUCCESS("Successfully set font size.");
}

void ce::Text::unbind() {
	ce::AssetManager::closeFont(m_font);
}
