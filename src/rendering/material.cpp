#include "material.h"

ce::Material::Material(Shader* shader)
	: m_shader(shader),
	  m_texture(NULL) {
	update();
}

ce::Material::~Material() {
	delete m_shader;
	delete m_texture;
}

void ce::Material::update() {
	if (m_texture != NULL)
		m_shader->setInt("material.texture", 1);
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
