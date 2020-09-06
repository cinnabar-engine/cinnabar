#version 330 core

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D fTex;

out vec4 fColor;

void main()
{
	fColor = texture(fTex,vTexCoord)*vColor;
}