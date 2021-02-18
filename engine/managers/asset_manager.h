#pragma once

#include <string>

#include <ce_assets.h>

namespace ce {
	class AssetManager {
	 private:
		inline static const std::string
			SHADER_FOLDER = "shaders",
			TEXTURE_FOLDER = "textures",
			MESH_FOLDER = "meshes";

		static std::string load_text_file(std::string file);

	 public:
		static ShaderFile getShaderFile(std::string filename);
		static TextureFile getTextureFile(std::string filename);
		static void freeTextureFile(ce::TextureFile textureFile);
		
		static MeshFile getMeshFile(std::string filename);
	};
}
