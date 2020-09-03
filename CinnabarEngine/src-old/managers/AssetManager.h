#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <map>
#include <string>

#include <glad/glad.h>
#include <libxml/tree.h>
#include <glm/glm.hpp>

#include "../core/Logger.h"
#include "../ce_assets.h"

#define ASSETMAN ce::AssetManager::GetInstance()

namespace ce {
	class AssetManager {
	public:
	private:
		inline static std::string SHADER_FOLDER = "shaders";
		inline static const std::string
			TEXTURE_FOLDER = "textures",
			MATERIAL_FOLDER = "materials";

		inline static AssetManager* instance = 0;
		Logger* logger;

		AssetManager();
		~AssetManager();

		std::string loadTextFile(std::string file);
		xmlNode* loadXMLFile(std::string path);
	public:

		ShaderFile getShaderFile(std::string file);
		TextureFile getTextureFile(std::string file);
		MaterialFile getMaterialFile(std::string filename);

		static AssetManager* GetInstance() {
			if (instance==0) {
				instance = new AssetManager();
			}
			return instance;
		}
	};
}

#endif // !_ASSET_MANAGER_H_
