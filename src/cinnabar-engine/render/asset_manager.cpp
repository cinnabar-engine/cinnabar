#include "asset_manager.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "stb_image.h"

#include <core/tpnt_log.h>

std::string ce::assetManager::getTextFile(std::string path, bool mustExist) {
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
		LOG_ERROR("FILE_NOT_SUCCESSFULLY_READ: (%s) %s", path.c_str(), e.what()); // TODO: figure out why files not exist create an iostream error instead of expected error
	}
	return text;
}

ce::ShaderFile ce::assetManager::getShaderFile(std::string vert, std::string geom, std::string frag) {
	ShaderFile shaderFile;
	shaderFile.vertName = vert;
	shaderFile.geomName = geom;
	shaderFile.fragName = frag;

	if (frag != "") {
		shaderFile.fragment = getTextFile(defaults::SHADER_FOLDER + "/" + frag + ".frag", false);
		if (shaderFile.fragment == "")
			shaderFile.fragment = getTextFile(defaults::SHADER_FOLDER + "/" + frag + ".fs");
	}
	if (vert != "") {
		shaderFile.vertex = getTextFile(defaults::SHADER_FOLDER + "/" + vert + ".vert", false);
		if (shaderFile.vertex == "")
			shaderFile.vertex = getTextFile(defaults::SHADER_FOLDER + "/" + vert + ".vs");
	}
	if (geom != "") {
		shaderFile.geometry = getTextFile(defaults::SHADER_FOLDER + "/" + geom + ".geom", false);
		if (shaderFile.geometry == "")
			shaderFile.geometry = getTextFile(defaults::SHADER_FOLDER + "/" + geom + ".gs");
	}

	return shaderFile;
}

ce::TextureFile ce::assetManager::getTextureFile(std::string filename) {
	std::string path = defaults::TEXTURE_FOLDER + "/" + filename;
	// stbi_set_flip_vertically_on_load(1);
	LOG_SUCCESS("LOADED_TEXTURE: %s", path.c_str());

	TextureFile textureFile;
	textureFile.data = stbi_load(path.c_str(), &textureFile.width,
		&textureFile.height, &textureFile.channelCount, 0);
	if (textureFile.data == NULL)
		return getTextureFile("missing.png");
	return textureFile;
}

void ce::assetManager::freeTextureFile(ce::TextureFile textureFile) {
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
	std::vector<GLuint> indices; // TODO: make this work for concave faces
	for (size_t i = 1; i < sides - 1; i++) {
		indices.push_back(offset);
		indices.push_back(i + offset);
		indices.push_back(i + 1 + offset);
	}
	return indices;
}

// TODO: system for other file types (not the actual loading of them, just detection of types)
ce::MeshFile ce::assetManager::getMeshFile(std::string filename) {
	std::string path = defaults::MESH_FOLDER + "/" + filename;
	std::ifstream file(path);
	if (!file.is_open()) {
		LOG_INFO("couldn't load model %s", filename.c_str());
		if (filename == "missing.obj")
			return MeshFile();
		else
			return getMeshFile("missing.obj");
	}

	MeshFile mesh;
	std::string line;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	// Get Line in the file
	while (std::getline(file, line)) {
		// remove comments
		line = line.substr(0, line.find("#"));
		if (line == "")
			continue;

		// Split the line into parts ( p1 p1 p3 p4 )

		std::vector<std::string> params;
		{
			std::stringstream lineStream(line);
			std::string param;
			//while (lineStream >> param)
			//	params.push_back(param);
			while (std::getline(lineStream, param, ' '))
				params.push_back(param);
		}

		// TODO: throw if invalid numbers, amount of params, etc
		// Vertices
		if (params[0] == "v")
			positions.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));
		// UVs
		else if (params[0] == "vt")
			uvs.push_back(glm::vec2(std::stof(params[1]), std::stof(params[2])));
		// Normals
		else if (params[0] == "vn")
			normals.push_back(glm::vec3(std::stof(params[1]), std::stof(params[2]), std::stof(params[3])));

		// Faces
		else if (params[0] == "f") {
			std::vector<Vertex> face;
			IndexedVertex indexedVert;
			size_t* fpAddresses[3] = {&indexedVert.position, &indexedVert.uv, &indexedVert.normal};
			// for each vertex of face
			for (int i = 1; i < params.size(); i++) {
				std::string facePart = params[i];
				// Split obj vertex into individual indices ( p1/p2/p3 )
				{
					std::stringstream fpStream(facePart); // Face Property Stream
					std::string fpProp; // fpProp Property (index, uv or normal)
					int i = 0;
					while (std::getline(fpStream, fpProp, '/')) {
						if (fpProp == "") {
							if (i == 0) {
								LOG_INFO("missing vertex position on face \"%s\"", line.c_str());
								throw;
							}
						} else {
							int err = sscanf(fpProp.c_str(), "%zu", fpAddresses[i]);
							if (err == EOF) {
								LOG_INFO("invalid vertex property index \"%s\"", fpProp.c_str());
								throw;
							}
							*fpAddresses[i] -= 1;
						}
						if (++i > 3)
							break;
					}
					if (i != 3) {
						LOG_INFO("invalid vertex properties %i %s", i, params[i].c_str()); // TODO: better exception handling
						throw;
					}
				}

				Vertex vertex;
				vertex.position = positions[indexedVert.position];
				if (indexedVert.uv != (size_t)-1)
					vertex.uv = uvs[indexedVert.uv];
				if (indexedVert.normal != (size_t)-1)
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
	return mesh;
}
