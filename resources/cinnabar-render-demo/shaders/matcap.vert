#version 330 core

struct Transform {
	mat4 model;
	mat4 view;
	mat4 proj;
};

uniform Transform transform;

in vec3 aPosition;
in vec3 aNormal;
in vec4 aColor;

out vec2 vUV;
out vec4 vColor;

void main() {
	vUV = (mat3(transform.view) *
		normalize(transpose(inverse(transform.model)) * vec4(aNormal, 1.)).xyz
	).xy * .5 + .5;
	vColor = aColor;

	gl_Position = transform.proj * transform.view * transform.model * vec4(aPosition, 1.);
}