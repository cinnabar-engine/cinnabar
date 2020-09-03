#include "Material.h"

#include "../managers/ObjectManager.h"

ce::Material::Material(MaterialFile material) :
	ambient(material.ambient),
	diffuse(material.diffuse),
	specular(material.speclular),
	diffuseTex(new Texture(ASSETMAN->getTextureFile(material.diffuseTex),GL_TEXTURE_2D)),
	specularTex(new Texture(ASSETMAN->getTextureFile(material.specularTex), GL_TEXTURE_2D)),
	shader(new Shader(ASSETMAN->getShaderFile(material.shader)))
{
	update();
}

ce::Shader* ce::Material::getShader()
{
	return shader;
}

void ce::Material::update() {
	/*shader->setVec4("material.ambient", this->ambient);
	shader->setVec4("material.diffuse", this->diffuse);
	shader->setVec4("material.specular", this->specular);
	shader->setVec4("material.ambient", this->ambient);*/
	shader->setInt("material.diffuseTex", 1);
	shader->setInt("material.specularTex", 2);
}

void ce::Material::bind()
{
	shader->bind();
	diffuseTex->activate(1);
	specularTex->activate(2);
}

void ce::Material::unbind()
{
	shader->unbind();
	diffuseTex->unbind();
	specularTex->unbind();
}

ce::Logger* ce::Material::GetLogger()
{
	return Object::GetLogger("material");
}

void ce::Material::destroy()
{
}
