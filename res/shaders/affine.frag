#version 330 core
#define F_DEFTEST 1
//===PLACE_OPTIONS===

uniform sampler2D uTex;

struct Material {
	sampler2D texture;
};

uniform Material material;

in vec4 vColor;
in vec2 vTexCoord;

out vec4 fColor;

void main() {
	fColor = texture(material.texture,vTexCoord + .5 * F_DEFTEST) * vColor;
}