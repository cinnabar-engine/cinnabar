#version 330 core

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D uTex;

out vec4 fColor;

void main()
{
	fColor = texture(uTex,vTexCoord)*vColor;
}
