#include <cinnabar-render/material.hpp>

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
	if (m_texture != NULL)
		m_shader->setUniform("material.texture", 1);
}

void ce::Material::bind() {
	m_shader->bind();
	if (m_texture != NULL)
		m_texture->activate(1);
}

void ce::Material::unbind() {
	m_shader->unbind();
	if (m_texture != NULL)
		m_texture->unbind();
}
