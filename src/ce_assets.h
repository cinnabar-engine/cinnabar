#pragma once

#include <GL/glew.h>
#include <ce_math.h>

#include "rendering/vertex.h"
#include <string>
#include <vector>



#include <ft2build.h>
#include FT_FREETYPE_H

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
	struct Meshfile {
		std::vector<Vertex> verts = {};
		std::vector<GLuint> indices = {};
	};
	
	class Material;
	class Mesh;
	struct Font {
			FT_Library library;
			FT_Face face;
			struct Character {
				char c;
				glm::ivec2 size, bearing;
				unsigned int advance;
				glm::vec2 scale;
				Material* material;
				Mesh* mesh;
			} characters[255] = {};
		};
}
