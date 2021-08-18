set(NAME cinnabar-core)
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
	${CE_LIBS}
)
