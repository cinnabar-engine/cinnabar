include_directories(
	${PROJECT_SOURCE_DIR}/include
	${CE_INCLUDES}
)

add_subdirectory(cinnabar-core)
add_subdirectory(cinnabar-render)
add_subdirectory(cinnabar-render-demo)