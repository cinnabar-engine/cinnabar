#pragma once

#include <GL/glew.h>

#include <cinnabar-render/asset_manager.hpp>

namespace ce {
	class Texture {
	 public:
		Texture(std::string filename, GLenum colorSpace = 0, GLenum target = GL_TEXTURE_2D) {
			TextureFile textureFile = ce::assetManager::getTextureFile(filename);
			init(textureFile, colorSpace, target);
			ce::assetManager::freeTextureFile(textureFile);
		};
		Texture(TextureFile textureFile, GLenum colorSpace = 0, GLenum target = GL_TEXTURE_2D) {
			init(textureFile, colorSpace, target);
		};
		~Texture();

		void bind(), unbind(), activate(int slot);

	 private:
		GLuint m_texture;
		GLenum m_target;

		void init(TextureFile textureFile, GLenum colorSpace = 0, GLenum target = GL_TEXTURE_2D);
		bool loadData(TextureFile textureFile, GLenum colorSpace = 0, GLenum target = GL_TEXTURE_2D);
	};
}
