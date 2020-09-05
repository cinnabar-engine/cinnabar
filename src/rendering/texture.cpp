#include "Texture.h"

#include "../managers/asset_manager.h"

ce::Texture::Texture(TextureFile texture, GLenum type) :
	width(texture.width),
	height(texture.height),
	channelCount(texture.channelCount),
	type(type)
{
	glGenTextures(1, &this->texture);
	bind();
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_REPEAT);

	width = texture.width;
	height = texture.height;
	channelCount = texture.channelCount;

	if (texture.data) {
		glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data);
		glGenerateMipmap(type);
		GetLogger()->Log(texture.name + " has been loaded.");
	}
	else {
		GetLogger()->Error("TEXTURE_LOADING_FAILED: " + texture.name);
	}
	unbind();
}

ce::Texture::~Texture()
{;
	glDeleteTextures(1, &texture);
}

ce::Logger* ce::Texture::GetLogger()
{
	return new Logger("texture");
}

void ce::Texture::bind()
{
	glBindTexture(type, texture);
	glEnable(type);
}

void ce::Texture::activate(int slot=0)
{
	glActiveTexture(GL_TEXTURE0+slot);
	bind();
}

void ce::Texture::unbind() {
	glDisable(type);
	glActiveTexture(0);
	glBindTexture(this->type, 0);
}
