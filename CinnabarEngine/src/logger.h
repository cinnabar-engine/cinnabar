#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

#define RESET "\033[0m"
#define SUCCESS "\033[1;32m"
#define WARN "\033[1;33m"
#define ERROR "\033[1;31m"


namespace ce {
	class Logger {
	private:
		std::string name;
	public:

		Logger(std::string name);
		~Logger() {};

		void Log(std::string message) { Info(message); };
		void Info(std::string message);
		void Success(std::string message);
		void Warn(std::string message);
		void Error(std::string message);
	};
}

#endif // !_LOGGER_H_
