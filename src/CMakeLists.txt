include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/cinnabar-engine
	${CE_INCLUDES}
)


add_subdirectory(cinnabar-engine/cinnabar-core)
add_subdirectory(cinnabar-engine/cinnabar-render)
add_subdirectory(cinnabar-render-demo)