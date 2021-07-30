#pragma once


#include <map>

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
			ce::Font::Character* character;
			Transform* transform;
			std::vector<Transform> points;
		};

	 public:
		Text(std::string content, const char* font, unsigned int size, bool make_3d=false);
		~Text();

		void setText(std::string content);
		void setColor(glm::vec4 color) { m_color = color; }
		void setSize(float size){m_font_size=size;}

		void render(RenderEngine* renderEngine, Transform* transform, ce::Camera* camera, ce::Material* material=NULL);

	 private:
		 bool m_make_3d;
		std::string m_content;
		glm::vec2 m_cursor;
		const char* m_font_path;
		float m_font_size;
		Font* m_font;
		glm::vec4 m_color;
		std::vector<Character> m_characters;
		
		void pushChar(char c);
		void clearChars();
		
		void setCharColor(ce::Font::Character* character, glm::vec4 color);
		static int bindChar(ce::Font* font, char c);
		static ce::Font::Character* getCharacter(ce::Font* font, char c);
		static ce::Font::Character* getCharacter3D(ce::Font* font, char c);
		
		void bind();
		void unbind();
	};
}
