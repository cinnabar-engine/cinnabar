/**
 * Tumpnt Logger
 * Author: Cameron Trow <tumblegamer@gmail.com>
 * Source: https://github.com/Tumpnt/TumpntAudio/blob/master/src/core/ta_log.h
 *
 * Example Usage
 *
 * int main() {
 *      LOG_INFO("Hello World");
 *      return 0;
 * }
 *
 * Output:
 * [INFO][main.cpp:3|main]: Hello World
 *
 */
#pragma once

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>

#define TPNT_LOGGER_STR(X) (std::string("") + X).c_str()
#define TPNT_LOGGER_FORMAT "[%s][%s:%d|%s]: %s\n"
#define TPNT_LOGGER_FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define TPNT_LOGGER_CONTEXT TPNT_LOGGER_FILE, __LINE__, __FUNCTION__
#define TPNT_LOG(L, X) printf(TPNT_LOGGER_FORMAT, TPNT_LOGGER_STR(L), TPNT_LOGGER_CONTEXT, TPNT_LOGGER_STR(X))
#define TPNT_LOG_RESET "\033[0m"
#define TPNT_LOG_SUCCESS "\033[1;32m"
#define TPNT_LOG_WARN "\033[1;33m"
#define TPNT_LOG_ERROR "\033[1;31m"

#define LOG_INFO(X) TPNT_LOG("INFO", X)
#define LOG_WARN(X) TPNT_LOG(TPNT_LOG_WARN + "WARN" + TPNT_LOG_RESET, X)
#define LOG_ERROR(X) TPNT_LOG(TPNT_LOG_ERROR + "ERROR" + TPNT_LOG_RESET, X)
#define LOG_SUCCESS(X) TPNT_LOG(TPNT_LOG_SUCCESS + "SUCCESS" + TPNT_LOG_RESET, X)
