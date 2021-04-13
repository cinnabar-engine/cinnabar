/**
 * API FOR CREATING MODULES FOR CINNABAR ENGINE
 */

#pragma once

namespace ce {
	class Module {
	 public:
		virtual void tick(double deltaTime) = 0;
	};
	typedef Module* init_module_t();
	typedef void delete_module_t(Module*);
}
#define CE_MODULE(CLASS)                                      \
	extern "C" ce::Module* init_module() { return new CLASS; } \
	extern "C" void delete_module(ce::Module* m) { delete m; }
