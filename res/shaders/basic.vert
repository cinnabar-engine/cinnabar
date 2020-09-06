#version 330 core

in vec3 aPos;
in vec4 aColor;
in vec2 aTexCoord;

out vec4 vColor;
out vec2 vTexCoord;

void main()
{
	vColor = aColor;
	vTexCoord = aTexCoord;

	gl_Position = vec4(aPos, 1.0f)*vec4(1.0,-1.0f,1.0,1.0);
}