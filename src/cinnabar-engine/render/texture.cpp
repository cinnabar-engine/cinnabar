#include "texture.hpp"

#include <core/tpnt_log.h>
#include "asset_manager.hpp"

ce::Texture::Texture(std::string filename, GLenum type)
	: m_width(0), m_height(0), m_channelCount(0), m_type(type) {
	TextureFile textureFile = ce::assetManager::getTextureFile(filename);

	m_width = textureFile.width;
	m_height = textureFile.height;
	m_channelCount = textureFile.channelCount;

	glGenTextures(1, &m_texture);
	bind();
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_REPEAT);

	if (textureFile.data) {
		glTexImage2D(type, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, textureFile.data);
		glGenerateMipmap(type);
		LOG_SUCCESS("Loaded texture: %s", filename.c_str());
	} else
		LOG_ERROR("TEXTURE_LOADING_FAILED: %s", filename.c_str());
	unbind();
	ce::assetManager::freeTextureFile(textureFile);
}

ce::Texture::~Texture() {
	glDeleteTextures(1, &m_texture);
}

void ce::Texture::bind() {
	glBindTexture(m_type, m_texture);
	glEnable(m_type);
}

void ce::Texture::activate(int slot = 0) {
	glActiveTexture(GL_TEXTURE0 + slot);
	bind();
}

void ce::Texture::unbind() {
	glDisable(m_type);
	glActiveTexture(0);
	glBindTexture(m_type, 0);
}