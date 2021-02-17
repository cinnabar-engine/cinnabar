#include "texture.h"

#include <core/tpnt_log.h>
#include <managers/asset_manager.h>

ce::Texture::Texture(std::string filename, GLenum type)
	: m_width(0), m_height(0), m_channelCount(0), m_type(type) {
	TextureFile textureFile = ce::AssetManager::getTextureFile(filename);

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
		LOG_SUCCESS(textureFile.name + " has been loaded.");
	} else
		LOG_ERROR("TEXTURE_LOADING_FAILED: " + textureFile.name);
	unbind();
	ce::AssetManager::freeTextureFile(textureFile);
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
<<<<<<< HEAD
	glBindTexture(this->m_type, 0);
}
=======
	glBindTexture(this->type, 0);
}
>>>>>>> 569c3cf679420af32babc9d733f4d03bb18f0b8e
