#pragma once

#include "asset_manager.hpp"
#include <GL/glew.h>

namespace ce {
	class Texture {
	 public:
		Texture(std::string filename, GLenum type = GL_TEXTURE_2D);
		Texture(const void* data, GLsizei width, GLsizei height, GLenum color_space = GL_RGBA, GLenum type = GL_TEXTURE_2D);
		~Texture();

		void bind(), unbind(), activate(int slot);

	 private:
		GLuint m_texture;
		int m_width, m_height, m_channelCount;
		unsigned int m_type;
		bool loadData(const void* data, GLsizei width, GLsizei height, GLenum color_space = GL_RGBA, GLenum type = GL_TEXTURE_2D);
	};
}
