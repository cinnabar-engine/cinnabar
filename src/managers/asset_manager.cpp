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
	if (textureFile.data == NULL)
		return getTextureFile("missing.png");
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
	file.name = filename;
	for (int i = 0; i < scene->mNumMeshes; i++) {
		auto mesh = *(scene->mMeshes + i);
		LOG_INFO("Loading Mesh " + path + " (V:I):" + std::to_string(mesh->mNumVertices) + ":" + std::to_string(mesh->mNumFaces));
		for (int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			vertex.position = glm::vec3(
				mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z
			);
			if(mesh->mTextureCoords[0]) {
				vertex.texCoord = glm::vec2(
					 mesh->mTextureCoords[1][i].x,
					 mesh->mTextureCoords[1][i].y
				);
			}
			if(mesh->mColors[0]) {
				vertex.color = glm::vec4(
					mesh->mColors[0][i].r,
					mesh->mColors[0][i].g,
					mesh->mColors[0][i].b,
					mesh->mColors[0][i].a
				);
			} else {
				vertex.color = glm::vec4(1.f,1.f,1.f,1.f);
			}
			file.vertices.push_back(vertex);
		}
		for (int i = 0; i < mesh->mNumFaces; i++) {
			auto face = *(mesh->mFaces + i);
			//TODO: Support Normals
			auto normal = mesh->mNormals[i];
			file.normals.push_back(glm::vec3(
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			));
			for (int j = 0; j < face.mNumIndices; j++) {
				file.indices.push_back(face.mIndices[j]);
			}
		}
	}
	return file;
}
