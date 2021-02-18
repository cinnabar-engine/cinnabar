#ifndef _MODULE_MANAGER_H_
#define _MODULE_MANAGER_H_

#include <string>

namespace ce {
	
	class ModuleManger {
		
	private:
		inline static const std::string MODULE_FOLDER = "modules";
		
		void loadModules();
	public:
		ModuleManger();
		~ModuleManger();
	};
}

#endif // _MODULE_MANAGER_H_
