#version 330 core
uniform sampler2D uTex;

struct Material {
	sampler2D texture;
};

uniform Material material;

in vec4 vColor;
in vec2 vTexCoord;

out vec4 fColor;

void main() {
	fColor = texture(material.texture,vTexCoord) * vColor;
}