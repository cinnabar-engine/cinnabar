#version 330 core

struct Transform {
	mat4 model;
	mat4 view;
	mat4 proj;
};

uniform Transform transform;

in vec3 aPos;
in vec3 aNormal;
in vec4 aColor;
in vec2 aUV;

out vec4 vColor;

void main() {
	vColor = aColor;

	gl_Position = transform.proj * transform.view * transform.model * vec4(aPos, 1.);
}