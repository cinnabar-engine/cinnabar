#include "asset_manager.h"

#include <algorithm>
#include <core/tpnt_log.h>

// TEXT FILES
#include <fstream>
#include <sstream>

// TEXTURES
#include "stb_image.h"

// MESHES

std::string ce::AssetManager::load_text_file(std::string path, bool mustExist) {
	std::fstream file;
	std::string text = "";
	file.exceptions(std::fstream::failbit | std::fstream::badbit);
	try {
		file.open(path);
		if (!file.good()) {
			if (mustExist)
				LOG_WARN("FILE_DOES_NOT_EXIST: %s", path.c_str());
			return "";
		}
		std::stringstream filestream;
		filestream << file.rdbuf();
		file.close();
		text = filestream.str();
		LOG_SUCCESS("LOADED_FILE: %s", path.c_str());
	} catch (std::fstream::failure e) {
		LOG_ERROR("FILE_NOT_SUCCESSFULLY_READ: (%s) %s", path.c_str(), e.what());
	}
	return text;
}

ce::ShaderFile ce::AssetManager::getShaderFiles(std::string vert, std::string geom, std::string frag) {
	ShaderFile shaderFile;
	shaderFile.vertName = vert;
	shaderFile.geomName = geom;
	shaderFile.fragName = frag;

	if (frag != "") {
		shaderFile.fragment = load_text_file(SHADER_FOLDER + "/" + frag + ".frag", false);
		if (shaderFile.fragment == "")
			shaderFile.fragment = load_text_file(SHADER_FOLDER + "/" + frag + ".fs");
		if (shaderFile.name == "") // TODO: this ShaderFile name thing really isn't needed, probably remove it (same for MeshFile)
			shaderFile.name = frag;
	}
	if (vert != "") {
		shaderFile.vertex = load_text_file(SHADER_FOLDER + "/" + vert + ".vert", false);
		if (shaderFile.vertex == "")
			shaderFile.vertex = load_text_file(SHADER_FOLDER + "/" + vert + ".vs");
		if (shaderFile.name == "")
			shaderFile.name = vert;
	}
	if (geom != "") {
		shaderFile.geometry = load_text_file(SHADER_FOLDER + "/" + geom + ".geom", false);
		if (shaderFile.geometry == "")
			shaderFile.geometry = load_text_file(SHADER_FOLDER + "/" + geom + ".gs");
		if (shaderFile.name == "")
			shaderFile.name = geom;
	}

	return shaderFile;
}

// TODO: all this mesh loading stuff should go into modules, and the only supported format should be one that can be loaded extremely easily (dumped MeshFile)
ce::TextureFile ce::AssetManager::getTextureFile(std::string filename) {
	std::string path = TEXTURE_FOLDER + "/" + filename;
	// stbi_set_flip_vertically_on_load(1);
	LOG_SUCCESS("LOADED_TEXTURE: %s", path.c_str());

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

/*
 * # Comment
 * v 1 2 3 4
 * vt 1 2 3 4
 * vn 1 2 3 4
 * f v1 v2 v3
 * f v1//vn1 v2/vt1/vn1 v3/vt2/vn1 v4/vt3/vn1
 */

ce::MeshFile ce::AssetManager::getMeshFile(std::string filename) {
	std::string path = MESH_FOLDER + "/" + filename;

	MeshFile mesh;
	// Get File
	std::ifstream file(path);
	if (file.is_open()) {
		std::string line;

		// get Line in the file
		while (std::getline(file, line)) {
			LOG_INFO("%s", line.c_str());

			// Split the line into parts ( p1 p1 p3 p4 )
			std::stringstream lineStream(line);
			std::vector<std::string> params;
			std::string param;
			//while (lineStream >> param)
			//	params.push_back(param);
			while (std::getline(lineStream, param, ' '))
				params.push_back(param);

			// TODO: throw if invalid numbers, amount of params, etc
			// Vertices
			if (params[0] == "v")
				mesh.vertices.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));
			// UVs
			else if (params[0] == "vt")
				mesh.uv.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));
			// Normals
			else if (params[0] == "vn")
				mesh.normals.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));

			// Faces
			else if (params[0] == "f") {
				std::vector<FacePart> face;
				// For each Face Part (corner)
				for (int f = 1; f < params.size(); f++) {
					std::string facePart = params[f];

					// Split Face Part into Parts ( p1/p2/p3 )
					std::stringstream fpStream(facePart); // Face Property Stream
					std::vector<std::string> fpInfo; // Collection fo face properties
					std::string fpProp; // Property (index, uv or normal)
					while (std::getline(fpStream, fpProp, '/'))
						fpInfo.push_back(fpProp);
					//while (fpStream >> fpProp)
					//	fpInfo.push_back(fpProp);

					// Retrieve the Index, UV, and Normal from the face part
					FacePart part{0, 0, 0};
					// the "if" and "try catch" is to catch any erros from converting string to float without crashing
					if (fpInfo[0] != "") // Vertex Index
						try {
							unsigned v = std::stoi(fpInfo[0]);
							part.index = v;
						} catch (std::exception e) {}
					if (fpInfo[1] != "") // UV Index
						try {
							unsigned u = std::stoi(fpInfo[1]);
							part.uv = u;
						} catch (std::exception e) {}
					if (fpInfo[2] != "") // Normal Index
						try {
							unsigned n = std::stoi(fpInfo[2]);
							part.normal = n;
						} catch (std::exception e) {}

					face.push_back(part);
					/*face.push_back({
						std::stoi(fpInfo[0]),
						std::stoi(fpInfo[1]),
						std::stoi(fpInfo[2])
					});*/
				}
				mesh.faces.push_back(face);
			}
		}
	}
	return mesh;
}
