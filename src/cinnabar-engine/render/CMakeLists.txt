set(NAME cinnabar-render)
set(BUILD_SHARED_LIBS TRUE)


file(GLOB_RECURSE SRC
	"*.hpp"
	"*.cpp"
	"*.c"
)


add_library(${NAME}
	${SRC}
)


target_link_libraries(${NAME}
	cinnabar-core
	${CE_LIBS}
)