/**
 * API FOR CREATING MODULES FOR  CINNABAR ENGINE
 */

#ifndef _CE_MODULE_H_
#define _CE_MODULE_H_

namespace ce {
	class Module {
	private:
	public:		
		virtual void tick(float deltaTime)=0;
	};
	
	typedef Module* init_module_t();
	typedef void delete_module_t(Module*);

}
#define CE_MODULE(X) extern "C" ce::Module* init_module() { return new X;} extern "C" void delete_module(ce::Module* m) { delete m;}

#endif //_CE_MODULE_H_
