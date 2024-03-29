#version 330 core

struct Transform {
	mat4 model;
	mat4 view;
	mat4 proj;
};

struct Material {
	sampler2D textures[1];
};

uniform Transform transform;
uniform Material material;

in vec2 vUV;
in vec4 vColor;

out vec4 fColor;

void main() {
	fColor = texture(material.textures[0], vUV) * vColor;
}