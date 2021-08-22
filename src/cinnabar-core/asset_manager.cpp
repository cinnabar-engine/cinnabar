#include <cinnabar-core/asset_manager.hpp>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

#include <cinnabar-core/tpnt_log.h>

namespace ce::assetManager::defaults {
	std::string RESOURCE_FOLDER = "resources";
}

std::string ce::assetManager::getTextFile(std::string path, bool mustExist) {
	std::fstream file;
	std::string text = "";
	file.exceptions(std::fstream::failbit | std::fstream::badbit);
	try {
		file.open(defaults::RESOURCE_FOLDER + "/" + path);
		if (!file.good()) {
			if (mustExist)
				LOG_WARN("Text file does not exist: %s", path.c_str());
			return "";
		}
		std::stringstream filestream;
		filestream << file.rdbuf();
		file.close();
		text = filestream.str();
		LOG_SUCCESS("Loaded text file: %s", path.c_str());
	} catch (std::fstream::failure e) {
		LOG_ERROR("Failed to read text file: (%s) %s", path.c_str(), e.what()); // TODO: figure out why files not exist create an iostream error instead of expected error
	}
	return text;
}