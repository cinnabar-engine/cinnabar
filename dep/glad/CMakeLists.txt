project(glad VERSION 0.1.33 LANGUAGES C)

add_library(glad INTERFACE)
target_include_directories(glad INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})