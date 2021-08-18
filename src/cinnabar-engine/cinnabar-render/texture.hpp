#pragma once

#include <GL/glew.h>
#include "asset_manager.hpp"

namespace ce {
	class Texture {
	 public:
		Texture(std::string filename, GLenum type = GL_TEXTURE_2D);
		~Texture();

		void bind(), unbind(), activate(int slot);

	 private:
		GLuint m_texture;
		int m_width, m_height, m_channelCount;
		unsigned int m_type;
	};
}
