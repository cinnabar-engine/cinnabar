#version 330 core

in vec3 aPos;
in vec4 aColor;
in vec2 aTexCoord;

out vec4 vColor;
out vec2 vTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
	vColor = aColor;
	vTexCoord = aTexCoord;

	gl_Position = uProj * uView * uModel * vec4(aPos, 1.0f);
}
