#pragma once

#include <ce_assets.h>
#include <ce_rendering.h>
#include <managers/asset_manager.h>

namespace ce {

	class Texture {
	 private:
		GLuint texture;
		int width, height, channelCount;
		unsigned int type;

	 public:
		Texture(std::string filename, GLenum type = GL_TEXTURE_2D);
		~Texture();

		void bind(), unbind(), activate(int slot);
	};
}