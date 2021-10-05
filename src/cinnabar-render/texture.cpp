#include <cinnabar-render/texture.hpp>

#include <GL/glew.h>

#include <cinnabar-core/tpnt_log.h>

#include <cinnabar-render/types.hpp>
#include <cinnabar-render/asset_manager.hpp>

void ce::Texture::init(TextureFile textureFile, ColorSpace colorSpace, TextureTarget target) {
	glGenTextures(1, (GLuint*)&m_texture);

	if (this->loadData(textureFile, colorSpace, target)) {
		LOG_SUCCESS("Loaded texture");
	} else {
		LOG_ERROR("Failed to load texture");
	}
}

ce::Texture::~Texture() {
	glDeleteTextures(1, (GLuint*)&m_texture);
}

void ce::Texture::bind(int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture((GLenum)m_target, (GLuint)m_texture);
}

void ce::Texture::unbind(int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture((GLenum)m_target, 0);
}

bool ce::Texture::loadData(TextureFile textureFile, ColorSpace colorSpace, TextureTarget target) {
	m_target = target;
	if (!colorSpace)
		switch (textureFile.internalColorSpace) {
			case GL_RED:
			case GL_RG:
			case GL_RGB:
			case GL_RGBA:
				colorSpace = textureFile.internalColorSpace;
				break;

				// TODO: add formats GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_RGBA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL
			default:
				LOG_WARN("Unrecognized internal color space: %i", textureFile.internalColorSpace);
		}

	if (textureFile.data) {
		bind(0);

		glTexParameteri((GLenum)target, GL_TEXTURE_WRAP_S, GL_REPEAT); // TODO: proper system for setting texture parameters
		glTexParameteri((GLenum)target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri((GLenum)target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri((GLenum)target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D((GLenum)m_target, 0, (GLenum)textureFile.internalColorSpace, textureFile.width, textureFile.height, 0, (GLenum)colorSpace, GL_UNSIGNED_BYTE, textureFile.data);
		glGenerateMipmap((GLenum)m_target);

		unbind(0);
		return true;
	} else
		return false;
}
