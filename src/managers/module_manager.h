#pragma once

#include <string>
#include <vector>

#include <core/module.h>

namespace ce {
	class ModuleManager {
	 private:
		struct ModuleRef {
			Module* module;
			void* lib;
			init_module_t* inti_module;
			delete_module_t* delete_module;
		};

		inline static const std::string MODULE_FOLDER = "modules";

		std::vector<ModuleRef> m_modules;

		void loadModules();

	 public:
		ModuleManager();
		~ModuleManager();

		void tickModules(double deltaTime);
	};
}