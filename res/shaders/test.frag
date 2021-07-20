#version 330 core

in float vDist;
in vec3 vNormal;

out vec4 fColor;

void main() {
	fColor = vec4(1, 3. / (vDist + 3.), (vNormal.x + vNormal.y + vNormal.z) / 3.0, 1);
}