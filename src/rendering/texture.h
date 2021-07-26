#pragma once

#include <GL/glew.h>
#include <ce_assets.h>
#include <managers/asset_manager.h>


// Font Rendering (temporery until dedicated font class exists)
#include <ft2build.h>
#include FT_FREETYPE_H

namespace ce {
	class Texture {
	 public:
		Texture(std::string filename, GLenum type = GL_TEXTURE_2D);
		Texture(FT_Face font_face);
		Texture(const void* data, GLsizei width, GLsizei height,GLenum color_space=GL_RGBA, GLenum type = GL_TEXTURE_2D);
		~Texture();

		void bind(), unbind(), activate(int slot);

	 private:
		GLuint m_texture;
		int m_width, m_height, m_channelCount;
		unsigned int m_type;
		bool loadData(const void* data, GLsizei width, GLsizei height,GLenum color_space=GL_RGBA, GLenum type = GL_TEXTURE_2D);
	};
}
