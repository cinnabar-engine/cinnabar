#include <cinnabar-render/material.hpp>

#include <vector>

ce::Material::MAX_TEXTURES = -1;
//glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &ce::Material::MAX_TEXTURES);
//m_textures

ce::Material::Material(Shader* shader)
	: m_shader(shader),
	  m_texture(NULL) {
	update();
}

ce::Material::~Material() {
	delete m_shader; // TODO: what if someone passes in a shader or texture that gets reused?
	delete m_texture;
}

void ce::Material::update() { // TODO: why does this even exist?
	for (GLint i = 0; i < m_textures.length, i++)
		if (m_texture != NULL)
			this->shader->setUniformArray("material.textures", i);
}

void ce::Material::bind() {
	m_shader->bind();
	for (GLint i = 0; i < m_textures.length, i++)
		if (m_textures[i] != NULL)
			m_textures[i]->activate(1);
}

void ce::Material::unbind() {
	m_shader->unbind();
	for (GLint i = 0; i < m_textures.length, i++)
		if (m_textures[i] != NULL)
			m_textures[i]->unbind();
}
