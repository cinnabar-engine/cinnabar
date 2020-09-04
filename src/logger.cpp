#include "logger.h"

#include <iostream>
#include <algorithm>

std::string to_upper(std::string& str) {
	std::for_each(str.begin(), str.end(), [](char& c) {
		c = ::toupper(c);
		});
	return str;
}

const char* CE_LOG_FORMAT = "%s::%s::%s";
void logf(std::string color, std::string type, std::string name, std::string message)
{
	std::cout << color << type << "::" << name << "::" << message << RESET << "\n";
	//fprintf
}

ce::Logger::Logger(std::string name)
	:name(to_upper(name)) {}

void ce::Logger::Info(std::string message)
{
	logf("", "INFO", name, message);
}

void ce::Logger::Success(std::string message)
{
	logf(SUCCESS, "SUCCESS", name, message);
}

void ce::Logger::Warn(std::string message)
{
	logf(WARN, "WARN", name, message);
}

void ce::Logger::Error(std::string message)
{
	logf(ERROR, "ERROR", name, message);
}
