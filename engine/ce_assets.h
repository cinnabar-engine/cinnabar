#ifndef _CE_ASSETS_H_
#define _CE_ASSETS_H_

#include <string>
#include <ce_math.h>

namespace ce {
	struct File {
		std::string name = "";
	};
	struct ShaderFile :public File {
		std::string vertex = "";
		std::string fragment = "";
		std::string geometry = "";
	};
	struct TextureFile :public File {
		unsigned char* data = NULL;
		int width = 0;
		int height = 0;
		int channelCount = 0;
	};
	struct MaterialFile :public File {
		glm::vec4
			ambient = glm::vec4(0.0f),
			diffuse = glm::vec4(0.0f),
			speclular = glm::vec4(0.0f);
		std::string
			diffuseTex = "missing.png",
			specularTex = "missing.png",
			shader = "";
	};
}

#endif // !_CE_ASSETS_H_
