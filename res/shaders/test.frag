#version 330 core

in float vDist;

out vec4 fColor;

void main() {
	fColor = vec4(1, 3. / (vDist + 3.), 0, 1);
}