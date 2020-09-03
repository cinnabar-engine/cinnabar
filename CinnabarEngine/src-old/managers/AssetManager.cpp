#include "AssetManager.h"
#include <algorithm>

//TEXT FILES
#include <fstream>
#include <sstream>

//TEXTURES
#include "stb_image.h"

//XML
#include <libxml/parser.h>
#include <cstring>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

ce::AssetManager::AssetManager()
	:logger(new Logger("asset_manager"))
{
}

ce::AssetManager::~AssetManager()
{
	delete this->logger;
}

std::string ce::AssetManager::loadTextFile(std::string path)
{
	std::fstream file;
	std::string filestring = "";
	file.exceptions(std::fstream::failbit || std::fstream::badbit);
	try {
		file.open(path);
		if (!file.good()) {
			logger->Warn("FILE_DOES_NOT_EXIST: " + path);
			return "";

		}
		std::stringstream filestream;
		filestream << file.rdbuf();
		file.close();
		filestring = filestream.str();
		logger->Log("LOADED_FILE: " + path);
	}
	catch (std::fstream::failure e) {
		logger->Error("FILE_NOT_SUCCESSFULLY_READ:" + std::string(e.what()));
	}
	return filestring;
}

xmlNode* ce::AssetManager::loadXMLFile(std::string path) {
	xmlDoc* file = NULL;
	xmlNode* root = NULL;
	file = xmlReadFile(path.c_str(), NULL, 0);
	if (file == NULL) {
		logger->Error("file unable to be read");
	}
	logger->Log("LOADED_XML_FILE: " + path);
	root = xmlDocGetRootElement(file);

	return root;
}


ce::ShaderFile ce::AssetManager::getShaderFile(std::string filename)
{
	std::string path = SHADER_FOLDER + "/" + filename;
	ShaderFile shaderFile;
	shaderFile.name = filename;
	shaderFile.vertex = loadTextFile(path+".vert");
	if (shaderFile.vertex == "") shaderFile.vertex = loadTextFile(path + ".vs");
	shaderFile.fragment = loadTextFile(path + ".frag");
	if (shaderFile.fragment == "") shaderFile.fragment = loadTextFile(path + ".fs");
	shaderFile.geometry = loadTextFile(path + ".geom");
	if (shaderFile.geometry == "") shaderFile.geometry = loadTextFile(path + ".gs");
	return shaderFile;

}
ce::TextureFile ce::AssetManager::getTextureFile(std::string filename)
{
	std::string path = TEXTURE_FOLDER + "/" + filename;
	//stbi_set_flip_vertically_on_load(1);
	logger->Log("LOADED_TEXTURE " + path);

	TextureFile textureFile;
	textureFile.name = filename;
	textureFile.data = stbi_load(path.c_str(), &textureFile.width, &textureFile.height, &textureFile.channelCount, 0);
	return textureFile;
}


ce::MaterialFile ce::AssetManager::getMaterialFile(std::string filename) {
	MaterialFile materialFile;
	materialFile.name = filename;
	std::string path = MATERIAL_FOLDER + "/" + filename;
	xmlNode* materialFileData = loadXMLFile(path);
	xmlNode* node = NULL;
	for (node = materialFileData->children; node; node = node->next) {
		if (node->type == XML_TEXT_NODE) continue;
		std::pair<const char*, char*> nodeData;
		std::string key = (char*)node->name;
		char* value = (char*)node->children->content;
		char* context = NULL;
		if (key == "ambient" ||
			key == "diffuse" ||
			key == "specular") {
			char* valueArray = strtok_s(value, " ", &context);
			float fourNumbers[4];
			int i = 0;
			while (valueArray != NULL) {
				fourNumbers[i++] = std::stof(valueArray);
				valueArray = strtok_s(NULL, " ", &context);
			}
			glm::vec4* color = reinterpret_cast<glm::vec4*>(fourNumbers);
			if (key == "ambient") materialFile.ambient = *color;
			if (key == "diffuse") materialFile.diffuse = *color;
			if (key == "specular") materialFile.speclular = *color;
		}
		if (key == "diffuseTex")  materialFile.diffuseTex = value;
		if (key == "specularTex") materialFile.specularTex = value;
		if (key == "shader") materialFile.shader = value;
	}
	return materialFile;
}