#include <cinnabar-render/texture.hpp>

#include <GL/glew.h>

#include <cinnabar-core/tpnt_log.h>

#include <cinnabar-render/asset_manager.hpp>

void ce::Texture::init(TextureFile textureFile, GLenum colorSpace, GLenum target) {
	glGenTextures(1, &m_texture);
	bind();
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT); // TODO: proper system for setting texture parameters
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_REPEAT);

	if (this->loadData(textureFile, colorSpace, target)) {
		LOG_SUCCESS("Loaded texture");
	} else {
		LOG_ERROR("Failed to load texture");
	}
}

ce::Texture::~Texture() {
	glDeleteTextures(1, &m_texture);
}

void ce::Texture::bind() {
	glBindTexture(m_target, m_texture);
	glEnable(m_target);
}

void ce::Texture::activate(int slot = 0) {
	glActiveTexture(GL_TEXTURE0 + slot);
	bind();
}

void ce::Texture::unbind() {
	glDisable(m_target);
	glActiveTexture(0);
	glBindTexture(m_target, 0);
}

bool ce::Texture::loadData(TextureFile textureFile, GLenum colorSpace, GLenum target) {
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
		bind();
		glTexImage2D(m_target, 0, textureFile.internalColorSpace, textureFile.width, textureFile.height, 0, colorSpace,
			GL_UNSIGNED_BYTE, textureFile.data);
		glGenerateMipmap(m_target);
		unbind();
		return true;
	} else
		return false;
}
