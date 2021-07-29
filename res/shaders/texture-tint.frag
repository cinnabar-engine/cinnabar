#version 330 core

struct Material {
	sampler2D texture;
	vec4 color;
};

uniform Material material;

in vec2 vUV;
in vec4 vColor;

out vec4 fColor;

void main() {
	fColor = texture(material.texture, vUV).rrrr * vColor * material.color;
}
