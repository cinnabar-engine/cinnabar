#version 330 core

struct Material {
	vec4 color;
};

uniform Material material;

in vec2 vUV;
in vec4 vColor;

out vec4 fColor;

void main() {
	fColor = vColor * material.color;
}
