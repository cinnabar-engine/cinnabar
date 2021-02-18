#include "asset_manager.h"
#include <algorithm>
#include <core/tpnt_log.h>

// TEXT FILES
#include <fstream>
#include <sstream>

// TEXTURES
#include "stb_image.h"

std::string ce::AssetManager::load_text_file(std::string path) {
	std::fstream file;
	std::string text = "";
	file.exceptions(std::fstream::failbit | std::fstream::badbit);
	try {
		file.open(path);
		if (!file.good()) {
			LOG_WARN("FILE_DOES_NOT_EXIST: " + path);
			return "";
		}
		std::stringstream filestream;
		filestream << file.rdbuf();
		file.close();
		text = filestream.str();
		LOG_SUCCESS("LOADED_FILE: " + path);
	} catch (std::fstream::failure e) {
		LOG_ERROR("FILE_NOT_SUCCESSFULLY_READ: (" + path + ") " + std::string(e.what()));
	}
	return text;
}

ce::ShaderFile ce::AssetManager::getShaderFiles(std::string vert, std::string geom, std::string frag) {
	ShaderFile shaderFile;
	shaderFile.vertName = vert;
	shaderFile.geomName = geom;
	shaderFile.fragName = frag;

	shaderFile.vertex = load_text_file(SHADER_FOLDER + "/" + vert + ".vert");
	if (shaderFile.vertex == "")
		shaderFile.vertex = load_text_file(SHADER_FOLDER + "/" + vert + ".vs");

	shaderFile.geometry = load_text_file(SHADER_FOLDER + "/" + geom + ".geom");
	if (shaderFile.geometry == "")
		shaderFile.geometry = load_text_file(SHADER_FOLDER + "/" + geom + ".gs");

	shaderFile.fragment = load_text_file(SHADER_FOLDER + "/" + frag + ".frag");
	if (shaderFile.fragment == "")
		shaderFile.fragment = load_text_file(SHADER_FOLDER + "/" + frag + ".fs");

	if (frag != "")
		shaderFile.name = frag;
	else if (vert != "")
		shaderFile.name = vert;
	else
		shaderFile.name = geom;

	return shaderFile;
}

ce::TextureFile ce::AssetManager::getTextureFile(std::string filename) {
	std::string path = TEXTURE_FOLDER + "/" + filename;
	// stbi_set_flip_vertically_on_load(1);
	LOG_SUCCESS("LOADED_TEXTURE " + path);

	TextureFile textureFile;
	textureFile.name = filename;
	textureFile.data = stbi_load(path.c_str(), &textureFile.width,
		&textureFile.height, &textureFile.channelCount, 0);
	return textureFile;
}

void ce::AssetManager::freeTextureFile(ce::TextureFile textureFile) {
	stbi_image_free(textureFile.data);
}