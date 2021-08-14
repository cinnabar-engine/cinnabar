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
	VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${NAME}>"
)