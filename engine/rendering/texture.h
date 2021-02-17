#pragma once

#include <ce_assets.h>
#include <ce_rendering.h>
#include <managers/asset_manager.h>

namespace ce {

	class Texture {
	 private:
		GLuint m_texture;
		int m_width, m_height, m_channelCount;
		unsigned int m_type;

	 public:
		Texture(std::string filename, GLenum type = GL_TEXTURE_2D);
		~Texture();

		void bind(), unbind(), activate(int slot);
	};
}
