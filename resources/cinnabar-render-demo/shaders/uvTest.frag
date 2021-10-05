#version 330 core

in vec2 vUV;

out vec4 fColor;

void main() {
	fColor = vec4(vUV, 0, 1);
}