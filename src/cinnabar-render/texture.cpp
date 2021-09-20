#include <cinnabar-render/texture.hpp>

#include <cinnabar-core/tpnt_log.h>

#include <cinnabar-render/asset_manager.hpp>

ce::Texture::Texture(TextureFile textureFile, GLenum colorSpace, GLenum target) {

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
	ce::assetManager::freeTextureFile(textureFile); // TODO: what if the TextureFile is used more than once? this should only be called if a string is passed in for the constructor
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
	m_format = textureFile.format; // TODO: are these variables needed, and are they redundantly set elsewhere?
	m_target = target;
	if (colorSpace)
		m_colorSpace = colorSpace;
	else
		switch (m_format.internalColorSpace) {
			case GL_RED:
			case GL_RG:
			case GL_RGB:
			case GL_RGBA:
				m_colorSpace = m_format.internalColorSpace;
				break;

				// TODO: add formats GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_RGBA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL
			default:
				LOG_WARN("Unrecognized internal color space: %i", textureFile.format.internalColorSpace);
		}

	if (textureFile.data) {
		bind();
		glTexImage2D(m_target, 0, m_format.internalColorSpace, m_format.width, m_format.height, 0, m_colorSpace,
			GL_UNSIGNED_BYTE, textureFile.data);
		glGenerateMipmap(m_target);
		unbind();
		return true;
	} else
		return false;
}
