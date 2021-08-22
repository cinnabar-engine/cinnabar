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
	${CE_LIBS}
	cinnabar-core
	cinnabar-render
)

set_target_properties(
	${NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/res"
)

ADD_CUSTOM_TARGET(cinnabar-render-demo-resources ALL
	COMMAND ${CMAKE_COMMAND} -E create_symlink
		${PROJECT_SOURCE_DIR}/resources/${NAME}
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)