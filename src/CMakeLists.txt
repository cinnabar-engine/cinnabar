include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/cinnabar-engine
	${CE_INCLUDES}
)

add_subdirectory(cinnabar-engine/core)
add_subdirectory(cinnabar-engine/render)
add_subdirectory(demo)
