set(NAME cinnabar-render)
set(BUILD_SHARED_LIBS TRUE)

file(GLOB_RECURSE SRC
	"*.cpp"
	"*.c"
)

add_library(${NAME}
	${SRC}
)

target_link_libraries(${NAME}
	${OPENGL_LIBS}
	${GLEW_LIBS}
	${SDL2_LIBS}
	cinnabar-core
)