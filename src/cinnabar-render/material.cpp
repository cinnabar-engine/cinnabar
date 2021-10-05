#include <cinnabar-render/material.hpp>

#include <string>
#include <vector>

#include <GL/glew.h>

ce::Material::Material(Shader* shader, size_t textureCount)
	: shader(shader),
	  textures(std::vector<Texture*>(textureCount, NULL)) {
	update();
}

void ce::Material::deleteContents() {
	delete this->shader;
	deleteTextures();
}

void ce::Material::deleteTextures() {
	for (Texture* t : this->textures)
		delete t;
	this->textures.clear();
}

void ce::Material::update() {
	for (GLint i = 0; ; i++) {
		glm::int32 location = this->shader->getUniformLocation("material.textures[" + std::to_string(i) + "]", false);
		if (location < 0)
			break;
		this->shader->setUniform(location, i);
	}
}

void ce::Material::bind() {
	this->shader->bind();
	for (GLint i = 0; i < this->textures.size(); i++)
		if (this->textures[i] != NULL)
			this->textures[i]->bind(i);
}

void ce::Material::unbind() {
	this->shader->unbind();
	for (GLint i = 0; i < this->textures.size(); i++)
		if (this->textures[i] != NULL)
			this->textures[i]->unbind(i);
}
