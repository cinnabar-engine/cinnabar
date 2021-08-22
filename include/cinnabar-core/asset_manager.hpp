#pragma once

#include <string>

namespace ce {
	namespace assetManager {
		namespace defaults {
			extern std::string RESOURCE_FOLDER;
		}

		std::string getTextFile(std::string file, bool mustExist = true);
	};
}
