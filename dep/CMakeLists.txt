find_package(PkgConfig REQUIRED)

# OpenGL
cmake_policy(SET CMP0072 NEW)
if(MINGW)
	set(OPENGL_LIBRARY gl)
else()
	find_package(OpenGL REQUIRED)
	if(UNIX)
		set(OPENGL_LIBRARY ${OPENGL_opengl_LIBRARY})
	endif()
	if(WIN32)
		set(OPENGL_LIBRARY ${OPENGL_gl_LIBRARY})
	endif()
endif()
message(NOTICE "OPENGL_LIBRARY " ${OPENGL_LIBRARY})

# glew
find_package(GLEW REQUIRED)
message(NOTICE "GLEW_LIBRARIES " ${GLEW_LIBRARIES})
message(NOTICE "GLEW_INCLUDE_DIRS " ${GLEW_INCLUDE_DIRS})

# glfw
find_package(glfw3 REQUIRED)

# glm
find_package(glm REQUIRED)
message(NOTICE "GLM_INCLUDE_DIRS " ${GLM_INCLUDE_DIRS})

# ASSIMP
#find_package(assimp REQUIRED)
#message(NOTICE "ASSIMP_LIBRARY " ${ASSIMP_LIBRARY})
#message(NOTICE "ASSIMP_LIBRARIES " ${ASSIMP_LIBRARIES})
#message(NOTICE "ASSIMP_INCLUDE_DIR " ${ASSIMP_INCLUDE_DIR})


set(OPENGL_LIBS ${OPENGL_LIBRARY} PARENT_SCOPE)
set(GLEW_LIBS ${GLEW_LIBRARIES} PARENT_SCOPE)
set(GLFW_LIBS glfw PARENT_SCOPE)
#set(ASSIMP_LIBS ${ASSIMP_LIBRARIES} PARENT_SCOPE)
set(CMAKE_LIBS ${CMAKE_DL_LIBS} PARENT_SCOPE)

set(CE_INCLUDE # TODO: remove prefix and create better name
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	#${ASSIMP_INCLUDE_DIR}
	${GLM_INCLUDE_DIRS}

	PARENT_SCOPE
)