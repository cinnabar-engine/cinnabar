#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <string>

#include "../core/logger.h"
#include "../ce_assets.h"

namespace ce {
	class AssetManager {
	private:
		inline static const std::string
			SHADER_FOLDER = "shaders",
			TEXTURE_FOLDER = "textures";
		inline static Logger* logger = new Logger("asset_manager");

		static std::string load_text_file(std::string file);
	public:
		static ShaderFile getShaderFile(std::string filename);
	};
}

#endif // !_ASSET_MANAGER_H_
