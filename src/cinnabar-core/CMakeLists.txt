set(NAME cinnabar-core)
set(BUILD_SHARED_LIBS TRUE)

file(GLOB_RECURSE SRC
	"*.cpp"
	"*.c"
)

add_library(${NAME}
	${SRC}
)

target_link_libraries(${NAME}
	${SDL2_LIBS}
)