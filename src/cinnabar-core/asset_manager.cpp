#include <cinnabar-core/asset_manager.hpp>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include <cinnabar-core/tpnt_log.h>

namespace ce::assetManager::defaults {
	std::string RESOURCE_FOLDER = "resources";
}

std::string ce::assetManager::getTextFile(std::string path, bool mustExist) {
	std::string text = "";
	std::ifstream file(defaults::RESOURCE_FOLDER + "/" + path);
	if (file.fail()) {
		if (std::filesystem::exists(path)) {
			LOG_ERROR("Failed to read text file: %s", path.c_str());
		} else {
			if (mustExist) {
				LOG_WARN("Text file does not exist: %s", path.c_str());
			}
		}
		return "";
	}
	std::stringstream filestream;
	filestream << file.rdbuf();
	file.close();
	text = filestream.str();
	LOG_SUCCESS("Loaded text file: %s", path.c_str());
	return text;
}