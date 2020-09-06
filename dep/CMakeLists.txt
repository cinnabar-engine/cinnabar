set(BUILD_SHARED_LIBS TRUE)
# OpenGL
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS})

# glad
# if(MSVC)
# add_subdirectory(glad)
# endif()

# glew
set(BUILD_UTILS true)
add_subdirectory(glew)
set_target_properties(libglew_shared PROPERTIES FOLDER dep/glew)
set_target_properties(libglew_static PROPERTIES FOLDER dep/glew)

# SDL
add_subdirectory(SDL)
set_target_properties(SDL2 PROPERTIES FOLDER dep/SDL)
set_target_properties(SDL2main PROPERTIES FOLDER dep/SDL)
set_target_properties(SDL2-static PROPERTIES FOLDER dep/SDL)

# GLM
add_subdirectory(glm)
# set_target_properties(glm_shared PROPERTIES FOLDER dep)

# Libs
set(CE_LIBS
${OPENGL_LIBRARY}
glew
glm
SDL2
SDL2main

PARENT_SCOPE
)