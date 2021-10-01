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
	for (GLint i = 0; ; i++)
		if (this->shader->setUniform("material.textures[" + std::to_string(i) + "]", i) < 0)
			break;
}

void ce::Material::bind() {
	this->shader->bind();
	for (GLint i = 0; i < this->textures.size(); i++)
		if (this->textures[i] != NULL)
			this->textures[i]->activate(i);
}

void ce::Material::unbind() {
	this->shader->unbind();
	for (GLint i = 0; i < this->textures.size(); i++)
		if (this->textures[i] != NULL)
			this->textures[i]->unbind();
}
