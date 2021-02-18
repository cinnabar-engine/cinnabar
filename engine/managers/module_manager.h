#pragma once

#include <string>

namespace ce {
	typedef void (*module_t)();
	class ModuleManger {

	 private:
		inline static const std::string MODULE_FOLDER = "modules";

		void loadModules();

	 public:
		ModuleManger();
		~ModuleManger();
	};
}