#include "module_manager.h"

#include <core/tpnt_log.h>
#include <dlfcn.h>
#include <filesystem>
#include <iostream>
#include <string>

#define LIB_EXT so

void ce::ModuleManger::loadModules() {
	std::string path = "./" + MODULE_FOLDER;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		const char* path = entry.path().c_str();
		LOG_INFO(path);
		void* lib = dlopen(path, RTLD_LAZY);
		if (!lib) {
			LOG_ERROR(dlerror());
			continue;
		}
		//reset Errors
		dlerror();
		LOG_ERROR("Loading Symbols for: " + path);
		module_t module = (module_t)dlsym(lib, "hello");
		const char* error = dlerror();
		if (error) {
			LOG_ERROR(dlerror());
			dlclose(lib);
			continue;
		}

		module();

		dlclose(lib);
	}
}

ce::ModuleManger::ModuleManger() {
	loadModules();
}

ce::ModuleManger::~ModuleManger() {
}
