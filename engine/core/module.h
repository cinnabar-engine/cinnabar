/**
 * API FOR CREATING MODULES FOR  CINNABAR ENGINE
 */

#pragma once

namespace ce {
	class Module {
	 private:
	 public:
		virtual void tick(float deltaTime) = 0;
	};
	typedef Module* init_module_t();
	typedef void delete_module_t(Module*);
}
#define CE_MODULE(X)                                      \
	extern "C" ce::Module* init_module() { return new X; } \
	extern "C" void delete_module(ce::Module* m) { delete m; }