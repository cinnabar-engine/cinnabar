project(glew-include)

add_library(glew INTERFACE)
target_include_directories(glew INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../glew/include)