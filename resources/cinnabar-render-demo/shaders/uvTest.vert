#version 330 core

struct Transform {
	mat4 model;
	mat4 view;
	mat4 proj;
};

uniform Transform transform;

in vec3 aPosition;
in vec2 aUV;

out vec2 vUV;

void main() {
	vUV = aUV;

	gl_Position = transform.proj * transform.view * transform.model * vec4(aPosition, 1.);
}