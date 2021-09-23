/**
 * Tumpnt Logger
 * Author: Cameron Trow <tumblegamer@gmail.com>, edited by SArpnt
 * Source: https://github.com/Tumpnt/TumpntAudio/blob/master/src/core/ta_log.h
 *
 * Example Usage
 *
 * int main() {
 * 	LOG_INFO("Hello World");
 * 	return 0;
 * }
 *
 * Output:
 * [INFO][main.cpp:3|main]: Hello World
 */
#pragma once

#include <stdio.h>
#include <string.h>

#ifdef NDEBUG
#define TPNT_LOGGER_FORMAT "[%s]: "
#define TPNT_LOGGER_CONTEXT __LINE__, __FUNCTION__
#else
#define TPNT_LOGGER_FORMAT "[%s][%s:%d|%s]: "
#define TPNT_LOGGER_FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define TPNT_LOGGER_CONTEXT TPNT_LOGGER_FILE, __LINE__, __FUNCTION__
#endif
#define TPNT_LOG(LOGTYPE, ...) \
	printf(TPNT_LOGGER_FORMAT, (LOGTYPE), TPNT_LOGGER_CONTEXT); \
	printf(__VA_ARGS__); \
	putchar('\n')
#define TPNT_LOG_RESET "\033[0m"
#define TPNT_LOG_SUCCESS "\033[1;32m"
#define TPNT_LOG_WARN "\033[1;33m"
#define TPNT_LOG_ERROR "\033[1;31m"

#define LOG_INFO(...) TPNT_LOG("INFO", __VA_ARGS__)
#define LOG_WARN(...) TPNT_LOG(TPNT_LOG_WARN "WARN" TPNT_LOG_RESET, __VA_ARGS__)
#define LOG_ERROR(...) TPNT_LOG(TPNT_LOG_ERROR "ERROR" TPNT_LOG_RESET, __VA_ARGS__)
#define LOG_SUCCESS(...) TPNT_LOG(TPNT_LOG_SUCCESS "SUCCESS" TPNT_LOG_RESET, __VA_ARGS__)
