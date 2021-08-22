#version 330 core

struct Material {
	sampler2D texture;
};

uniform Material material;

in vec4 vColor;

out vec4 fColor;

void main() {
	fColor = vColor;
}