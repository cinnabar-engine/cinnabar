set(NAME cinnabar-render-demo)

file(GLOB_RECURSE CE_SRC
	"*.cpp"
	"*.c"
)

add_executable(${NAME}
	WIN32
	${CE_SRC}
)

target_link_libraries(${NAME}
	${CE_LIBS}
	cinnabar
)

set_target_properties(
	${NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${NAME}>"
)