#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <cinnabar-render/types.hpp>
#include <cinnabar-render/vertex.hpp>

namespace ce {
	struct ShaderFile {
		std::string
			vert = "",
			geom = "",
			frag = "";
	};
	struct TextureFile {
		void* data = NULL;
		glm::uint32
			width = 0,
			height = 0;
		glm::int32 internalColorSpace = 0; // TODO: is there a better value for this? GL_NONE exists but doesn't seem correct (also make changes in Texture)
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
		std::vector<glm::uint32> indices = {};
		MeshFormat format;
	};
}
