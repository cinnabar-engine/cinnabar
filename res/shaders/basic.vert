#version 330 core

struct Transform {
	mat4 model;
	mat4 view;
	mat4 proj;
};

uniform Transform transform;

in vec3 aPos;
in vec4 aColor;
in vec2 aTexCoord;

out vec4 vColor;
out vec2 vTexCoord;


void main()
{
	vColor = aColor;
	vTexCoord = aTexCoord;

	gl_Position = transform.proj * transform.view * transform.model * vec4(aPos, 1.0f);
}
