#pragma once

#include <GL/glew.h>
#include <ce_math.h>

#include <string>
#include <vector>

namespace ce {
	struct File {
		std::string name = "";
	};
	struct ShaderFile : public File {
		std::string
			vertName = "",
			geomName = "",
			fragName = "",
			vertex = "",
			geometry = "",
			fragment = "";
	};
	struct TextureFile : public File {
		unsigned char* data = NULL;
		int
			width = 0,
			height = 0,
			channelCount = 0;
	};
	struct MaterialFile : public File {
		glm::vec4
			ambient = glm::vec4(0.0f),
			diffuse = glm::vec4(0.0f),
			speclular = glm::vec4(0.0f);
		std::string
			diffuseTex = "missing.png",
			specularTex = "missing.png",
			shader = NULL;
	};
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv = glm::vec2(0.0f, 0.0f);
		glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	};
	struct Meshfile : public File {
		std::vector<Vertex> verts = {};
		std::vector<GLuint> indices = {};
	};
}
