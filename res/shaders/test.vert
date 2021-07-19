#version 330 core

struct Transform {
	mat4 model;
	mat4 view;
	mat4 proj;
};

uniform Transform transform;

in vec3 aPosition;
in vec3 aNormal;
in vec2 aUV;
in vec4 aColor;

out float vDist;

void main() {
	gl_Position = transform.proj * transform.view * transform.model * vec4(aPosition, 1.);
	vDist = gl_Position[3];
}