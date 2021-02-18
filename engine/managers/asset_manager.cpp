#include "asset_manager.h"
#include <algorithm>
#include <core/tpnt_log.h>

// TEXT FILES
#include <fstream>
#include <sstream>

// TEXTURES
#include "stb_image.h"

// MESHES
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

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

ce::ShaderFile ce::AssetManager::getShaderFile(std::string filename) {
	std::string path = SHADER_FOLDER + "/" + filename;
	ShaderFile shaderFile;
	shaderFile.name = filename;

	shaderFile.vertex = load_text_file(path + ".vert");
	if (shaderFile.vertex == "")
		shaderFile.vertex = load_text_file(path + ".vs");

	shaderFile.fragment = load_text_file(path + ".frag");
	if (shaderFile.fragment == "")
		shaderFile.fragment = load_text_file(path + ".fs");

	shaderFile.geometry = load_text_file(path + ".geom");
	if (shaderFile.geometry == "")
		shaderFile.geometry = load_text_file(path + ".gs");

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
	if(textureFile.data == NULL)return getTextureFile("missing.png");
	return textureFile;
}

void ce::AssetManager::freeTextureFile(ce::TextureFile textureFile) {
	stbi_image_free(textureFile.data);
}

ce::MeshFile ce::AssetManager::getMeshFile(std::string filename) {
	std::string path = MESH_FOLDER + "/" + filename;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		LOG_ERROR(importer.GetErrorString());
	}
	MeshFile file;
	for (int i = 0; i < 1 /*scene->mNumMeshes*/; i++) {
		auto mesh = *(scene->mMeshes + i);
		for (int i = 0; i < mesh->mNumVertices; i++) {
			auto position = *(mesh->mVertices + i);
			auto texCoord = *(mesh->mTextureCoords + i);
			//TODO: Support Normals
			auto normal = *(mesh->mNormals + i);
			auto color = *(mesh->mColors + i);
			file.vertices.push_back({glm::vec3(position.x, position.y, position.z), glm::vec4(color->r, color->g, color->b, color->a), glm::vec2(texCoord->x, texCoord->y)});
		}
		for (int i = 0; i < mesh->mNumFaces; i++) {
			auto face = *(mesh->mFaces + i);
			for (int j = 0; j < face.mNumIndices; j++) {
				file.indices.push_back(*(face.mIndices + i));
			}
		}
	}
	return file;
}
