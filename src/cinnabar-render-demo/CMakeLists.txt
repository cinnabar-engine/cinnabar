set(NAME cinnabar-render-demo)

file(GLOB_RECURSE SRC
	"*.cpp"
	"*.c"
)

add_executable(${NAME}
	WIN32
	${SRC}
)

target_link_libraries(${NAME}
	${CMAKE_LIBS}
	${SDL2_LIBS}
	${GLM_LIBS}
	cinnabar-core
	cinnabar-render
)

add_custom_command(TARGET ${NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink
		${PROJECT_SOURCE_DIR}/resources/${NAME}
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)