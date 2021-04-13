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

// TODO: all this mesh loading stuff should go into modules, and the only supported format should be one that can be loaded extremely easily (dumped MeshFile)
struct IndexedVertex {
	size_t
		position = -1,
		normal = -1,
		uv = -1,
		color = -1;
};

std::vector<GLuint> genNgonIndices(std::size_t sides, std::size_t offset) {
	std::vector<GLuint> indices;
	for (size_t i = 1; i < sides - 1; i++) {
		indices.push_back(offset);
		indices.push_back(i + offset);
		indices.push_back(i + 1 + offset);
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

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> uvs;
		std::vector<glm::vec3> normals;
		
		// Get Line in the file
		while (std::getline(file, line)) {
			// remove comments
			line = line.substr(0, line.find("#"));
			if (line == "")
				continue;
			
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
				positions.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));
			// UVs
			else if (params[0] == "vt")
				uvs.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));
			// Normals
			else if (params[0] == "vn")
				normals.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));
			
			// Faces
			else if (params[0] == "f") {
				std::vector<Vertex> face;
				// For each Face Vertex (corner)
				for (int i = 1; i < params.size(); i++) {
					std::string facePart = params[i];
					// Split obj vertex into individual indices ( p1/p2/p3 )
					std::string fpInfo[3]; // Collection fo face properties
					{
						std::stringstream fpStream(facePart); // Face Property Stream
						std::string fpProp; // fpProp Property (index, uv or normal)
						int i = 0;
						while (std::getline(fpStream, fpProp, '/')) {
							fpInfo[i] = fpProp;
							if (++i > 3)
								break;
						}
						if (i != 3) {
							LOG_INFO("invalid vertex properties %i %s/%s/%s", i, fpInfo[0].c_str(), fpInfo[1].c_str(), fpInfo[2].c_str()); // TODO: better exception handling
							throw;
						}
					}

					// Retrieve the Index UV and Normal from the face part
					// TODO: make this code less messy
					IndexedVertex indexedVert;
					size_t* fpAddresses[3] = {&indexedVert.position, &indexedVert.uv, &indexedVert.normal};
					// the "if" and "try catch" is to catch any errors from converting string to float without crashing
					// TODO: log errors in catch, that should only happen if the mesh file is broken
					for (int i = 0; i < 3; i++)
						if (fpInfo[i] != "")
							try { *fpAddresses[i] = std::stoi(fpInfo[i]); } catch (std::exception e) {}
					
					Vertex vertex;
					// TODO: throw if property missing
					vertex.position = positions[indexedVert.position];
					if (indexedVert.uv > -1)
						vertex.uv = uvs[indexedVert.uv];
					else
						vertex.uv = glm::vec2(0.0f, 0.0f);
					vertex.normal = normals[indexedVert.normal];
					face.push_back(vertex);
				}
				if (face.size() < 3) {
					LOG_INFO("invalid face polygon %i", face.size()); // TODO better exception handling
					throw;
				}
				std::vector<GLuint> indices = genNgonIndices(face.size(), mesh.verts.size());
				std::move(face.begin(), face.end(), std::back_inserter(mesh.verts));
				std::move(indices.begin(), indices.end(), std::back_inserter(mesh.indices));
				// TODO: optimize mesh (find and remove repeat verticies)
			}
		}
	}
	return mesh;
}
