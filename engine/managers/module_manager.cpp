#include "module_manager.h"

#include <dlfcn.h>
#include <string>
#include <filesystem>
#include <core/tpnt_log.h>
#include <iostream>
#include <core/module.h>

#define LIB_EXT so

void ce::ModuleManger::loadModules()
{
	std::string path = "./" + MODULE_FOLDER;
	for(const auto & entry : std::filesystem::directory_iterator(path)) {
		const char* path = entry.path().c_str();
		LOG_INFO(path);
		void * lib = dlopen(path,RTLD_LAZY);
		if(!lib) {
			LOG_ERROR(dlerror());
			continue;
		}
		//reset Errors
		dlerror();
		const char* error;
		LOG_ERROR("Loading Symbols for: " + path);
		//Get a function called "Hello"
		init_module_t* init_module = (init_module_t*) dlsym(lib,"init_module");
		//Handle any errors
		error = dlerror();
		if(error) {
			LOG_ERROR(dlerror());
			dlclose(lib);
			continue;
		}
		delete_module_t* delete_module = (delete_module_t*) dlsym(lib,"delete_module");
		error = dlerror();
		if(error) {
			LOG_ERROR(dlerror());
			dlclose(lib);
			continue;
		}
		Module* module = init_module(lib);
		delete_module(module);
		dlclose(lib);
	}
}

ce::ModuleManger::ModuleManger()
{
	loadModules();
}

ce::ModuleManger::~ModuleManger()
{
}

