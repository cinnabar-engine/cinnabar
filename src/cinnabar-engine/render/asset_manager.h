#pragma once

#include <string>

#include <assets.h>

namespace ce {
	namespace assetManager {
		namespace default {
			const std::string
				SHADER_FOLDER = "shaders",
				TEXTURE_FOLDER = "textures",
				MESH_FOLDER = "meshes",
				SHADER_MISSING = "",
				TEXTURE_MISSING = "",
				MESH_MISSING = "missing.obj";
		}

		std::string getTextFile(std::string file, bool mustExist = true);

		ShaderFile getShaderFile(std::string name) { return getShaderFile(name, name, name); };
		ShaderFile getShaderFile(std::string vert, std::string geom, std::string frag);
		TextureFile getTextureFile(std::string filename);
		void freeTextureFile(TextureFile textureFile);

		MeshFile getMeshFile(std::string filename);
	};
}
