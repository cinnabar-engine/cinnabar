#pragma once

#include <GL/glew.h>

#include <cinnabar-render/asset_manager.hpp>

namespace ce {
	class Texture {
	 public:
		Texture(std::string filename, GLenum colorSpace = 0, GLenum target = GL_TEXTURE_2D) // TODO: default colorSpace should change based on TextureFile.channelCount (GL_RED, GL_RG, GL_RGB, GL_RGBA)
			: Texture(ce::assetManager::getTextureFile(filename), colorSpace, target){};
		Texture(TextureFile textureFile, GLenum colorSpace = 0, GLenum target = GL_TEXTURE_2D);
		~Texture();

		void bind(), unbind(), activate(int slot);

	 private:
		GLuint m_texture;
		TextureFormat m_format;
		GLenum m_colorSpace;
		GLenum m_target;

		bool loadData(TextureFile textureFile, GLenum colorSpace = 0, GLenum target = GL_TEXTURE_2D);
	};
}
