#include "asset_manager.h"

#include <algorithm>
#include <core/tpnt_log.h>

// TEXT FILES
#include <fstream>
#include <sstream>

// TEXTURES
#include "stb_image.h"

// MESHES

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

/*
 * # Comment
 * v 1 2 3 4
 * vt 1 2 3 4
 * vn 1 2 3 4
 * f v1 v2 v3
 * f v1//vn1 v2/vt1/vn1 v3/vt2/vn1 v4/vt3/vn1
 */

// TODO: all this mesh loading stuff should go into modules, and the only supported format should be one that can be loaded extremely easily (dumped MeshFile)
std::vector<ce::Vertex> ngonToTris(std::vector<ce::Vertex> face) {
	std::vector<ce::Vertex> indices;
	for (int i = 1; i < face.size() - 1; i++) {
		indices.push_back(face[0]);
		indices.push_back(face[i]);
		indices.push_back(face[i+1]);
	}
	return indices;
}

ce::MeshFile ce::AssetManager::getMeshFile(std::string filename) {
	std::string path = MESH_FOLDER + "/" + filename;
	
	MeshFile mesh;
	// Get File
	std::ifstream file(path);
	if (file.is_open()) {
		std::string line;
		
		// Get Line in the file
		while (std::getline(file, line)) {
			LOG_INFO(line);
			
			// Split the line into parts ( p1 p1 p3 p4 )
			std::stringstream lineStream(line);
			std::vector<std::string> params;
			std::string param;
			//while (lineStream >> param)
			//	params.push_back(param);
			while (std::getline(lineStream, param, ' '))
				params.push_back(param);
			
			// Vertices
			if (params[0] == "v")
				mesh.positions.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));
			// UVs
			if (params[0] == "vt")
				mesh.uvs.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));
			// Normals
			if (params[0] == "vn")
				mesh.normals.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));
			
			// Faces
			if (params[0] == "f") {
				std::vector<Vertex> face;
				// For each Face Vertex (corner)
				// TODO: throw if face has less than 2 verts
				for (int f = 1; f < params.size(); f++) {
					std::string facePart = params[f];
					
					// Split obj vertex into individual indices ( p1/p2/p3 )
					std::stringstream fpStream(facePart); // Face Property Stream
					std::vector<std::string> fpInfo; // Collection fo face properties
					std::string fpProp; // Property (index, uv or normal)
					while (std::getline(fpStream, fpProp, '/'))
						fpInfo.push_back(fpProp);
					//while (fpStream >> fpProp) fpInfo.push_back(fpProp);
					
					// Retrieve the Index UV and Normal from the face part
					Vertex vertex {0, 0, 0};
					// the "if" and "try catch" is to catch any errors from converting string to float without crashing
					// TODO: log errors in catch, that should only happen if the mesh file is broken
					if (fpInfo[0] != "")
						try { vertex.position = std::stoi(fpInfo[0]); } catch (std::exception e) {} // Vertex Index
					if (fpInfo[1] != "")
						try { vertex.uv = std::stoi(fpInfo[1]); } catch (std::exception e) {} // UV Index
					if (fpInfo[2] != "")
						try { vertex.normal = std::stoi(fpInfo[2]); } catch (std::exception e) {} // Normal Index
					
					face.push_back(vertex);
					/*face.push_back({
						std::stoi(fpInfo[0]),
						std::stoi(fpInfo[1]),
						std::stoi(fpInfo[2])
					});*/
				}
				std::vector<Vertex> indices = ngonToTris(face);
				std::move(indices.begin(), indices.end(), std::back_inserter(mesh.indices));
			}
		}
	}
	return mesh;
}
