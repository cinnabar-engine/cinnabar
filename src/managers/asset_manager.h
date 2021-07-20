#pragma once

#include <string>

#include <ce_assets.h>

namespace ce {
	class AssetManager {
	 private:
		inline static const std::string
			SHADER_FOLDER = "shaders",
			TEXTURE_FOLDER = "textures",
			MESH_FOLDER = "meshes",
			SHADER_MISSING = "",
			TEXTURE_MISSING = "",
			MESH_MISSING = "missing.obj";

		static std::string load_text_file(std::string file, bool mustExist = true);

	 public:
		static ShaderFile getShaderFile(std::string name) { return getShaderFiles(name, name, name); };
		static ShaderFile getShaderFiles(std::string vert, std::string geom, std::string frag);
		static TextureFile getTextureFile(std::string filename);
		static void freeTextureFile(TextureFile textureFile);

		static Meshfile getMeshfile(std::string filename);
	};
}
