set(BUILD_SHARED_LIBS TRUE)
# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
add_subdirectory(glew)
add_library(glew INTERFACE)
target_include_directories(glew INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)


# SDL
add_subdirectory(SDL2)
set_target_properties(SDL2 PROPERTIES FOLDER dep/SDL)
set_target_properties(SDL2main PROPERTIES FOLDER dep/SDL)

# GLM
add_subdirectory(glm)
set_target_properties(glm_shared PROPERTIES FOLDER dep)

# Libs
set(CE_LIBS
${OPENGL_LIBRARY}
libglew_shared
libglew_static
glm
SDL2
SDL2main

PARENT_SCOPE
)