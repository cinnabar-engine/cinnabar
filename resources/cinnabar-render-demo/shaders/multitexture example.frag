#version 330 core

struct Material {
	sampler2D textures[2];
};

uniform Material material;

in vec2 vUV;
in vec4 vColor;
in float vTexture;

out vec4 fColor;

void main() {
	fColor = (
		texture(material.textures[0], vUV) * (1 - vTexture) +
		texture(material.textures[1], vUV) * vTexture
	) * vColor;
}