#pragma once

#include <cinnabar-render/types.hpp>
#include <cinnabar-render/asset_manager.hpp>

namespace ce {
	class Texture {
	 public:
		Texture(std::string filename, ColorSpace colorSpace = 0, TextureTarget target = TARGET_TEXTURE_2D) {
			TextureFile textureFile = ce::assetManager::getTextureFile(filename);
			init(textureFile, colorSpace, target);
			ce::assetManager::freeTextureFile(textureFile);
		};
		Texture(TextureFile textureFile, ColorSpace colorSpace = 0, TextureTarget target = TARGET_TEXTURE_2D) {
			init(textureFile, colorSpace, target);
		};
		~Texture();

		void bind(), unbind(), activate(int slot);

	 private:
		glm::uint32 m_texture;
		TextureTarget m_target;

		void init(TextureFile textureFile, ColorSpace colorSpace = 0, TextureTarget target = TARGET_TEXTURE_2D);
		bool loadData(TextureFile textureFile, ColorSpace colorSpace = 0, TextureTarget target = TARGET_TEXTURE_2D);
	};
}
