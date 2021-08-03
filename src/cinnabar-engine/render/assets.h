#pragma once

#include <GL/glew.h>
#include <ce_math.h>

#include <vertex.h>
#include <string>
#include <vector>

namespace ce {
	struct ShaderFile {
		std::string
			vertName = "",
			geomName = "",
			fragName = "",
			vertex = "",
			geometry = "",
			fragment = "";
	};
	struct TextureFile {
		unsigned char* data = NULL;
		int
			width = 0,
			height = 0,
			channelCount = 0;
	};
	struct MaterialFile {
		glm::vec4
			ambient = glm::vec4(0.0f),
			diffuse = glm::vec4(0.0f),
			speclular = glm::vec4(0.0f);
		std::string
			diffuseTex = "missing.png",
			specularTex = "missing.png",
			shader = NULL;
	};
	struct MeshFile {
		std::vector<Vertex> verts = {};
		std::vector<GLuint> indices = {};
	};
}
