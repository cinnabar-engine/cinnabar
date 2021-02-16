#version 330 core
uniform sampler2D uTex;

in vec4 vColor;
in vec2 vTexCoord;

out vec4 fColor;

void main()
{
	fColor = texture(uTex,vTexCoord)*vColor;
}
