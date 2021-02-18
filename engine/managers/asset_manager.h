#pragma once

#include <string>

#include <ce_assets.h>

namespace ce {
	class AssetManager {
	 private:
		inline static const std::string
			SHADER_FOLDER = "shaders",
			TEXTURE_FOLDER = "textures";

		static std::string load_text_file(std::string file);

	 public:
		static ShaderFile getShaderFile(std::string name) { return getShaderFiles(name, name, name); };
		static ShaderFile getShaderFiles(std::string vert, std::string geom, std::string frag);
		static ce::TextureFile getTextureFile(std::string filename);
		static void freeTextureFile(ce::TextureFile textureFile);
	};
}