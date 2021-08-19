#include "texture.hpp"

#include "asset_manager.hpp"
#include <cinnabar-core/tpnt_log.h>

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


	if (this->loadData(textureFile.data, textureFile.width, textureFile.height, GL_RGBA, type)) {
		LOG_SUCCESS("Loaded texture: %s", filename.c_str());
	} else
		LOG_ERROR("TEXTURE_LOADING_FAILED: %s", filename.c_str());
	ce::assetManager::freeTextureFile(textureFile);
}

ce::Texture::Texture(const void* data, GLsizei width, GLsizei height, GLenum color_space, GLenum type)
	: m_width(0), m_height(0), m_channelCount(0), m_type(type) {

	if (this->loadData(data, width, height, color_space, type)) {
		LOG_SUCCESS("Loaded texture");
	} else {
		LOG_ERROR("TEXTURE_LOADING_FAILED");
	}
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

bool ce::Texture::loadData(const void* data, GLsizei width, GLsizei height, GLenum color_space, GLenum type) {
	m_width = width;
	m_height = height;

	bool out = false;
	bind();

	if (data) {
		glTexImage2D(type, 0, color_space, m_width, m_height, 0, color_space,
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(type);
		out = true;
	}
	unbind();
	return out;
}
