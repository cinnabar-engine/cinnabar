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

out vec2 vUV;
out vec4 vColor;
out float vTexture;

void main() {
	vUV = aUV;
	vColor = aColor;
	vTexture = float(aNormal.y > 0.01);

	gl_Position = transform.proj * transform.view * transform.model * vec4(aPosition, 1.);
}