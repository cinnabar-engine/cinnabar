#version 330 core
uniform sampler2D uTex;

struct Material {
	sampler2D texture;
};

uniform Material material;

in float vDist;

out vec4 fColor;

void main() {
	fColor = vec4(1, 3. / (vDist + 3.), 0, 1);
}