#pragma once

#include <string>

#include <cinnabar-core/asset_manager.hpp>

#include <cinnabar-render/assets.hpp>

namespace ce {
	namespace assetManager {
		namespace defaults {
			extern std::string
				SHADER_FOLDER,
				TEXTURE_FOLDER,
				MESH_FOLDER,
				SHADER_MISSING,
				TEXTURE_MISSING,
				MESH_MISSING;
		}

		ShaderFile getShaderFile(std::string vert, std::string geom, std::string frag);
		inline ShaderFile getShaderFile(std::string name) { return getShaderFile(name, name, name); };
		TextureFile getTextureFile(std::string path);
		void freeTextureFile(TextureFile textureFile);

		MeshFile getMeshFile(std::string path);
	};
}
