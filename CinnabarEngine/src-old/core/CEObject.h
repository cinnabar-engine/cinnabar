#ifndef _CE_OBJECT_H_
#define _CE_OBJECT_H_

#include "Logger.h"

namespace ce {
	class Object {
	private:
		Logger* logger;
	protected:
		Logger* GetLogger(std::string name) {
			if (logger == nullptr) {
				logger = new Logger(name);
			}
			return logger;
		}

		virtual Logger* GetLogger() = 0;
	public:
		Object() :logger(nullptr) {};
		~Object() {
			delete logger;
		}
		virtual void destroy() = 0;
	};
}

#endif // !_CE_OBJECT_H_
