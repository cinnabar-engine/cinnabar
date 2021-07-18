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
		// reset errors
		dlerror();
		const char* error;
		LOG_INFO("Loading Symbols for: %s", path);
		// Get a function called "Hello"
		init_module_t* init_module = (init_module_t*)dlsym(lib, "init_module");
		// Handle any errors
		error = dlerror();
		if (error) {
			LOG_ERROR(dlerror());
			dlclose(lib);
			continue;
		}
		delete_module_t* delete_module = (delete_module_t*)dlsym(lib, "delete_module");
		error = dlerror();
		if (error) {
			LOG_ERROR(dlerror());
			dlclose(lib);
			continue;
		}
		Module* module = init_module();
		m_modules.push_back({module, lib, init_module, delete_module});
		//delete_module(module);
		//dlclose(lib);
	}
}

ce::ModuleManger::ModuleManger() {
	loadModules();
}

ce::ModuleManger::~ModuleManger() {
	for (int i = 0; i < m_modules.size(); i++) {
		ModuleRef module = m_modules[i];
		module.delete_module(module.module);
		dlclose(module.lib);
	}
}

void ce::ModuleManger::tickModules(double deltaTime) {
	for (int i = 0; i < m_modules.size(); i++)
		m_modules[i].module->tick(deltaTime);
}