#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <cinnabar-render/vertex.hpp>

namespace ce {
	struct ShaderFile {
		std::string
			vert = "",
			geom = "",
			frag = "";
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
			specular = glm::vec4(0.0f);
		std::string
			diffuseTex = "missing.png",
			specularTex = "missing.png",
			shader = "missing";
	};
	struct MeshFile {
		std::vector<Vertex> verts = {};
		std::vector<GLuint> indices = {};
		GLenum format;
	};
}
